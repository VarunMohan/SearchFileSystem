#ifndef PREFIXPARSELET
#define PREFIXPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class PrefixParselet {
 public:
    PrefixParselet() {

    }

    virtual Expression * parse(Parser *p, Token t) = 0;
};

#endif
