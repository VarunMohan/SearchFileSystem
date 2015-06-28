#ifndef ANDPARSELET
#define ANDPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../expressions/AndExpression.h"
#include "PrefixParselet.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class AndParselet : public InfixParselet {
 public:
    AndParselet(int prec) : InfixParselet(prec) {

    }

    AndParselet() {

    }

    Expression * parse(Parser *p, Expression *left, Token t) {
	Expression *rest = p->parse(precedence-1);
	return new AndExpression(left, rest);
    }
};

#endif
