#!/bin/bash
# Usage:
# run_benchmarks.sh [variants] [configure.optflags=] [configure.compiler=]
# (the script hands off all arguments to the port command)

set -x
port -novk configure libcxx "$@" 1>&2
set +x

WDIR=`port work libcxx`
BDIR=${WDIR}/build

CWD=`pwd`

cd ${BDIR}
make -w cxx-benchmarks 1>&2

cd bin

for bm in *.libcxx.out ;do
    bm="`basename ${bm} .libcxx.out`"
    echo "### Benchmark \"${bm}\""
    for version in libcxx native ;do
        if [ ${version} = "libcxx" ] ;then
            echo -e "###\tLibC++:"
        else
            echo -e "###\tLibStdc++ (native):"
        fi
        # run a 1st time discarding results
        ${bm}.${version}.out 2>&1 > /dev/null
        # show the results of the 2nd call, ensuring that the "time"
        # data is appended to the same stream.
        (time ${bm}.${version}.out) 2>&1
    done
done
