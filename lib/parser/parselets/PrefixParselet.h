#ifndef PREFIXPARSELET
#define PREFIXPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class PrefixParselet {
 protected:
    int precedence;
 public:
    PrefixParselet(int prec) {
	precedence = prec;
    }

    PrefixParselet() {

    }

    int getPrecedence() {
	return precedence;
    }

    virtual Expression * parse(Parser *p, Token t) = 0;
};

#endif
