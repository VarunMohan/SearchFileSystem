#ifndef INFIXPARSELET
#define INFIXPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class InfixParselet {
 protected:
    int precedence;
 public:
    InfixParselet(int prec) {
	precedence = prec;
    }

    InfixParselet() {

    }

    int getPrecedence() {
	return precedence;
    }

    virtual Expression * parse(Parser *p, Expression *left, Token t) = 0;
};

#endif
