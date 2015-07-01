SearchFileSystem (SFS)
-----------------------------------
Project allows you to index files in a particular directory and then query for them.

Setup & Installation
-----------------------------------
First clone the repository in the directory to be indexed. Then install the below dependencies with the following commands.

boost: brew install boost

flask: pip install flask

Running
-----------------------------------
Run "make sfs" in the project directory and then run the command "python run.py". This will open a web interface with the following two capabilities.

-> click index to generate an index of the selected directory

-> search query (E.G: "term1" OR "term2" AND "term3") 

The results of the commands are output on the page after processing.

Querying
------------------------------------
There is support for PHRASE queries, OR queries, and AND queries. The grammar for the queries are as follows.

PHRASE Queries are of the form: "term1 term2"

AND Queries are of the form: (query1 AND query2)

OR Queries are of the form: (query1 OR query2)