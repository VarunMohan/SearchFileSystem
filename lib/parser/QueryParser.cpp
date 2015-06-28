#include <iostream>
#include "Parser.h"
#include "Token.h"
#include "TokenTypes.h"
#include "parselets/PrefixParselet.h"
#include "parselets/InfixParselet.h"
#include "parselets/TermPhraseParselet.h"
#include "parselets/OrParselet.h"
#include "parselets/AndParselet.h"
#include "expressions/Expression.h"

using namespace std;

int main(void) {
    TermPhraseParselet termPhraseParselet = TermPhraseParselet();
    AndParselet andParselet = AndParselet();
    OrParselet orParselet = OrParselet();
    Parser p;
    p.registerPrefixParselet(Token(PHRASE_TOKEN), &termPhraseParselet);
    p.registerInfixParselet(Token(AND_TOKEN), &andParselet);
    p.registerInfixParselet(Token(OR_TOKEN), &orParselet);
    Expression *e = p.parseRawString("filler");
    cout << e->toString() << endl;
    e->free();
}
