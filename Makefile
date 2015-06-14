#make all

all: build/glib_hash_table build/stl_unordered_map build/boost_unordered_map build/glib_hash_table build/stl_unordered_map build/google_sparse_hash_map build/google_dense_hash_map build/kyotocabinet_hash build/kyotocabinet_stash build/rockc build/leveldb build/postgresql build/google_dense_hash_map_bulk build/google_sparse_hash_map_bulk build/stl_unordered_map_bulk build/kyotocabinet_bulk build/rocksdb_bulk build/postgresql_bulk
test: build/glib_hash_table_test build/stl_map_test build/stl_unordered_map_test build/google_sparse_hash_map_test build/google_dense_hash_map_test

#make insert/delete data test

build/glib_hash_table: src/glib_hash_table.c Makefile src/template.c
	gcc -ggdb -O2 -lm `pkg-config --cflags --libs glib-2.0` src/glib_hash_table.c -o build/glib_hash_table

build/stl_unordered_map: src/stl_unordered_map.cc Makefile src/template.c
	g++ -O2 -lm src/stl_unordered_map.cc -o build/stl_unordered_map -std=c++0x

build/boost_unordered_map: src/boost_unordered_map.cc Makefile src/template.c
	g++ -O2 -lm src/boost_unordered_map.cc -o build/boost_unordered_map

build/google_sparse_hash_map: src/google_sparse_hash_map.cc Makefile src/template.c
	g++ -O2 -lm src/google_sparse_hash_map.cc -o build/google_sparse_hash_map

build/google_dense_hash_map: src/google_dense_hash_map.cc Makefile src/template.c
	g++ -O2 -lm src/google_dense_hash_map.cc -o build/google_dense_hash_map

build/qt_qhash: src/qt_qhash.cc Makefile src/template.c
	g++ -O2 -lm `pkg-config --cflags --libs QtCore` src/qt_qhash.cc -o build/qt_qhash

build/python_dict: src/python_dict.c Makefile src/template.c
	gcc -O2 -lm -I/usr/include/python2.6 -lpython2.6 src/python_dict.c -o build/python_dict

build/ruby_hash: src/ruby_hash.c Makefile src/template.c
	gcc -O2 -lm -I/usr/include/ruby-1.9.0 -I /usr/include/ruby-1.9.0/x86_64-linux -lruby1.9 src/ruby_hash.c -o build/ruby_hash

build/kyotocabinet_hash: src/kyotocabinet_hash.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_hash.cc -o build/kyotocabinet_hash -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lc

build/kyotocabinet_stash: src/kyotocabinet_stash.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_stash.cc -o build/kyotocabinet_stash -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lc

build/rockc: src/rocksdb.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/rocksdb.cc -o build/rockc /usr/local/lib/librocksdb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/leveldb: src/leveldb.cc Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/leveldb.cc -o build/leveldb /usr/local/lib/libleveldb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/postgresql: src/postgresql.cpp Makefile src/template.c
	g++ -O2 -lm -std=c++11 src/postgresql.cpp -o build/postgresql -lpqxx -lpq

#make bulk test

build/google_dense_hash_map_bulk: src/google_dense_hash_map_bulk.cc Makefile src/template_bulk.c
	g++ -O2 -lm src/google_dense_hash_map_bulk.cc -o build/google_dense_hash_map_bulk

build/google_sparse_hash_map_bulk: src/google_sparse_hash_map_bulk.cc Makefile src/template_bulk.c
	g++ -O2 -lm src/google_sparse_hash_map_bulk.cc -o build/google_sparse_hash_map_bulk

build/stl_unordered_map_bulk: src/stl_unordered_map_bulk.cc Makefile src/template_bulk.c
	g++ -O2 -lm src/stl_unordered_map_bulk.cc -o build/stl_unordered_map_bulk -std=c++0x

build/kyotocabinet_bulk: src/kyotocabinet_stash_bulk.cc Makefile src/template_bulk.c
	g++ -std=c++11 -I/usr/local/include src/kyotocabinet_stash_bulk.cc -o build/kyotocabinet_bulk -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lm -lc

