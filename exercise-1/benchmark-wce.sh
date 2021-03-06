#!/bin/bash


if [ -z "$1" ]; then
	PROGRAMM_NAME="./solver"  		# insert your program here ...
else
	PROGRAMM_NAME=$1													# ... or give the program as parameter to the script
fi

today=$(date +%Y-%m-%d-%H-%M-%S)

LOG="log.txt"									# specify the name of the log file
maxSec=432000									# overall allowed time for the whole script
maxSecPerInstance=300							# allowed time (in seconds) for one instance
maxNotSolved=10									# no of instances the program is allowed to fail to solve. If reached, then the script is aborted

CSV="results-$today.csv"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
run_ce_solver()
{
# 	PROGRAMM_NAME="$1"
# 	LOG=$2
# 	CSV=$3
# 	maxSec=$4
# 	maxSecPerInstance=$5
# 	maxNotSolved=$6
	
	
	FILES=$(ls $1*.dimacs)

	rm -f time.txt

	overallTime=$(date +%s);
	now=$(date +%s);
	elapsed=`expr $now - $overallTime`;
	notSolved=0
	showedHint=0

# 	maxSecPerInstanceHard=$((maxSecPerInstance + 1));

	for f in $FILES
	do
		if [ $elapsed -le $maxSec -a $notSolved -lt $maxNotSolved ]; then
			echo $f >> $LOG
			
			# start everything in a new process group such that we can kill everything if necessary
# 			(setsid /usr/bin/time -f "%e" -a -o time.txt timeout -k $maxSecPerInstance -s 9 $maxSecPerInstance $PROGRAMM_NAME< $f 1> prog_out.txt 2>&1) & PID=$!
# 			(setsid /usr/bin/time -f "%e" -a -o time.txt timeout -k $maxSecPerInstanceHard -s 2 $maxSecPerInstance $PROGRAMM_NAME< $f 1> prog_out.txt 2>&1) & PID=$!
			(setsid /usr/bin/time -f "%e" -a -o time.txt timeout -k 10 -s 2 $maxSecPerInstance $PROGRAMM_NAME< $f 1> prog_out.txt 2>&1) & PID=$!

			# kill processes when exiting this script
			trap "{ kill $PID 2>/dev/null; kill -TERM -- -$(pgrep -P $PID)>/dev/null;}" TERM
			trap "{ kill -9 -$PID 2>/dev/null; kill -9 -- -$(pgrep -P $PID)>/dev/null;}" EXIT

			wait $PID

			# just to be sure: if the process still is around brutally kill it
			kill -0 $PID 2>/dev/null || kill -9 -$PID 2>/dev/null;

			# get n
			n=$(head -1 $f | sed 's/#//' | sed 's/ .*//')

			# get m
# 			m=$(head -1 $f | sed 's/#.* //')
			m=$(( $(grep -v - $f | wc -l) -1 )) # number of lines not containing a "-" minus one since first line denotes number of vertices
			
			# get k (old; k is now computed by verify script; here is only a reset)
			#k=$(grep -ve "^#" prog_out.txt | wc -l)
			k=""
			recursiveSteps=$(grep -e "#recursive steps:" prog_out.txt | sed -e 's/.*recursive steps: \([0-9]*\).*/\1/' )
			#lastK=$(grep -e "last-k:" prog_out.txt | sed -e 's/.*last-k: \([0-9]*\).*/\1/' )
			cat prog_out.txt >> $LOG
			
			# get time
			time=$(cat time.txt);
			
			if [[ $time == "Command terminated by signal 9"* ]] || [[ $time == "Command exited with non-zero status"* ]]; then
				finished=0;
				(( notSolved += 1 ));
				time="";
			else
				finished=1;
			fi
			
			verify="";
			
			if [ "$finished" -eq "1" ]; then
				solFile=$(basename $f .dimacs)
				# the best cost that we found
				ourk=$(cat $f.solution); 
				msg=$($DIR/wce-verify.py $f prog_out.txt)
				if [ $? != 0 ]; then
					verify="verifier.py:  \t $msg";
				else
					k=$msg;
					if [ -n "$ourk" ] && [ "$ourk" -eq "$ourk" ] 2>/dev/null; then
						if [ "$ourk" -eq "$k" ]; then
							verify="correct\t";
						elif [ "$ourk" -gt "$k" ]; then
							verify=">>GOOD COST<<\t$(($ourk-$k))"; 
						else
							verify=">>BAD COST<< \t$(($k-$ourk))";
						fi
					else
						verify="our own cost is weird"
					fi
				fi
			fi
			
			fileNameLong=$(printf '%-40s' "$f");
			
# 			if [ -n "$solNumber" ] && [ -n "$lastK" ] 2>/dev/null; then
# 				lastK=$(($solNumber-$lastK));
# 			fi
# 			solNumber="";
			
			
			echo -e "$fileNameLong\t"$time"\t"$k"\t"$recursiveSteps"\t"$finished"\t"$verify # "\t"$lastK"\t"$solNumber
			echo -e $f"\t"$n"\t"$m"\t"$time"\t"$k"\t"$recursiveSteps"\t"$finished"\t"$verify | sed 's/	/;/g' >> $CSV
			echo "" >> $LOG
			rm -f prog_out.txt
			
			rm -f time.txt

			now=$(date +%s);
			elapsed=`expr $now - $overallTime`;
		else
			if [ $showedHint -eq 0 ]; then
				if [ $notSolved -ge $maxNotSolved ]; then
					echo "$notSolved instances not solved. Script aborted."
				else
					echo "maximal time of $maxSec sec elapsed. Script aborted."
				fi
				showedHint=1;
			fi		
		fi
	done
}

echo "file;vertices;edges;time;solsize;recsteps;finished;verified" > $CSV
## now loop through data set directories
for data in $(find $DIR -mindepth 1 -maxdepth 1 -type d); do
	FILENAME=$(basename $data)
	echo "run $data instances $PROGRAMM_NAME (Tab-separated columns: File, Time in seconds, solution size, recursive steps, finished, solution size verified)"
# 	run_ce_solver "$PROGRAMM_NAME" $LOG $CSV $maxSec $maxSecPerInstance $maxNotSolved $data/
	run_ce_solver $data/
done

echo ""
