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
            if (getDocID() >= docID)  return getDocID();

	    //Binary search a posting with specified docid
	    Posting toFind = Posting(docID, 0);
	    vector<Posting>::iterator it = lower_bound(list.begin(), list.end(), toFind);

	    //Get position of found element. If less than current
	    //position, return end token
	    int newpos = it - list.begin();
	    if (newpos >= list.size()) {
		end = true;
		return DocIterator::MAX_DOCID;
	    }
	    pos = newpos;
	    return getDocID();
    	}

    	int cost() {
    		return list.size();
    	}

};
