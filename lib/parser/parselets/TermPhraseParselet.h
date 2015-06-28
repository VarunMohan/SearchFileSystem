#ifndef TERMPHRASEPARSELET
#define TERMPHRASEPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../expressions/TermPhraseExpression.h"
#include "PrefixParselet.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class TermPhraseParselet : public PrefixParselet {
 public:
    TermPhraseParselet() {

    }

    Expression * parse(Parser *p, Token t) {
	return new TermPhraseExpression(t);
    }
};

#endif
