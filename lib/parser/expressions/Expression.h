#ifndef EXPRESSION
#define EXPRESSION

#include <iostream>

using namespace std;

class Expression {
 public:
    Expression() {

    }

    virtual string toString() = 0;
    virtual void free() = 0;
};

#endif
