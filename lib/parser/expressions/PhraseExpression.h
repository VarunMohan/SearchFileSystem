#ifndef PHRASEEXPRESSION
#define PHRASEEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

using namespace std;

class PhraseExpression : public Expression {
 private:
    Token tok;
 public:
    PhraseExpression(Token t) {
	tok = t;
    }

    string toString() {
	return "Phrase("+tok.value+")";
    }

    void free() {
	delete this;
    }
};

#endif
