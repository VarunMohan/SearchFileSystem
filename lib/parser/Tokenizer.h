#ifndef TOKENIZER
#define TOKENIZER

#include <iostream>
#include <vector>
#include "Token.h"
#include "TokenTypes.h"

using namespace std;

class Tokenizer {
 private:
    vector<Token> tokens;
    int index;
 public:
    Tokenizer() {
	index = 0;
    }

    Tokenizer(string rawString) {
	tokens.push_back(Token(PHRASE_TOKEN, "\"Hello there\""));
	tokens.push_back(Token(AND_TOKEN, "AND"));
	tokens.push_back(Token(PHRASE_TOKEN, "\"Hello world\""));
	tokens.push_back(Token(OR_TOKEN));
	tokens.push_back(Token(PHRASE_TOKEN, "\"blah2\""));
	index = 0;
    }

    void advance() {
	index++;
    }

    Token curToken() {
	return tokens[index];
    }
};

#endif
