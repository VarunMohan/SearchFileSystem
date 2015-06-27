#include <iostream>
#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

class Posting {
 private:
    int docid;
    vector<int> positions;
 public:
    Posting() {
	docid = -1;
    }

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

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
	ar & positions;
	ar & docid;
    }
};
