#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

map<string, vector<string> > inv_index;
const char * extensions[] = {"txt", "doc"};
vector<string> valid_extensions(extensions, end(extensions));

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

string get_cwd() {
    char cur_path[FILENAME_MAX];
    getcwd(cur_path, sizeof(cur_path));
    return string(cur_path);
}

bool is_alphanum(char c) {
    if ((('a' <= c) && (c <= 'z')) || (('0'<= c) && (c <= '9')) ||  (('A'<= c) && (c <= 'Z'))) {
        return false;
    }
    return true;
}

void index_file(string file_path) {
    ifstream in(file_path.c_str());
    while (!in.eof()) {
        string s;
        in >> s;
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        s.erase(std::remove_if(s.begin(), s.end(), is_alphanum), s.end());
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
    in.close();
}

void list_directory_contents(string path, vector<string>& dirs, vector<string>& files) {
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
            files.push_back(string(entry->d_name));
        }
    }

    closedir(dp);
    return;
}

void get_all_files(string base_path, vector<string> &all_files) {
    vector<string> dirs;
    list_directory_contents(base_path, dirs, all_files);
    for (int i = 0; i < dirs.size(); i++) {
        get_all_files(base_path + "/" + dirs[i], all_files);
    }
}

void index_all_files(string base_path) {
    vector<string> all_files;
    get_all_files(base_path, all_files);
    for (int i = 0; i < all_files.size(); i++) {
        index_file(base_path + "/" + all_files[i]);
    }
}

int main() {
  index_all_files(get_cwd());
  for (std::map<string,vector<string> >::iterator it=inv_index.begin(); it!=inv_index.end(); ++it) {
    cout << it -> first << endl;
    vector<string> v = it -> second;
    for (int i=0; i < v.size(); i++) {
	cout << v[i]<< " ";
    }
    cout<<endl;
  }
}
