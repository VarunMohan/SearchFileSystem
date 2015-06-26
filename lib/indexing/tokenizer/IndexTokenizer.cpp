#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "SFSToken.h"

using namespace std;

class IndexTokenizer {
private:
    unordered_set<string> stopwords;
    ifstream fileInput;

    void readStopWords() {
	ifstream stopwordsFile("../stopwords.txt");
	while (!stopwordsFile.eof()) {
	    string cur;
	    stopwordsFile >> cur;
	    this->stopwords.insert(cur);
	}
	stopwordsFile.close();
    }

    //Assumes the current file is at an alphanum char
    SFSToken nextTokenHelper() {
	string token = "";
	int position = this->fileInput.tellg();
	char c;

	while (is_alphanum(this->fileInput.peek())) {
	    this->fileInput >> c;
	    token += c;
	}
	this->advanceToAlphanumChar();
	return (SFSToken){token, position};
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
	this->fileInput.open(fname);
	this->readStopWords();
	this->advanceToAlphanumChar();
    }

    //Assumes that the first character is alphanum
    SFSToken nextToken() {
	SFSToken curToken = this->nextTokenHelper();
	while (stopwords.find(curToken.tok) != stopwords.end())
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
