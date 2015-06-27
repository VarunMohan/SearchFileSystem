#include "DocIterator.h"
#include "PostingList.h"

const int MAX_DOCID = 2147483647;

class TermIterator : public DocIterator
{
    private:
    	vector<Posting> list;
    	int pos = 0;

    public:
    	TermIterator(PostingList plist) {
    		list = plist.getList();
    	}

    	int getDocID() {
    		return list[pos].getDocID();
    	}

    	vector<int> getPositions() {
    		return list[pos].getPositions();
    	}

    	int next() {
    		if (pos < list.size()) {
    			pos++;
    			return list[pos].getDocID();
    		}
    		else return MAX_DOCID;
    	}

    	int advance(int docid) {
    		while (next() < docID) {
    			//do nothing
    		}
    		return getDocID();
    	}    	
};