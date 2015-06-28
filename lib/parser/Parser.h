#ifndef PARSER
#define PARSER

#include <iostream>
#include <map>
#include "Token.h"
#include "Tokenizer.h"
#include "TokenTypes.h"
#include "parselets/PrefixParselet.h"
#include "parselets/InfixParselet.h"
#include "parselets/TermPhraseParselet.h"
#include "expressions/Expression.h"

using namespace std;

class Parser {
 private:
    map<Token, PrefixParselet *> prefixParseletMap;
    map<Token, InfixParselet *> infixParseletMap;
    Tokenizer tokenizer;

    Token peak() {
	return tokenizer.curToken();
    }

    Token consume() {
	Token t = peak();
	tokenizer.advance();
	return t;
    }

 public:
    Parser() {
	tokenizer = Tokenizer();
    }

    void registerPrefixParselet(Token t, PrefixParselet *p) {
	prefixParseletMap[t] = p;
    }

    void registerInfixParselet(Token t, InfixParselet *p) {
	infixParseletMap[t] = p;
    }

    Expression * parseRawString(string query) {
	tokenizer = Tokenizer(query);
	return parse();
    }

    Expression * parse() {
	Token curToken = consume();
	if (prefixParseletMap.find(curToken) == prefixParseletMap.end()) {
	    cout << "Error: Unexpected token " << curToken << endl;
	    exit(0);
	}
	PrefixParselet *prefixParselet = prefixParseletMap[curToken];
	Expression *e = prefixParselet->parse(this, curToken);

	Token nextToken = peak();
	if (infixParseletMap.find(nextToken) != infixParseletMap.end()) {
	    consume();
	    InfixParselet *infixParselet = infixParseletMap[nextToken];
	    return infixParselet->parse(this, e, nextToken);
	}

	return e;
    }
};

#endif
