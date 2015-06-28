#ifndef EXPRESSION
#define EXPRESSION

#include <iostream>
//#include "../datastructures/DocIterator.h"

using namespace std;

class Expression {
 public:
    Expression() {

    }

    virtual string toString() = 0;
    virtual void free() = 0;
    //virtual DocIterator getIterator() = 0;
};

#endif
