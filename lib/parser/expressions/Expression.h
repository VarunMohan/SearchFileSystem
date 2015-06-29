#ifndef EXPRESSION
#define EXPRESSION

#include <iostream>
#include <map>
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../Token.h"

using namespace std;

class Expression {
 public:
    Token tok;

    Expression() {

    }

    virtual string toString() = 0;
    virtual void free() = 0;
    virtual DocIterator* getIterator(map<string, PostingList>& index) = 0;
};

#endif
