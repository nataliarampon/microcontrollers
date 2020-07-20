#!/bin/bash
if [ -z "$1" ] ; then
	echo "usage: plot.sh <datafile>"
	exit -1;
fi;
gnuplot -p << EOF
plot "$1" using 5:1 with lines title "rotary", \
	"$1" using 5:2 with lines title "light", \
	"$1" using 5:3 with lines title "sound", \
	"$1" using 5:4 with lines title "temperature"
EOF
