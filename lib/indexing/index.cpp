#include <iostream>
#include <vector>
#include <map>
#include "../tokenizer/IndexTokenizer.cpp"
#include "../utils/DirectoryFileUtils.h"
#include "../tokenizer/SFSToken.h"
#include "../datastructures/PostingList.h"
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

vector<string> doc_id_to_path_map;
map<string, PostingList> inv_index;

inline void index_term(string term, int docid, int position) {
    if (inv_index.count(term) == 0) {
        PostingList plist(term);
        inv_index[term] = plist;
    }
    inv_index[term].add(docid, position);
}

void index_file(string fullpath, int docid) {
    IndexTokenizer tok(fullpath);
    while (!tok.isEmpty()) {
        SFSToken cur_token = tok.nextToken();
        index_term(cur_token.tok, docid, cur_token.pos);
    }
}

void index_files() {
    vector<sfsFile> all_files = getAllFiles("..");
    for (int i=0; i < all_files.size(); i++) {
        index_file(all_files[i].fullpath, i);
        index_term(all_files[i].name, i, 0);
        doc_id_to_path_map.push_back(all_files[i].fullpath);
        cout << "INDEXED: "<< all_files[i].name << endl;
    }
}

void print_index() {
    for (map<string, PostingList>::iterator it = inv_index.begin();
	 it != inv_index.end(); it++) {
	cout << it->first << endl;
	vector<Posting> postingList = it->second.getList();
	for (int i = 0; i < postingList.size(); i++) {
	    Posting cur = postingList[i];
	    cout << "\t" << doc_id_to_path_map[cur.getDocID()] << endl;
	}
    }
}

void serialize_doc_id_map(string fname) {
    ofstream out(fname.c_str());
    boost::archive::text_oarchive oarch(out);
    oarch << doc_id_to_path_map;
}

vector<string> deserialize_doc_id_map(string fname) {
    vector<string> dmap;
    ifstream in(fname.c_str());
    boost::archive::text_iarchive iarch(in);
    iarch >> dmap;
    return dmap;
}

void serialize_index(string fname) {
    ofstream out(fname.c_str());
    boost::archive::text_oarchive oarch(out);
    oarch << inv_index;
}

map<string, PostingList> deserialize_index(string fname) {
    map<string, PostingList> index;
    ifstream in(fname.c_str());
    boost::archive::text_iarchive iarch(in);
    iarch >> index;
    return index;
}
