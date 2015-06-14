import sys, json

lines = [ line.strip() for line in sys.stdin if line.strip() ]

by_benchtype = {}

for line in lines:
    benchtype, nkeys, program, nbytes, runtime = line.split(',')
    nkeys = int(nkeys)
    nbytes = int(nbytes)
    runtime = float(runtime)

    by_benchtype.setdefault("%s-runtime" % benchtype, {}).setdefault(program, []).append([nkeys, runtime])
    by_benchtype.setdefault("%s-memory"  % benchtype, {}).setdefault(program, []).append([nkeys, nbytes])

proper_names = {
#'glib_hash_table_access': 'Glib GHashTable',
#'stl_unordered_map_access': 'GCC std::unordered_map',
#'google_sparse_hash_map_access': 'Google sparsehash sparse_hash_map',
#'google_dense_hash_map_access': 'Google sparsehash dense_hash_map',
#'kyotocabinet_stash_access': 'Kyotocabinet StashDB',
#'rockc_access' : 'rocksdb',
#'leveldb_access' : 'leveldb',
'postgresql_access' : 'postgresql',
}

# do them in the desired order to make the legend not overlap the chart data
# too much
program_slugs = [
				 #	'glib_hash_table_access',
                 #'stl_unordered_map_access',
                 #'google_sparse_hash_map_access',
                 #'google_dense_hash_map_access',
				 #'kyotocabinet_stash_access',
                 #'rockc_access',
                 #'leveldb_access',
                 'postgresql_access',
]

chart_data = {}

for i, (benchtype, programs) in enumerate(by_benchtype.items()):
    chart_data[benchtype] = []
    for j, program in enumerate(program_slugs):
        data = programs[program]
        chart_data[benchtype].append({
            'label': proper_names[program],
            'data': [],
        })

        for k, (nkeys, value) in enumerate(data):
            chart_data[benchtype][-1]['data'].append([nkeys, value])

print 'chart_data = ' + json.dumps(chart_data)
