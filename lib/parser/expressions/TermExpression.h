#ifndef TERMEXPRESSION
#define TERMEXPRESSION

#include <iostream>
#include <map>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/TermIterator.h"
#include "../../datastructures/EmptyIterator.h"

using namespace std;

class TermExpression : public Expression {
 public:
    TermExpression(Token t) {
	tok = t;
    }

    string toString() {
	return "Term("+tok.value+")";
    }

    void free() {
	delete this;
    }

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        if (index.count(tok.value) == 0) {
            return new EmptyIterator();
        }
        return new TermIterator(index[tok.value]);
    }

};

#endif
