#!/bin/sh
for file in tests/*.sp2020
do
	./comp "${file}"
done
exit 0

