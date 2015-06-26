#include <iostream>
#include <vector>

using namespace std;

class Posting {
 private:
    int docid;
    vector<int> positions;
 public:
    Posting (int pos, int id) {
        positions.push_back(pos);
        docid = id;
    }

    vector<int> getPositions() {
        return positions;
    }

    vector <int> add(int docid) {
        positions.push_back(i);
    }

    int getDocID() {
    	return docid;
    }
};
