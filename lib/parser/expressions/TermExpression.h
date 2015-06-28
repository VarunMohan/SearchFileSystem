#ifndef TERMEXPRESSION
#define TERMEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

using namespace std;

class TermExpression : public Expression {
 private:
    Token tok;
 public:
    TermExpression(Token t) {
	tok = t;
    }

    string toString() {
	return "Term("+tok.value+")";
    }

    void free() {
	delete this;
    }
};

#endif
