SearchFileSystem (SFS)
-----------------------------------
Project allows you to index files in a local directory and then query for them using a different API similar to a search engine.

Setup & Installation
-----------------------------------
First clone the repository in the directory to be indexed. Then install the below dependencies with the following commands.

    boost: brew install boost
    flask: pip install flask

Running
-----------------------------------
First <code>cd</code> to the project directory. Then, run <code>make sfs</code>, followed by <code>python run.py</code>. This will open a web interface with the following two capabilities.
* Click index to generate an index of the selected directory
* Ente a search query (E.G: "term1" OR "term2" AND "term3") 

The results of the commands are output on the page after processing. 

Note that the commands can also be run through the command-line. 
* To index, run <code> project-dir/executables/sfs index </code>
* To query, run <code> project-dir/executables/sfs query "example_query" </code>

Querying
------------------------------------
There is support for PHRASE queries, AND queries, and OR queries. The grammar for the queries are as follows.

* PHRASE Queries are of the form: "term1 term2"
* AND Queries are of the form: (query1 AND query2)
* OR Queries are of the form: (query1 OR query2)

Index Document Selection
------------------------------------
The list of subdirectories and documents that are indexed are specified in the direcotry <code>project-dir/lib/utils/DirectoryFileUtils.h </code>. This file can be modified to incorporate other kinds of documents into the index.
