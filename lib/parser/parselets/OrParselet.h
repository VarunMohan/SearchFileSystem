#ifndef ORPARSELET
#define ORPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../expressions/OrExpression.h"
#include "PrefixParselet.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class OrParselet : public InfixParselet {
 public:
    OrParselet() {

    }

    Expression * parse(Parser *p, Expression *left, Token t) {
	Expression *rest = p->parse();
	return new OrExpression(left, rest);
    }
};

#endif
