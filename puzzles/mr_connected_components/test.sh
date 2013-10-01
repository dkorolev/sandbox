#!/bin/bash
#
# `make` should be run before invoking this script,
# or just run it via `make test`.

INPUT_FILE=input.txt
BASELINE_OUTPUT_FILE=golden.txt
MAPREDUCE_OUTPUT_FILE=output.txt

for N in 5 10 25 100 ; do
  for Q in 0.05 0.1 0.15 ; do
    for seed in `seq 1 10` ; do
      # Uncomment to see the tests being run.
      # echo ./gen $N $Q $seed 
      ./gen $N $Q $seed >$INPUT_FILE
      ./baseline <$INPUT_FILE >$BASELINE_OUTPUT_FILE
      ./mapreduce <$INPUT_FILE >$MAPREDUCE_OUTPUT_FILE
      if ! diff $BASELINE_OUTPUT_FILE $MAPREDUCE_OUTPUT_FILE ; then
        echo "Error, see $INPUT_FILE, $BASELINE_OUTPUT_FILE and $MAPREDUCE_OUTPUT_FILE for more details."
        exit
      fi
    done
  done
done
rm -f $INPUT_FILE $BASELINE_OUTPUT_FILE $MAPREDUCE_OUTPUT_FILE
echo OK
