#include <iostream>
#include <vector>
#include "Posting.h"

using namespace std;

class PostingList {
 private:
    vector<Posting> posting_list;
    string term;

    bool isEmpty() {
    	return posting_list.size() == 0;
    }
 public:
 	PostingList(string t) {
 		term = t;
 	}

 	void add(int docid, int position) {
 		if (!isEmpty() && posting_list[posting_list.size() - 1].getDocID() == docid) {
 			posting_list[posting_list.size() - 1].add(position);
 		} else {
 			Posting p(docid, position);
 			posting_list.push_back(p);
 		}

 	}

 	vector<Posting> getList() {
 		return posting_list;
 	}

 	string getTerm() {
 		return term;
 	}

};
