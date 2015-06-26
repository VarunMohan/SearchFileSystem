#include <iostream>
#include <vector>

using namespace std;

class Posting {
 private:
    int docid;
    vector<int> positions;
 public:
    Posting (int id, int pos) {
        positions.push_back(pos);
        docid = id;
    }

    vector<int> getPositions() {
        return positions;
    }

    void add(int docid) {
        positions.push_back(docid);
    }

    int getDocID() {
    	return docid;
    }
};
