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

    public:
    	TermIterator(PostingList plist) {
    		list = plist.getList();
    		pos = 0;
    	}

    	int getDocID() {
    		return list[pos].getDocID();
    	}

    	vector<int> getPositions() {
    		return list[pos].getPositions();
    	}

    	int next() {
    		if (pos < list.size() - 1) {
    			pos++;
    			return list[pos].getDocID();
    		}
    		return (DocIterator.MAX_DOCID);
    	}

    	int advance(int docID) {
    		while (next() < docID) {
    			//do nothing
    		}
    		return getDocID();
    	}  

    	int cost() {
    		return list.size();
    	}  	
};