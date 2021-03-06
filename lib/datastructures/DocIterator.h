#ifndef DOCITERATOR
#define DOCITERATOR

class DocIterator {
 public:
    static const int MAX_DOCID = 2147483647;

    virtual int getDocID() = 0;
    virtual int next() = 0;
    virtual int advance(int docid) = 0;
    virtual int cost() = 0;

    static int compare(DocIterator *a, DocIterator *b) {
	return a->cost() < b->cost();
    }
};

#endif
