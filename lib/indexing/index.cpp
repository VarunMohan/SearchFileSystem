#include <iostream>
#include <vector>
#include <map>
#include "../tokenizer/IndexTokenizer.cpp"
#include "../utils/DirectoryFileUtils.h"
#include "../tokenizer/SFSToken.h"
#include "../datastructures/PostingList.h"

using namespace std;

vector<string> doc_id_to_path_map;
map<string, PostingList> inv_index;

inline void index_term(string term, int docid, int position) {
    cout << term << endl;
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
    vector<sfsFile> all_files = getAllFiles(".");
    for (int i=0; i < all_files.size(); i++) {
        index_file(all_files[i].fullpath, i);
        index_term(all_files[i].name, i, 0);
        doc_id_to_path_map.push_back(all_files[i].fullpath);
    }
}

int main(void) {
    index_files();
}
