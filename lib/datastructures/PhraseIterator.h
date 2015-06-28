#include <vector>
#include <iostream>
#include "TermIterator.h"
#include "DocIterator.h"

using namespace std;

class PhraseIterator : public DocIterator
{
    private:
        bool end;
    	vector<TermIterator *> subIterators;
        vector<int> offsets;

        bool isPhrase() {
            int curDoc = subIterators[0]->getDocID();
            for (int i = 1; i < subIterators.size(); i++) {
                if (subIterators[i]->getDocID() != curDoc) {
                    return false;
                }
            }
            vector<vector<int> > positions;
            vector<int> start;
            for (int i = 0; i < subIterators.size(); i++) {
                positions.push_back(subIterators[i]->getPositions());
                start.push_back(0);
            }

            for (int i = 0; i < positions[0].size(); i++) {
                int curPos = positions[0][i];
                bool phrase = true;
                for (int j = 1; j < subIterators.size(); j++) {
                    while (positions[j][start[j]] < curPos + offsets[j-1]) {
                        start[j]++;
                        if (start[j] == positions[j].size()) return false;
                    }
                    if (positions[j][start[j]] != curPos + offsets[j-1]) {
                        phrase = false;
                        break;
                    }
                    curPos += offsets[j-1];
                }
                if (phrase) return true;
            }
            return false;
        }

        int findNextMatch() {
            int matchID = subIterators[0]->getDocID();
            if (matchID == DocIterator::MAX_DOCID){
                end = true;
                return DocIterator::MAX_DOCID;
            }
            bool totalMatch = false;
            while (!totalMatch) {
                int maxAdvance = matchID;
                totalMatch = true;
                for (int i = 1; i < subIterators.size(); i++) {
                    int advancedID = subIterators[i] -> advance(matchID);
                    if (advancedID != matchID){
                        if (advancedID == DocIterator::MAX_DOCID) {
                            end = true;
                            return DocIterator::MAX_DOCID;
                        }
                        totalMatch = false;
                        maxAdvance = advancedID;
                        break;
                    }
                }
                if (!totalMatch) {
                    subIterators[0]->advance(maxAdvance);
                    matchID = subIterators[0]->getDocID();
                }
            }
            if (!isPhrase()) {
                subIterators[0]->next();
                return findNextMatch();
            }
            return matchID;
        }


    public:
    	PhraseIterator(vector<TermIterator *> iterators, vector<int> offs) {
	       subIterators = iterators;
           offsets = offs;
	       end = false;
           findNextMatch();
    	}

    	int getDocID() {
            if (end) return DocIterator::MAX_DOCID;
            return subIterators[0]->getDocID();
    	}

    	int next() {
            if (end) return DocIterator::MAX_DOCID;
    		subIterators[0]->next();
            return findNextMatch();
    	}

    	int advance(int docid) {
           if (end) return DocIterator::MAX_DOCID;
	       subIterators[0]->advance(docid);
	       return findNextMatch();
    	}

        int cost () {
            //no real value
            return subIterators[0]->cost();
        }
};