build/rocksdb_bulk: src/rockdb_bulk.cc Makefile src/template_bulk.c
	g++ -O2 -lm -std=c++11 src/rockdb_bulk.cc -o build/rocksdb_bulk /usr/local/lib/librocksdb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/postgresql_bulk: src/postgresql_bulk.cpp Makefile src/template_bulk.c
	g++ -O2 -lm -std=c++11 src/postgresql_bulk.cpp -o build/postgresql_bulk -lpqxx -lpq

#make access/update data test

build/glib_hash_table_access: src/glib_hash_table_access.c Makefile src/template_access.c
	gcc -ggdb -O2 -lm `pkg-config --cflags --libs glib-2.0` src/glib_hash_table_access.c -o build/glib_hash_table_access

build/stl_unordered_map_access: src/stl_unordered_map_access.cc Makefile src/template_access.c
	g++ -O2 -lm src/stl_unordered_map_access.cc -o build/stl_unordered_map_access -std=c++0x

build/google_sparse_hash_map_access: src/google_sparse_hash_map_access.cc Makefile src/template_access.c
	g++ -O2 -lm src/google_sparse_hash_map_access.cc -o build/google_sparse_hash_map_access

build/google_dense_hash_map_access: src/google_dense_hash_map_access.cc Makefile src/template_access.c
	g++ -O2 -lm src/google_dense_hash_map_access.cc -o build/google_dense_hash_map_access

build/qt_qhash_access: src/qt_qhash.cc Makefile src/template_access.c
	g++ -O2 -lm `pkg-config --cflags --libs QtCore` src/qt_qhash.cc -o build/qt_qhash

build/kyotocabinet_hash_access: src/kyotocabinet_hash_access.cc Makefile src/template_access.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_hash_access.cc -o build/kyotocabinet_hash_access -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lm -lc

build/kyotocabinet_stash_access: src/kyotocabinet_hash_access.cc Makefile src/template_access.c
	g++ -O2 -lm -std=c++11 src/kyotocabinet_stash_access.cc -o build/kyotocabinet_stash_access -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lm -lc

build/rockc_access: src/rocksdb_access.cc Makefile src/template_access.c
	g++ -O2 -lm -std=c++11 src/rocksdb_access.cc -o build/rockc_access /usr/local/lib/librocksdb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/leveldb_access: src/leveldb_access.cc Makefile src/template_access.c
	g++ -O2 -lm -std=c++11 src/leveldb_access.cc -o build/leveldb_access /usr/local/lib/libleveldb.a -I/usr/local/include -lstdc++ -lpthread -lrt -lz -lbz2

build/postgresql_access: src/postgresql_access.cpp Makefile src/template_access.c
	g++ -O2 -lm -std=c++11 src/postgresql_access.cpp -o build/postgresql_access -lpqxx -lpq

#make hash function

build/hash_function: hash_function.cpp
	g++ -O2 -lm -lcryptopp hash_function.cpp -o build/hash_function

#make correction test

build/glib_hash_table_test: Makefile
	g++ -ggdb -lm `pkg-config --cflags --libs glib-2.0` data_correction/glib_hash_table_test.cpp -o build/glib_hash_table_test

build/stl_unordered_map_test: Makefile
	g++ -lm data_correction/stl_unordered_map_test.cpp -o build/stl_unordered_map_test -std=c++0x

build/stl_map_test: Makefile
	g++ -lm data_correction/stl_map_test.cpp -o build/stl_map_test -std=c++0x

build/google_sparse_hash_map_test: Makefile
	g++ -lm data_correction/google_sparse_hash_map_test.cpp -o build/google_sparse_hash_map_test -std=c++0x

build/google_dense_hash_map_test: Makefile
	g++ -lm data_correction/google_dense_hash_map_test.cpp -o build/google_dense_hash_map_test -std=c++0x