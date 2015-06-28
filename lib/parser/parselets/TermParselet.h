#ifndef TERMPARSELET
#define TERMPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../expressions/TermExpression.h"
#include "PrefixParselet.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class TermParselet : public PrefixParselet {
 public:
    TermParselet() {

    }

    Expression * parse(Parser *p, Token t) {
	return new TermExpression(t);
    }
};

#endif
