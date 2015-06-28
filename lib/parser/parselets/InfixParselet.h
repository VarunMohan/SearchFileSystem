#ifndef INFIXPARSELET
#define INFIXPARSELET

#include <iostream>
#include "../expressions/Expression.h"
#include "../Token.h"
#include "../Parser.h"

using namespace std;

class Parser;

class InfixParselet {
 public:
    InfixParselet() {

    }

    virtual Expression * parse(Parser *p, Expression *left, Token t) = 0;
};

#endif
