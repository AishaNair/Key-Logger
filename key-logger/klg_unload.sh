#!/bin/bash

RMMOD=`which rmmod`
MODULE=klogger
DEV=klg

echo "Removing module .."
$RMMOD $MODULE.ko || exit 1

rm -f /dev/$DEV

echo "Device /dev/$DEV has been removed"
