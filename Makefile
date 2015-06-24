all:
	g++ lib/indexer.cpp -lboost_serialization -o executables/index-files
index-files:
	g++ lib/indexer.cpp -lboost_serialization -o executables/index-files
	./executables/index-files
