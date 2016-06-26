#!/bin/bash

ip="127.0.0.1"
port="4242"
script="./src_client_ai/lua/standard.lua"

if [ $# -gt 0 ] ; then
    ip="$1"
    if [ $# -gt 1 ] ; then
	port="$2"
	if [ $# -gt 2 ] ; then
	    script="$3"
	fi
    fi
fi

for i in `seq 1 10`;
do
    ./zappy_ai -h "$ip" -p "$port" -s "$script" -n toto &
done

cat
