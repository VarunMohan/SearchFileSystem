#include <vector>
#include <iostream>
#include <algorithm>
#include "DocIterator.h"

using namespace std;

class ConjunctionIterator : public DocIterator
{
    private:
        bool end;
    	vector<DocIterator> subIterators;

        bool isMatch() {
            int curDoc = subIterators[0].getDocID();
            for (int i = 1; i < subIterators.size(); i++) {
                if (subIterators[i].getDocID() != curDoc) {
                    return false;
                }
            }
            return true;
        }

        int findNextMatch() {
            int matchID = subIterators[0].getDocID();
            if (matchID == DocIterator::MAX_DOCID){
                end = true;
                return DocIterator::MAX_DOCID;
            } 
            bool totalMatch = false;
            while (!totalMatch) {
                int maxAdvance = matchID;
                totalMatch = true;
                for (int i = 1; i < subIterators.size(); i++) {
                    if (subIterators[i].advance(matchID) != matchID){
                        int advancedID = subIterators[i].getDocID();
                        if (advancedID == DocIterator::MAX_DOCID) {
                            end = true;
                            return DocIterator::MAX_DOCID;
                        }
                        totalMatch = false;
                        maxAdvance = advanceID;
                        break;
                    }
                }
                if (!totalMatch) {
                    subIterators[0].advance(maxAdvance);
                    matchID = subIterators[0].getDocID();
                }
            }
            return matchID;
        }


    public:
    	ConjunctionIterator(vector<DocIterator> iterators) {
	       subIterators = iterators;
	       end = false;
            sort(subIterators.begin(), subIterators.end(), DocIterator::compare);
    	}

    	int getDocID() {
            if (end) return DocIterator.MAX_DOCID;
    		if (!isMatch()) {
                return next();
            }
            return subIterators[0].getDocID();
    	}

    	int next() {
            if (end) return DocIterator.MAX_DOCID;
    		subIterators[0].next();
            return findNextMatch();
    	}

    	int advance(int docid) {
            if (end) return DocIterator.MAX_DOCID;
    		subIterators[0].advance(docid);
    		return findNextMatch();
    	}

        int cost () {
            //no real value
            return subIterators[0].cost();
        }
};
