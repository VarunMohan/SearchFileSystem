#ifndef PARSER
#define PARSER

#include <iostream>
#include <map>
#include "Token.h"
#include "Tokenizer.h"
#include "TokenTypes.h"
#include "parselets/PrefixParselet.h"
#include "parselets/InfixParselet.h"
#include "parselets/PhraseParselet.h"
#include "parselets/TermParselet.h"
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

    int getPrecedence() {
	if (infixParseletMap.find(peak()) == infixParseletMap.end()) return 0;
	InfixParselet *p = infixParseletMap[peak()];
	return p->getPrecedence();
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
	return parse(0);
    }

    Expression * parse(int prec) {
	Token curToken = consume();
	if (prefixParseletMap.find(curToken) == prefixParseletMap.end()) {
	    cout << "Error: Unexpected token " << curToken << endl;
	    exit(0);
	}
	PrefixParselet *prefixParselet = prefixParseletMap[curToken];
	Expression *e = prefixParselet->parse(this, curToken);

	while (prec < getPrecedence()) {
	    Token t = consume();
	    InfixParselet *p = infixParseletMap[t];
	    e = p->parse(this, e, t);
	}

	return e;
    }
};

#endif
