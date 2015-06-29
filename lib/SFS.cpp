#include <iostream>
#include "indexing/index.cpp"
#include "parser/QueryParser.cpp"

using namespace std;

void index() {
    index_files();
    cout << endl;
    cout << "SERIALIZING INDEX" << endl;
    serialize_index("serialized_inv_index");
    cout << "SERIALIZING DOCUMENT MAPPING" << endl;
    serialize_doc_id_map("serialized_doc_id_map");
    cout << "INDEXING COMPLETE" << endl;
    print_index();
}

void search(int argc, char *argv[]) {
    map<string, PostingList> index = deserialize_index("serialized_inv_index");
    vector<string> docidmaps = deserialize_doc_id_map("serialized_doc_id_map");
    string query = "";
    for (int i = 2; i < argc; i++)
	query += string(argv[i]) + " ";
    Parser *p = getParser();
    Expression *e = p->parseRawString(query);
    DocIterator *it = e->getIterator(index);
    int curDocId;
    while ((curDocId = it->getDocID()) != DocIterator::MAX_DOCID) {
	cout << docidmaps[curDocId] << endl;
	it->next();
    }
    e->free();
    delete p;
}

void help() {
    cout << "Usage: sfs [index] [search \"phr1\" OR \"phr2\" AND ...]" << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) help();
    string firstArg(argv[1]);
    if (firstArg == "index") index();
    else if (firstArg == "search") search(argc, argv);
    else help();
}
