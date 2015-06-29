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

int main(void) {
    PhraseParselet phraseParselet = PhraseParselet(10);
    TermParselet termParselet = TermParselet(10);
    AndParselet andParselet = AndParselet(2);
    OrParselet orParselet = OrParselet(1);
    Parser p;
    p.registerPrefixParselet(Token(PHRASE_TOKEN), &phraseParselet);
    p.registerPrefixParselet(Token(TERM_TOKEN), &termParselet);
    p.registerInfixParselet(Token(AND_TOKEN), &andParselet);
    p.registerInfixParselet(Token(OR_TOKEN), &orParselet);
    //Expression *e = p.parseRawString("  \"HELLO WORLD\" AND    \"TESTING\" OR  \"blah\"  AND \"blah2\"");
    Expression *e = p.parseRawString("\"A\" OR \"B\" OR \"C\" OR \"D\"");
    cout << e->toString() << endl;
    e->free();
}
