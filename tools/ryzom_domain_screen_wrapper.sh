#!/bin/bash

CMD=$1
DOMAIN=shard

if [[ ! -z "$2" ]]
then
	SHARD_RUN_PATH=$2
else
	SHARD_RUN_PATH=$SHARD_PATH
fi

if [ "x$CMD" = "x" ]
then
	echo
	echo Screen sessions currently running:
	screen -list
	echo
	echo "Commands:"
	echo "  'start' to start the shard"
	echo "  'stop'  to stop the ${DOMAIN}"
	echo "  'join'  to join the ${DOMAIN}'s screen session"
	echo "  'share' to join the screen session in shared mode"
	echo "  'state' to view state information for the ${DOMAIN}"
	echo
	printf "Enter a command: "
	read CMD
fi

if [ "$CMD" = "stop" ]
then
	if [ $(screen -list | grep \\\.${DOMAIN} | wc -l) != 1 ]
	then
		echo Cannot stop domain \'${DOMAIN}\' because no screen by that name appears to be running
		screen -list
	else
		screen -d -r $(screen -list | grep \\\.${DOMAIN}| sed 's/(.*)//') -X quit> /dev/null
		cd $SHARD_PATH
		rm -v */*.state
		rm -v */*launch_ctrl ./global.launch_ctrl
	fi
fi

STARTARGS=
if [ "$CMD" = "batchstart" ]
then
	STARTARGS="-d -m"
	CMD="start"
fi

if [ "$CMD" = "start" ]
then

	cd $SHARD_RUN_PATH/run

	ulimit -c unlimited
	screen -wipe > /dev/null
	if [ $( screen -list | grep \\\.${DOMAIN} | wc -w ) != 0 ]
	then
		echo Cannot start domain \'${DOMAIN}\' because this domain is already started
		screen -list | grep $DOMAIN
	else
		#sorbot_tell :relaxed: Shard is launching. Should be available in a few minutes :relaxed:
		echo "screen $STARTARGS -S ${DOMAIN} -c $SHARD_RUN_P$SHARD_RUN_PATHATH/tools/${DOMAIN}.screen.rc"
		SHARD_PATH=$SHARD_RUN_PATH screen $STARTARGS -S ${DOMAIN} -c $SHARD_RUN_PATH/tools/${DOMAIN}.screen.rc
	fi
fi

if [ "$CMD" = "join" ]
then
	if [ $(screen -list | grep \\\.${DOMAIN} | wc -l) != 1 ]
	then
	echo Cannot join domain \'${DOMAIN}\' because no screen by that name appears to be running
	screen -list
	else
	screen -r $(screen -list | grep \\\.${DOMAIN}| sed 's/(.*)//')
	fi
fi

if [ "$CMD" = "share" ]
then
	if [ $(screen -list | grep \\\.${DOMAIN} | wc -l) != 1 ]
	then
	echo Cannot join domain \'${DOMAIN}\' because no screen by that name appears to be running
	screen -list
	else
	screen -r -x $(screen -list | grep \\\.${DOMAIN}| sed 's/(.*)//')
	fi
fi

if [ "$CMD" = "state" ]
then
	echo State of domain ${DOMAIN}:
	if [ $(echo */*.state) = "*/*.state" ]
	then
		echo - No state files found
	else
		grep RUNNING *state
	fi
fi
