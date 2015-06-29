#ifndef PHRASEEXPRESSION
#define PHRASEEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/TermIterator.h"

using namespace std;

class PhraseExpression : public Expression {
 public:
    PhraseExpression(Token t) {
	tok = t;
    }

    string toString() {
	return "Phrase("+tok.value+")";
    }

    void free() {
	delete this;
    }

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        return new TermIterator(index[tok.value]);
    }

};

#endif
