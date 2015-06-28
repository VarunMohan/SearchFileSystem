#include <vector>
#include <iostream>
#include "DocIterator.h"

using namespace std;

class DisjunctionIterator : public DocIterator
{
    private:
        bool end;
    	vector<DocIterator *> subIterators;
        int head;

        int getLead() {
            int lead = 0;
            int curMinID = subIterators[0]->getDocID();
            for (int i = 1; i < subIterators.size(); i++) {
                int curID = subIterators[i]->getDocID();
                if (curMinID > curID) {
                    lead = i;
                    curMinID = curID;
                }
            }
            if (curMinID == DocIterator::MAX_DOCID) {
                end = true;
            }
            return lead;
        }

    public:
    	DisjunctionIterator(vector<DocIterator *> iterators) {
	       subIterators = iterators;
	       end = false;
           head = getLead();
    	}

    	int getDocID() {
            if (end) return DocIterator::MAX_DOCID;
            return subIterators[head].getDocID();
    	}

    	int next() {
            if (end) return DocIterator::MAX_DOCID;
    		int prevDocID = getDocID();
            for (int i = 0; i < subIterators.size(); i++) {
                if (subIterators[i]->getDocID() == prevDocID) {
                    subIterators[i]->next();
                }
            }
            head = getLead();
            if (end) return DocIterator::MAX_DOCID;
            return subIterators[head]->getDocID();
    	}

    	int advance(int docid) {
            if (end) return DocIterator::MAX_DOCID;
            for (int i = 0; i < subIterators.size(); i++) {
                subIterators[i]->advance(docid);
            }
            head = getLead();
            if (end) return DocIterator::MAX_DOCID;
            return subIterators[head]->getDocID();
    	}

        int cost () {
            int cost = 0;
            for (int i = 0; i < subIterators.size(); i++) {
                cost += subIterators[i]->cost();
            }
            return cost;
        }
};
