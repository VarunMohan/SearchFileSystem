#include <iostream>
#include "../TermIterator.h"
#include "../PostingList.h"

using namespace std;

int main() {
	PostingList p("cat");
	p.add(1,1);
	p.add(2,3);
	p.add(3,4);
	p.add(4,2);
	p.add(5,10);
	p.add(7,8);

	TermIterator tIterator1(p);
	TermIterator tIterator2(p);
	TermIterator tIterator3(p);

	int did = tIterator1.getDocID();
	while (did < 100) {
	    cout << did << endl;
	    did = tIterator1.next();
	}

	cout << endl;
	did = tIterator2.advance(2);
	cout << did << endl;
	did = tIterator2.advance(4);
	cout << did << endl;
	did = tIterator2.advance(6);
	cout << did << endl;
	did = tIterator2.advance(6);
	cout << did << endl;
	did = tIterator2.advance(9);
	cout << did << endl;

	cout << endl;
	did = tIterator3.advance(6);
	cout << did << endl;
	did = tIterator3.advance(5);
	cout << did << endl;
}
