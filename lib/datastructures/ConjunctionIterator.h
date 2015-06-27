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
            bool totalMatch = false;
            while (!totalMatch) {
                int maxAdvance = matchID;
                totalMatch = true;
                for (int i = 1; i < subIterators.size(); i++) {
                    if (subIterators[i].advance(matchID) != matchID){
                        totalMatch = false;
                        maxAdvance = (maxAdvance < subIterators[i].getDocID()) ? subIterators[i].getDocID() : maxAdvance;
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
            sort(subIterators.begin(), subIterators.end(), DocIterator.compare());
    	}

    	int getDocID() {
    		if (!isMatch()) {
                return next();
            }
            return subIterators[0].getDocID();
    	}

    	int next() {
    		subIterators[0].next();
            findNextMatch();
    	}

    	int advance(int docid) {
    		subIterators[0].advance(docid);
    		return findNextMatch();
    	}   

        int cost () {
            //no real value
            return subIterators[0].cost();
        } 	
};