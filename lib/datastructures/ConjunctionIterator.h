#include <vector>
#include <iostream>
#include <algorithm>
#include "DocIterator.h"

using namespace std;

const int MAX_DOCID = 2147483647;

class ConjunctionIterator : public DocIterator
{
    private:
    	vector<DocIterator> subIterators;

    public:
    	TermIterator(vector<DocIterator> iterators) {
    		subIterators = iterators;
            sort(subIterators.begin(), subIterators.end(), DocIterator.cmp);
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

        int cost () {
            //no real value
            return subIterators[0].cost();
        } 	
};