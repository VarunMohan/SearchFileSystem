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

	TermIterator tIterator(p);

	int did = tIterator.next();
	while (did < 100) {
	    cout << did << endl;
	    did = tIterator.next();
	}
}
