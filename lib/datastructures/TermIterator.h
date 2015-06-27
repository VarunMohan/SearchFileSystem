#include <vector>
#include <iostream>
#include "DocIterator.h"
#include "PostingList.h"

using namespace std;

class TermIterator : public DocIterator
{
    private:
    	vector<Posting> list;
    	int pos;
    	bool end;

    public:
    	TermIterator(PostingList plist) {
    		list = plist.getList();
    		pos = 0;
    	}

    	int getDocID() {
    		if(end) {
    			return DocIterator::MAX_DOCID;
    		}
    		return list[pos].getDocID();
    	}

    	vector<int> getPositions() {
    		if (end) {
    			vector <int> v; return v;
    		}
    		return list[pos].getPositions();
    	}

    	int next() {
    		if (pos < list.size() - 1) {
    			pos++;
    			return list[pos].getDocID();
    		}
    		end = true;
    		return (DocIterator::MAX_DOCID);
    	}

    	//MAKE ADVANCE FASTER
    	int advance(int docID) {
    		if (end) return DocIterator::MAX_DOCID;

    		while (next() < docID) {
    			//do nothing
    		}
    		return getDocID();
    	}

    	int cost() {
    		return list.size();
    	}

	DocIterator& operator=(const DocIterator& other) {
	    return *this;
	}

};
