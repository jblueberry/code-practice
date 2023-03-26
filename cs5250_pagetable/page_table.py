s = '''
559a11bb3000-559a11bb5000 r--p 00000000 103:05 1835157                   /usr/bin/cat
559a11bb5000-559a11bb9000 r-xp 00002000 103:05 1835157                   /usr/bin/cat
559a11bb9000-559a11bbb000 r--p 00006000 103:05 1835157                   /usr/bin/cat
559a11bbb000-559a11bbc000 r--p 00007000 103:05 1835157                   /usr/bin/cat
559a11bbc000-559a11bbd000 rw-p 00008000 103:05 1835157                   /usr/bin/cat
559a139d7000-559a139f8000 rw-p 00000000 00:00 0                          [ heap ]
7f0e27400000-7f0e281e7000 r--p 00000000 103:05 1840467                   /usr/lib/locale/locale-archive
7f0e28200000-7f0e28228000 r--p 00000000 103:05 1841592                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f0e28228000-7f0e283bd000 r-xp 00028000 103:05 1841592                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f0e283bd000-7f0e28415000 r--p 001bd000 103:05 1841592                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f0e28415000-7f0e28419000 r--p 00214000 103:05 1841592                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f0e28419000-7f0e2841b000 rw-p 00218000 103:05 1841592                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f0e2841b000-7f0e28428000 rw-p 00000000 00:00 0 
7f0e284cf000-7f0e284f4000 rw-p 00000000 00:00 0 
7f0e28509000-7f0e2850b000 rw-p 00000000 00:00 0 
7f0e2850b000-7f0e2850d000 r--p 00000000 103:05 1841255                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f0e2850d000-7f0e28537000 r-xp 00002000 103:05 1841255                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f0e28537000-7f0e28542000 r--p 0002c000 103:05 1841255                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f0e28543000-7f0e28545000 r--p 00037000 103:05 1841255                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f0e28545000-7f0e28547000 rw-p 00039000 103:05 1841255                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffc92159000-7ffc9217a000 rw-p 00000000 00:00 0                          [ stack ]
7ffc921a6000-7ffc921aa000 r--p 00000000 00:00 0                          [ vvar ]
7ffc921aa000-7ffc921ac000 r-xp 00000000 00:00 0                          [ vdso ]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [ vsyscall ]
'''
lines = s.split('\n')
count = 0
for line in lines:
    if line == '':
        continue
    count += 1

print(count)
for line in lines:
    if line == '':
        continue
    strs = line.split(' ')
    first = strs[0].split('-')
    print(first[0], first[1])