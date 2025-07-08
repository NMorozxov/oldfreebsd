#!/bin/sh

case "$1" in
	start)
		/usr/local/sbin/logf.rules.manual
		;;
	stop)
		;;
	*)
		echo ""
		echo "Usage: `basename $0` { start | stop }"
		echo ""
		exit 64
		;;
esac
