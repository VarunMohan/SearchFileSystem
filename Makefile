sfs:
	mkdir -p executables
	g++ -O3 lib/SFS.cpp -lboost_serialization -o executables/sfs
clean:
	rm a.out
