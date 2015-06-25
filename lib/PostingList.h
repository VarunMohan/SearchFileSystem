#include <iostream>
#include <set>
#include "Posting.h"

using namespace std;

class PostingList {
 private:
    set<Posting> posting_list;
 public:
    Posting(set<Posting>& pos_list) {
    	posting_list = pos;
    }

    vector<int> getList() {
    	return posting_list;
    }
};
