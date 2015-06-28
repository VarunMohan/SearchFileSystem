#include <iostream>
#include <vector>
#include "../PhraseIterator.h"
#include "../PostingList.h"
#include "../TermIterator.h"

using namespace std;

int main() {
    PostingList t1("t1");
    t1.add(1,1);
    t1.add(2,1);
    t1.add(2,4);
    t1.add(3,1);
    t1.add(5,1);
    t1.add(6,1);
    t1.add(7,1);

    PostingList t2("t2");
    t2.add(1,2);
    t2.add(2,2);
    t2.add(2,5);
    t2.add(6,3);
    t2.add(7,2);
    t2.add(9,1);

    PostingList t3("t3");
    t3.add(1,3);
    t3.add(2,3);
    t2.add(2,6);
    t3.add(4,1);
    t3.add(6,2);
    t3.add(7,3);
    t3.add(8,1);

    TermIterator tt1(t1);
    TermIterator tt2(t2);
    TermIterator tt3(t3);

    vector<TermIterator *> iterators;
    iterators.push_back(&tt1);
    iterators.push_back(&tt2);
    iterators.push_back(&tt3);

    vector<int> offsets;
    offsets.push_back(1); 
    offsets.push_back(1);

    PhraseIterator piter(iterators, offsets);
    //Expect 1, 2, 7
    cout << piter.getDocID() << endl;
    piter.next();
    cout << piter.getDocID() << endl;
    piter.next();
    cout << piter.getDocID() << endl << endl;

    TermIterator ttt1(t1);
    TermIterator ttt2(t2);
    TermIterator ttt3(t3);

    vector<TermIterator *> iterators2;
    iterators2.push_back(&ttt1);
    iterators2.push_back(&ttt2);
    iterators2.push_back(&ttt3);

    PhraseIterator piter2(iterators2, offsets);
    //Expect 7, 2147483647
    cout << piter2.advance(5) << endl;
    cout << piter2.next() << endl;
}
