#!/bin/bash

MAX_WIDTH=20
CACHE_OUT_FILE="cache_bench.out"
MEM_OUT_FILE="mem_bench.out"

echo "Running cache misses benchmark..."
for width in $(seq 1 $MAX_WIDTH); do
    echo -ne "$width " >> $CACHE_OUT_FILE
    perf stat -e cache-references,cache-misses ./benchmark $width 2>&1 | grep -o '[0-9]*,[0-9]* %' | grep -o '[0-9]*,[0-9]*' >> $CACHE_OUT_FILE
done

echo "Running memory usage benchmark..."
for width in $(seq 1 $MAX_WIDTH); do
    echo -ne "$width " >> $MEM_OUT_FILE
    valgrind --tool=massif --pages-as-heap=yes --massif-out-file=massif.out ./benchmark $width 10; grep mem_heap_B massif.out | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1 >> $MEM_OUT_FILE
    rm massif.out
done

echo "Running time benchmarks..."
./benchmark