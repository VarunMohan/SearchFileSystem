#ifndef TERMEXPRESSION
#define TERMEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/TermIterator.h"

using namespace std;

class TermExpression : public Expression {
 private:
    Token tok;
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
        return new TermIterator(index[tok.value]);
    }

};

#endif
