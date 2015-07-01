SFS
-----------------------------------
Project allows you to index files in a particular directory and then query for them.

First clone the repository in the directory to be indexed.

Installation
-----------------------------------
boost: brew install boost
flask: pip install flask

Running
-----------------------------------
cd path_to_sfs_dir
make sfs
python run.py

- click index
- search query (E.G: "term1" OR "term2" AND "term3")

Querying
------------------------------------
There is support for PHRASE queries, OR queries, and AND queries
PHRASE Queries are of the form: "term1 term2"
AND Queries are of the form: (query1 AND query2)
OR Queries are of the form: (query1 OR query2)