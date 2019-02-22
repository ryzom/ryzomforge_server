#!/bin/bash

# the object is to make a launcher script that works with a command file to determine when to launch the application that it is responsible for

DOMAIN=shard

NAME_BASE="$1/$1"
NAME="$1"
mkdir $1
shift

CTRL_FILE=${NAME_BASE}_immediate.launch_ctrl
NEXT_CTRL_FILE=${NAME_BASE}_waiting.launch_ctrl
STATE_FILE=${NAME_BASE}.state
START_COUNTER_FILE=${NAME_BASE}.start_count

EXECUTABLE=$1
shift
CTRL_CMDLINE=$*

echo
echo ---------------------------------------------------------------------------------
echo Starting service launcher
echo ---------------------------------------------------------------------------------
printf "%-16s = " CMDLINE         ; echo $CTRL_CMDLINE
printf "%-16s = " CTRL_FILE       ; echo $CTRL_FILE
printf "%-16s = " NEXT_CTRL_FILE  ; echo $NEXT_CTRL_FILE
printf "%-16s = " STATE_FILE      ; echo $STATE_FILE
echo ---------------------------------------------------------------------------------
echo

# reinit the start counter
echo 0 > $START_COUNTER_FILE
START_COUNTER=0

echo Press ENTER to launch program
while true
do

	# see if the conditions are right to launch the app
	if [ -e $CTRL_FILE ]
		then

		# a control file exists so read it's contents
		CTRL_COMMAND=_$(cat $CTRL_FILE)_

		# do we have a 'launch' command?
		if [ $CTRL_COMMAND = _LAUNCH_ ]
			then

			# update the start counter
			START_COUNTER=$(( $START_COUNTER + 1 ))
			echo $START_COUNTER > $START_COUNTER_FILE

			# big nasty hack to deal with the special cases of ryzom_naming_service and ryzom_admin_service who have badly names cfg files
			for f in ryzom_*cfg
			do
			cp $f $(echo $f | sed "s/ryzom_//")
			done

			# we have a launch command so prepare, launch, wait for exit and do the housekeeping
			echo -----------------------------------------------------------------------
			echo Launching ...
			echo
			printf RUNNING > $STATE_FILE
			echo "" >> /tmp/dump_$NAME.txt
			echo "================" >> /tmp/dump_$NAME.txt
			echo "================" >> /tmp/dump_$NAME.txt
			date >> /tmp/dump_$NAME.txt
			echo "================" >> /tmp/dump_$NAME.txt
			
			$EXECUTABLE $CTRL_CMDLINE

			echo -----------------------------------------------------------------------
			printf STOPPED > $STATE_FILE

			# consume (remove) the control file to allow start once
			rm $CTRL_FILE

			echo Press ENTER to relaunch
		 fi
	fi

	# either we haven't launched the app yet or we have launched and it has exitted
	if [ -e $NEXT_CTRL_FILE ]
	then
		# we have some kind of relaunch directive lined up so deal with it
		mv $NEXT_CTRL_FILE $CTRL_FILE
	else
		printf LAUNCH > $CTRL_FILE
	fi

done

