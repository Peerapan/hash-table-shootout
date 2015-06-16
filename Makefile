#make all

all:
	build/glib_hash_table
	build/google_dense_hash_map
	build/google_sparse_hash_map
	build/stl_unordered_map
	build/kyotocabinet_stash
	build/kyotocabinet_hash
	build/boost_unordered_map
	build/qt_qhash
	build/python_dict
	build/ruby_hash
	build/rockc
	build/leveldb
	build/postgresql
test:
	build/glib_hash_table_test
	build/stl_map_test
	build/stl_unordered_map_test
	build/google_dense_hash_map_test
	build/google_sparse_hash_map_test

#make insert/delete data test

build/glib_hash_table: src/glib_hash_table.c Makefile src/template.c
	gcc -O2 -lm -std=c++11 -ggdb `pkg-config --cflags --libs glib-2.0` src/glib_hash_table.c -o build/glib_hash_table

build/google_dense_hash_map: src/google_dense_hash_map.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/google_dense_hash_map.cc -o build/google_dense_hash_map

build/google_sparse_hash_map: src/google_sparse_hash_map.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/google_sparse_hash_map.cc -o build/google_sparse_hash_map

build/stl_unordered_map: src/stl_unordered_map.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/stl_unordered_map.cc -o build/stl_unordered_map -std=c++0x

build/kyotocabinet_stash: src/kyotocabinet_stash.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_stash.cc -o build/kyotocabinet_stash -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lc

build/kyotocabinet_hash: src/kyotocabinet_hash.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_hash.cc -o build/kyotocabinet_hash -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lc

build/boost_unordered_map: src/boost_unordered_map.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/boost_unordered_map.cc -o build/boost_unordered_map

build/qt_qhash: src/qt_qhash.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 `pkg-config --cflags --libs QtCore` src/qt_qhash.cc -o build/qt_qhash

build/python_dict: src/python_dict.c Makefile src/template.c
	gcc -O2 -lm -std=c++11 -I/usr/include/python2.6 -lpython2.6 src/python_dict.c -o build/python_dict

build/ruby_hash: src/ruby_hash.c Makefile src/template.c
	gcc -O2 -lm -std=c++11 -I/usr/include/ruby-1.9.0 -I /usr/include/ruby-1.9.0/x86_64-linux -lruby1.9 src/ruby_hash.c -o build/ruby_hash

build/rocksdb: src/rocksdb.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/rocksdb.cc -o build/rocksdb /usr/local/lib/librocksdb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/leveldb: src/leveldb.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/leveldb.cc -o build/leveldb /usr/local/lib/libleveldb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/postgresql: src/postgresql.cpp Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/postgresql.cc -o build/postgresql -lpqxx -lpq

#make hash function

build/hash_function: hash_function.cpp
	g++ -O2 -lm -lcryptopp hash_function.cpp -o build/hash_function

#make correction test

build/glib_hash_table_test: Makefile
	g++ -O2 -ggdb -lm `pkg-config --cflags --libs glib-2.0` data_correction/glib_hash_table_test.cpp -o build/glib_hash_table_test

build/stl_unordered_map_test: Makefile
	g++ -O2 -lm data_correction/stl_unordered_map_test.cpp -o build/stl_unordered_map_test -std=c++0x

build/stl_map_test: Makefile
	g++ -O2 -lm data_correction/stl_map_test.cpp -o build/stl_map_test -std=c++0x

build/google_sparse_hash_map_test: Makefile
	g++ -O2 -lm data_correction/google_sparse_hash_map_test.cpp -o build/google_sparse_hash_map_test -std=c++0x

build/google_dense_hash_map_test: Makefile
	g++ -O2 -lm data_correction/google_dense_hash_map_test.cpp -o build/google_dense_hash_map_test -std=c++0x