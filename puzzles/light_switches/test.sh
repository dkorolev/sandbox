#!/bin/bash
#
# `make` should be run before invoking this script,
# or just run it via `make test`.

LIGHTS_FILE=lights.txt
SWITCHES_FILE=switches.txt

# Smoke tests, with golden files.
echo -n "Smoke tests:  "
for i in tests/*.in ; do
  IN=$i
  ANS=${i/in/ans}
  if [ ! -r $IN ] || [ ! -r $ANS ] ; then
    echo "Cannot read $IN or $ANS."
    exit
  fi
  cp $IN $LIGHTS_FILE
  cp $ANS $SWITCHES_FILE
  if ! ./solve $LIGHTS_FILE | diff $SWITCHES_FILE - ; then
    echo "Error, see $LIGHTS_FILE for input and $SWITCHES_FILE for golden output."
    exit
  fi
done
echo "OK"

# Random tests should always be solvable, see http://oeis.org/A076436
# for the dimensions that fit this criterion.
echo -n "Random tests: "
for N in 1 2 3 6 7 8 10 12 13 15 ; do
  for Q in 0.2 0.5 0.8 ; do
    for seed in `seq 1 3` ; do
      # Uncomment to see the tests being run.
      # echo ./gen $N $Q $seed 
      ./gen $N $Q $seed >$LIGHTS_FILE
      if ./solve $LIGHTS_FILE >$SWITCHES_FILE 2>/dev/null ; then
        if ! ./apply $LIGHTS_FILE $SWITCHES_FILE ; then
          echo "Error, see $LIGHTS_FILE and $SWITCHES_FILE for the details."
          exit
        fi
      else
        echo "Error: Must be solvable for N=$N. See $LIGHTS_FILE for details."
        exit
      fi
    done
  done
done
rm -f $LIGHTS_FILE $SWITCHES_FILE
echo OK
