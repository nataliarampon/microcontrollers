#!/bin/bash
boardId=`cat /sys/devices/virtual/dmi/id/board_name`
case $boardId in
	"Galileo")
		GPIO=3
	;;
	"GalileoGen2")
		GPIO=7
	;;
esac

while true ; do
	echo -n "0" > /sys/class/gpio/gpio$GPIO/value
	sleep 1
	echo -n "1" > /sys/class/gpio/gpio$GPIO/value
	sleep 1
done
