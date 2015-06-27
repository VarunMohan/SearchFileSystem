class DocIterator {
 public:
    virtual int getDocid() = 0;
    virtual int next() = 0;
    virtual int advance(int docid) = 0;
};
