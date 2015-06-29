index:
	g++ lib/indexing/index.cpp -lboost_serialization
	./a.out
sfs:
	g++ -O3 lib/SFS.cpp -lboost_serialization -o executables/sfs
clean:
	rm a.out
