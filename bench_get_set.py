import sys, os, subprocess, signal

programs = [
            #'glib_hash_table_access',
            #'stl_unordered_map_access',
            #'google_sparse_hash_map_access',
            #'google_dense_hash_map_access',
            #'kyotocabinet_stash_access',
            #'rockc_access',
            #'leveldb_access',
            #'postgresql_access',
            ]

minkeys  = 20*100
maxkeys  = 40*100
interval =  5*100
best_out_of = 1

# for the final run, use this:
#minkeys  =  2*1000*1000
#maxkeys  = 40*1000*1000
#interval =  2*1000*1000
#best_out_of = 3
# and use nice/ionice
# and shut down to the console
# and swapoff any swap files/partitions

outfile = open('output', 'w')

if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = ('randomgetgood','randomgetbad','randomstringgetgood','randomstringgetbad','randomset','randomstringsetbest')

for benchtype in benchtypes:
    nkeys = minkeys
    while nkeys <= maxkeys:
        for program in programs:
            fastest_attempt = 1000000
            fastest_attempt_data = ''
            
            for attempt in range(best_out_of):
                print 'Start a Process'
                proc = subprocess.Popen(['./build/'+program, str(nkeys), benchtype], stdout=subprocess.PIPE)
                
                # wait for the program to fill up memory and spit out its "ready" message
                try:
                    runtime = float(proc.stdout.readline().strip())
                except:
                    runtime = 0
                
                ps_proc = subprocess.Popen(['ps up %d | tail -n1' % proc.pid], shell=True, stdout=subprocess.PIPE)
                nbytes = int(ps_proc.stdout.read().split()[4]) * 1024
                print 'Wait for process Finish'
                ps_proc.wait()
                
                os.kill(proc.pid, signal.SIGKILL)
                print 'Wait for process Kill'
                proc.wait()
                
                if nbytes and runtime: # otherwise it crashed
                    line = ','.join(map(str, [benchtype, nkeys, program, nbytes, "%0.6f" % runtime]))
                    
                    if runtime < fastest_attempt:
                        fastest_attempt = runtime
                        fastest_attempt_data = line
    
            if fastest_attempt != 1000000:
                print >> outfile, fastest_attempt_data
                print fastest_attempt_data
                    
        nkeys += interval
