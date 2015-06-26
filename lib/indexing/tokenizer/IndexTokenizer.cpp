#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class IndexTokenizer {
private:
    ifstream fileInput;

    bool is_alphanum(char c) {
	return ((('a' <= c) && (c <= 'z')) ||
		(('0'<= c) && (c <= '9')) ||
		(('A'<= c) && (c <= 'Z')));
    }

    void advanceToAlphanumChar() {
	while (!this->fileInput.eof() &&
	       !is_alphanum(this->fileInput.peek())) {
	    this->fileInput.get();
	}
    }

public:
    //Takes a filename and initializes the IndexTokenizer
    IndexTokenizer(string fname) {
	this->fileInput.open(fname);
	this->advanceToAlphanumChar();
    }

    string nextToken() {
	string token = "";
	char c;
	while (is_alphanum(this->fileInput.peek())) {
	    this->fileInput >> c;
	    token += c;
	}
	this->advanceToAlphanumChar();
	return token;
    }

    bool isEmpty() {
	return this->fileInput.eof();
    }

    ~IndexTokenizer() {
	this->fileInput.close();
    }
};
