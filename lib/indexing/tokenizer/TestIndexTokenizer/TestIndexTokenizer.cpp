#include <iostream>
#include "../IndexTokenizer.cpp"

using namespace std;

int main(void) {
    IndexTokenizer t("testinput");
    while (!t.isEmpty()) {
	cout << t.nextToken() << endl;
    }
}
