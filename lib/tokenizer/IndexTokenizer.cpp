#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "SFSToken.h"
#include "../misc/stopwords.cpp"

using namespace std;

class IndexTokenizer {
private:
    set<string> stopwordset;
    ifstream fileInput;
    int absolutePosition;

    void readStopWords() {
	stopwordset = getStopwords();
    }

    //Assumes the current file is at an alphanum char
    SFSToken nextTokenHelper() {
	string token = "";
	char c;

	while (is_alphanum(this->fileInput.peek())) {
	    this->fileInput >> c;
	    token += tolower(c);
	}
	this->advanceToAlphanumChar();
	absolutePosition++;
	return (SFSToken){token, absolutePosition};
    }

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
    absolutePosition = 0;
	this->fileInput.open(fname);
	this->readStopWords();
	this->advanceToAlphanumChar();
    }

    //Assumes that the first character is alphanum
    SFSToken nextToken() {
	SFSToken curToken = this->nextTokenHelper();
	while (stopwordset.find(curToken.tok) != stopwordset.end())
	    curToken = this->nextTokenHelper();
	return curToken;
    }

    bool isEmpty() {
	return this->fileInput.eof();
    }

    ~IndexTokenizer() {
	this->fileInput.close();
    }
};
