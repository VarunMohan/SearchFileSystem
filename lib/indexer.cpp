#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_set>
#include <map>
#include <vector>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

unordered_set<string> stopwords;
map<string, vector<string> > inv_index;
const char * extensions[] = {"txt", "doc"};
vector<string> valid_extensions(extensions, end(extensions));

map<string, vector<string> > deserialize(string fname) {
    ifstream in(fname.c_str());
    map<string, vector<string> > loaded_map;
    boost::archive::text_iarchive iarch(in);
    iarch >> loaded_map;
    return loaded_map;
}

void serialize(map<string, vector<string> > map, string file_out) {
   ofstream fout(file_out.c_str());
   boost::archive::text_oarchive oarch(fout);
   oarch << map;
}

void read_stopwords(string fname) {
    ifstream in(fname);
    while (!in.eof()) {
        string cur;
        in >> cur;
        stopwords.insert(cur);
    }
    in.close();
}

bool is_stopword(string word) {
    return stopwords.find(word) != stopwords.end();
}

bool is_valid_file(string name) {
    string ext = name.substr(name.find_last_of(".")+1);
    for (int i = 0; i < valid_extensions.size(); i++) {
        if (ext == valid_extensions[i]) return true;
    }
    return false;
}

bool is_valid_dir(string name) {
    return name[0] != '.';
}

bool is_alphanum(char c) {
    if ((('a' <= c) && (c <= 'z')) || (('0'<= c) && (c <= '9')) ||  (('A'<= c) && (c <= 'Z'))) {
        return true;
    }
    return false;
}

inline void index_term(string s, string file_path) {
    if (is_stopword(s)) return;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (inv_index.count(s) == 0) {
        vector<string> v;
        v.push_back(file_path);
        inv_index[s] = v;
    } else {
        vector<string> v = inv_index[s];
        if (v[v.size() - 1] != file_path) {
            inv_index[s].push_back(file_path);
        }
    }
}

inline void index_string(string s, string file_path) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    string curstring = "";
    for (int i=0; i< s.size(); i++) {
        if (!is_alphanum(s[i])) {
            if (curstring.size() > 0) {
                index_term(curstring, file_path);
            }
            curstring = "";
        } else {
            curstring += s[i];
        }
    }
    if (curstring != "") {
        index_term(curstring, file_path);
    }
}

void index_file(string file_path, string file_name) {
    ifstream in(file_path.c_str());
    while (!in.eof()) {
        string s;
        in >> s;
        index_string(s, file_path);
    }
    index_string(file_name, file_path);
    in.close();
}

void list_directory_contents(string path, vector<string>& dirs, vector<pair<string, string> >& files) {
    vector<string> results;
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path.c_str());
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_DIR && is_valid_dir(entry->d_name)) {
            dirs.push_back(string(entry->d_name));
        } else if (entry->d_type == DT_REG && is_valid_file(entry->d_name)) {
            files.push_back(make_pair(path+"/"+string(entry->d_name), string(entry->d_name)));
        }
    }

    closedir(dp);
    return;
}

void get_all_files(string base_path, vector<pair<string, string> > &all_files) {
    vector<string> dirs;
    list_directory_contents(base_path, dirs, all_files);
    for (int i = 0; i < dirs.size(); i++) {
        get_all_files(base_path + "/" + dirs[i], all_files);
    }
}

void index_all_files(string base_path) {
    read_stopwords("lib/stopwords.txt");
    vector<pair<string, string> > all_files;
    get_all_files(base_path, all_files);
    for (int i = 0; i < all_files.size(); i++) {
        index_file(all_files[i].first, all_files[i].second);
    }
}

void test_serialization() {
    serialize(inv_index, "test-serialization");
    map<string, vector<string> > deserialized = deserialize("test-serialization");
    for (std::map<string,vector<string> >::iterator it=inv_index.begin(); it!=inv_index.end(); ++it) {
        vector<string> v1 = it->second;
        vector<string> v2 = deserialized[it->first];
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
            perror("Bad serialization...");
            exit(0);
            }
        }
    }
}

int main() {
    index_all_files(".");
    for (std::map<string,vector<string> >::iterator it=inv_index.begin(); it!=inv_index.end(); ++it) {
    cout << it -> first << endl;
    vector<string> v = it -> second;
    for (int i=0; i < v.size(); i++) {
        cout << v[i]<< " ";
    }
    cout<<endl;
    }
    test_serialization();
}


