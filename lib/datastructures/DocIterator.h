class DocIterator {
 public:
    virtual int getDocid() = 0;
    virtual int next() = 0;
    virtual int advance(int docid) = 0;
    virtual int const() = 0;

    bool compare(const DocIterator & d1, const DocIterator & d2)
    {
       return d1.cost() < d2.cost();
    }
};

