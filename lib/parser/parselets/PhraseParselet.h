#ifndef PHRASEPARSELET
#define PHRASEPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../expressions/PhraseExpression.h"
#include "PrefixParselet.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class PhraseParselet : public PrefixParselet {
 public:
    PhraseParselet() {

    }

    Expression * parse(Parser *p, Token t) {
	return new PhraseExpression(t);
    }
};

#endif
