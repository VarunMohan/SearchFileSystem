#include <iostream>
#include "Parser.h"
#include "Token.h"
#include "TokenTypes.h"
#include "parselets/PrefixParselet.h"
#include "parselets/InfixParselet.h"
#include "parselets/TermParselet.h"
#include "parselets/PhraseParselet.h"
#include "parselets/OrParselet.h"
#include "parselets/AndParselet.h"
#include "expressions/Expression.h"

using namespace std;

PhraseParselet phraseParselet = PhraseParselet(10);
TermParselet termParselet = TermParselet(10);
AndParselet andParselet = AndParselet(2);
OrParselet orParselet = OrParselet(1);

Parser *getParser() {
    Parser *p = new Parser();
    p->registerPrefixParselet(Token(PHRASE_TOKEN), &phraseParselet);
    p->registerPrefixParselet(Token(TERM_TOKEN), &termParselet);
    p->registerInfixParselet(Token(AND_TOKEN), &andParselet);
    p->registerInfixParselet(Token(OR_TOKEN), &orParselet);
    return p;
}
