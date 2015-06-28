#ifndef TERMPHRASEEXPRESSION
#define TERMPHRASEEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

using namespace std;

class TermPhraseExpression : public Expression {
 private:
    Token tok;
 public:
    TermPhraseExpression(Token t) {
	tok = t;
    }

    string toString() {
	return tok.value;
    }

    void free() {
	delete this;
    }
};

#endif
