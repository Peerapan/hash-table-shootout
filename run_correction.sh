#!/bin/bash

mkdir build
make test
./build/stl_unordered_map_test
./build/stl_map_test
./build/google_dense_hash_map_test


<<unused
./build/glib_hash_table_test
./build/google_sparse_hash_map_test
unused