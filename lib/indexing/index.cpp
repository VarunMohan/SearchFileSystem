#include <iostream>
#include <vector>
#include <map>
#include "tokenizer/IndexTokenizer.cpp"
#include "../utils/DirectoryFileUtils.h"

using namespace std;

vector<string> doc_id_to_path_map; 
map<string, PostingList> inv_index; 

void index_term(string term, int docid) {
    
}

void index_file(string fullpath, int docid) {
    IndexTokenizer tok(fullpath);
    while (!tok.isEmpty()) {
        string cur_token = tok.nextToken();
        index_term(cur_token, docid);
    }
}

void index_files() {
    vector<sfsFile> all_files = getAllFiles("..");
    for (int i=0; i < all_files.size(); i++) {
        index_file(all_files[i].fullpath, i);
        doc_id_to_path_map.push_back(all_files[i].name);
    }
}