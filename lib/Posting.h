#include <iostream>
#include <vector>

using namespace std;

class Posting {
 private:
    int docid;
    vector<int> positions;
 public:

    Posting(vector<int>& pos) {
    	positions = pos;
    }

    vector<int> getPositions() {
    	return positions;
    }

    int getDocID() {
    	return docid;
    }
};
