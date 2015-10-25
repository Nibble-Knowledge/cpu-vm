#!/bin/bash
if [ -n "$(grep -q BCM2708 /proc/cpuinfo && echo "ISPI")" ]
then
	echo -n "-DRPI"
fi
