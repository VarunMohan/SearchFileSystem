#ifndef EMPTYITERATOR
#define EMPTYITERATOR

#include <iostream>
#include "DocIterator.h"

using namespace std;

class EmptyIterator : public DocIterator
{

    public:
    	EmptyIterator() {
    	}

    	int getDocID() {
    		return DocIterator::MAX_DOCID;
    	}

    	int next() {
    		return (DocIterator::MAX_DOCID);
    	}

    	int advance(int docID) {
	       return DocIterator::MAX_DOCID;
	   }

    	int cost() {
    		return 0;
    	}

};

#endif
