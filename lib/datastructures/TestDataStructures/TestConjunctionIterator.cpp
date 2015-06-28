#include <iostream>
#include "../ConjunctionIterator.h"
#include "../PostingList.h"
#include "../TermIterator.h"

using namespace std;

int main() {
    PostingList t1("t1");
    t1.add(1,1);
    t1.add(2,1);
    t1.add(3,1);
    t1.add(5,1);
    t1.add(7,1);

    PostingList t2("t2");
    t2.add(1,1);
    t2.add(2,1);
    t2.add(6,1);
    t2.add(7,1);
    t2.add(9,1);

    PostingList t3("t3");
    t3.add(2,1);
    t3.add(4,1);
    t3.add(6,1);
    t3.add(7,1);
    t3.add(8,1);

    TermIterator tt1(t1);
    TermIterator tt2(t2);
    TermIterator tt3(t3);

    vector<DocIterator *> iterators;
    iterators.push_back(&tt1);
    iterators.push_back(&tt2);
    iterators.push_back(&tt3);

    ConjunctionIterator citer(iterators);
    //Expect 2, 7, 2147483647
    cout << citer.getDocID() << endl;
    citer.next();
    cout << citer.getDocID() << endl;
    citer.next();
    cout << citer.getDocID() << endl;

    TermIterator ttt1(t1);
    TermIterator ttt2(t2);
    TermIterator ttt3(t3);

    vector<DocIterator *> iterators2;
    iterators2.push_back(&ttt1);
    iterators2.push_back(&ttt2);
    iterators2.push_back(&ttt3);

    ConjunctionIterator citer2(iterators2);
    //Expect 7, 2147483647
    cout << citer2.advance(7) << endl;
    cout << citer2.next() << endl;
}
