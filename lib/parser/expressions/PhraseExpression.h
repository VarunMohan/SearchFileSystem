#ifndef PHRASEEXPRESSION
#define PHRASEEXPRESSION

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <string>
#include <iterator>
#include "../Token.h"
#include "Expression.h"

#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/TermIterator.h"
#include "../../datastructures/PhraseIterator.h"
#include "../../datastructures/EmptyIterator.h"

using namespace std;

class PhraseExpression : public Expression {
 private:
    Token tok;
    vector<string> terms;
    vector<int> offsets;
    set<string> stopWords;

    void splitPhrase() {
        string phrase = tok.value;
        istringstream iss(phrase);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(terms));
        for (int i = 0; i < terms.size(); i++) {
            std::transform(terms[i].begin(), terms[i].end(), terms[i].begin(), ::tolower);
            if (i >= 1) offsets.push_back(1);
        }
    }

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
        splitPhrase();
        vector<TermIterator*> termIterators;
        for (int i = 0; i < terms.size(); i++) {
            if (index.count(terms[i]) == 0) return new EmptyIterator();
            termIterators.push_back(new TermIterator(index[terms[i]]));
        }
        return new PhraseIterator(termIterators, offsets);
    }

};

#endif
