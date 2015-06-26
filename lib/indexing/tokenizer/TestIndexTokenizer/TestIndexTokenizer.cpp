#include <iostream>
#include "../IndexTokenizer.cpp"
#include "../SFSToken.h"

using namespace std;

int main(void) {
    IndexTokenizer t("testinput");
    while (!t.isEmpty()) {
	SFSToken i = t.nextToken();
	cout << i.tok << " " << i.pos << endl;
    }
}
