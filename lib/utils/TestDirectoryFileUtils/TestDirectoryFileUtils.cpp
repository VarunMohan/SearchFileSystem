#include <iostream>
#include "../DirectoryFileUtils.h"

using namespace std;

void printFiles(vector<SfsFile> &files) {
    for (int i = 0; i < files.size(); i++) {
	cout << "(" << files[i].name << " : " << files[i].fullpath << ")" << endl;
    }
}

int main(void) {
    vector<SfsFile> files = getAllFiles(".");
    printFiles(files);
}
