#ifndef TOKENIZER
#define TOKENIZER

#include <iostream>
#include <vector>
#include "Token.h"
#include "TokenTypes.h"

using namespace std;

//Replace multiple spaces with one single space
static inline bool bothAreSpaces(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

class Tokenizer {
 private:
    vector<Token> tokens;
    int index;
    string str;

    int extractTermPhrase(int index, Token &curToken) {
	string termPhrase = "";
	bool isPhrase = false;
	index++;
	while (!(str[index] == '"' && str[index-1] != '\\')) {
	    if (str[index] == ' ') isPhrase = true;
	    termPhrase += str[index++];
	}
	if (isPhrase) curToken = Token(PHRASE_TOKEN, termPhrase);
	else curToken = Token(TERM_TOKEN, termPhrase);
	return index+1;
    }

    int extractAnd(int index, Token &curToken) {
	curToken = Token(AND_TOKEN);
	return index + 3;
    }

    int extractOr(int index, Token &curToken) {
	curToken = Token(OR_TOKEN);
	return index + 3;
    }

    string getChunk(int index) {
	if (str[index] == ' ') return " ";
	string res;
	while (str[index] != ' ') res += str[index++];
	return res;
    }

    int extractToken(int index, Token &curToken) {
	string curChunk = getChunk(index);
	if (curChunk[0] == ' ') {
	    return index + 1;
	}
	if (curChunk[0] == '"') {
	    return extractTermPhrase(index, curToken);
	}
	else if (curChunk == "AND") {
	    return extractAnd(index, curToken);
	}
	else if (curChunk == "OR") {
	    return extractOr(index, curToken);
	}
	else {
	    return index + 1;
	}
    }

    void tokenize() {
	string::iterator new_end = unique(str.begin(), str.end(), bothAreSpaces);
	str.erase(new_end, str.end());
	trim(str);
	int i = 0;
	while (i < str.size()) {
	    Token curToken = Token();
	    i = extractToken(i, curToken);
	    if (curToken.token != "")
		tokens.push_back(curToken);
	}
    }

 public:
    Tokenizer() {
	index = 0;
    }

    Tokenizer(string rawString) {
	index = 0;
	str = rawString;
	tokenize();
    }

    void advance() {
	index++;
    }

    Token curToken() {
	return tokens[index];
    }
};

#endif
