#ifndef ANDEXPRESSION
#define ANDEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/ConjunctionIterator.h"
#include <vector>

using namespace std;

class AndExpression : public Expression {
 private:
    vector<Expression *> expressions;
 public:
    AndExpression(Token andToken, Expression *left, Expression *right) {
	expressions.push_back(left);
	if (right->tok == andToken) {
	    expressions.insert(expressions.end(),
			       ((AndExpression *)right)->expressions.begin(),
			       ((AndExpression *)right)->expressions.end());
	    delete (AndExpression *)right;
	}
	else {
	    expressions.push_back(right);
	}
	this->tok = andToken;
    }

    string toString() {
	string res = "(AND";
	for (int i = 0; i < expressions.size(); i++) {
	    res += ", " + expressions[i]->toString();
	}
	res += ")";
	return res;
    }

    void free() {
	for (int i = 0; i < expressions.size(); i++)
	    expressions[i]->free();
	delete this;
    }

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        vector<DocIterator*> iterators;
	for (int i = 0; i < expressions.size(); i++) {
	    iterators.push_back(expressions[i]->getIterator(index));
	}
        return new ConjunctionIterator(iterators);
    }
};

#endif
