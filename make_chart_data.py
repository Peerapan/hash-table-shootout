import sys, json

lines = [ line.strip() for line in sys.stdin if line.strip() ]

by_benchtype = {}

for line in lines:
    benchtype, nkeys, program, nbytes, runtime = line.split(',')
    nkeys = int(nkeys)
    nbytes = int(nbytes)
    runtime = float(runtime)

    by_benchtype.setdefault("%s-runtime" % benchtype, {}).setdefault(program, []).append([nkeys, runtime])
    if benchtype.startswith('sequential'):
        by_benchtype.setdefault("%s-memory"  % benchtype, {}).setdefault(program, []).append([nkeys, nbytes])

proper_names = {
	'glib_hash_table': 'GLib Hash Table',
	'google_dense_hash_map': 'Google Dense Hash Map',
	'google_sparse_hash_map': 'Google Sparse Hash Map',
	'stl_unordered_map': 'Std::unordered_map',
	'kyotocabinet_stash': 'Kyotocabinet StashDB',
	'kyotocabinet_hash': 'Kyotocabinet HashDB',
	'boost_unordered_map': 'Boost:unordered_map',
	'qt_qhash': 'Qt Hash',
	'python_dict': 'Python Dictionary',
	'ruby_hash': 'Ruby Hash',
	'rocksdb' : 'Rocksdb',
	'leveldb' : 'Leveldb',
	'postgresql' : 'Postgresql'
}

# do them in the desired order to make the legend not overlap the chart data
# too much
program_slugs = [
	 'glib_hash_table',
	 'google_dense_hash_map',
	 'google_sparse_hash_map',
	 'stl_unordered_map',
	 'kyotocabinet_stash',
	 'kyotocabinet_hash',
	 'boost_unordered_map',
	 'qt_qhash',
	 'python_dict',
	 'ruby_hash',
	 'rocksdb',
	 'leveldb',
	 'postgresql'
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
