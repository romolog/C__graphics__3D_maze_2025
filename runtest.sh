#! /usr/bin/bash

YEL="\033[0;93m";
GRN="\033[0;92m";
RED="\033[0;91m";
DFT="\033[0m";
NUM=0

echo -e $YEL "\nTESTS:" $DFT;

LOG="./tests/test.log"
SEGF_LOG=./tests/seg_fault.log
echo $(date) >$LOG;
echo -e "--------------------------------\n\n" >$LOG;
echo $(date) >$SEGF_LOG;
echo -e "--------------------------------\n\n" >$SEGF_LOG;

### TEST 1 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D";
TEST="$YEL $NUM:$DFT No args: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL 
	echo -e $TEST
	echo -e $RED "SEG FAULT\n" $DFT
	exit 1
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");
SEG_FAULT=$($CALL 2>$SEGF_LOG; cat $SEGF_LOG | grep fault);
# echo "CHECK RES ASSIGNMENT: |" $RES "|"

echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

# IMPORTANT: 
# OK:		if [[ "$RES" == "Err" ]]; then
# WRONG:	if [[ "$RES" == "Err" ]] then
# 
# OK:		if [[ "$RES" == "Err" ]]; then
# WRONG:	if [["$RES" == "Err"]]; then

echo -en $YEL; 
echo -e $TEST;

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi

### TEST 2 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D INVALID";
TEST="$YEL $NUM:$DFT Invalid arg: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL; 
	echo -e $TEST;
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");

echo >> $LOG;
echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

echo -e $YEL; 
echo -e $TEST;

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi

### TEST 3 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D ./maps/invalid/extention_1.cub3";
TEST="$YEL $NUM:$DFT Invalid file ext: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL; 
	echo -e $TEST;
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");

echo >> $LOG;
echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

echo -e $YEL; 
echo -e $TEST;

if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi


### TEST 4 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D ./maps/invalid/extention_2.cu";
TEST="$YEL $NUM:$DFT Invalid file ext: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL; 
	echo -e $TEST;
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");

echo >> $LOG;
echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

echo -e $YEL; 
echo -e $TEST;

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi

### TEST 5 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D ./maps/invalid/.cub";
TEST="$YEL $NUM:$DFT Invalid file name before extention: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL 
	echo -e $TEST
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");

echo >> $LOG;
echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

echo -e $YEL; 
echo -e $TEST;

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi

### TEST 6 ######################################################################
NUM=$(($NUM + 1));
CALL="./cub3D ./non_existing.cub";
TEST="$YEL $NUM:$DFT Invalid file: $CALL";

{ $CALL; } >& $SEGF_LOG;
SEG_FAULT=$(cat $SEGF_LOG | grep fault);
if [[ "$SEG_FAULT" == *"fault"* ]]; then
	echo -en $YEL 
	echo -e $TEST
	echo -e $RED "SEG FAULT" $DFT
	exit 1;
fi

TARGET=Error;
RES=$($CALL 2>&1 | grep $TARGET);
LEAK=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "in use at exit");
FDS=$(valgrind --leak-check=full --track-fds=yes $CALL 2>&1 | grep "FILE DESCRIPTORS:");

echo >> $LOG;
echo $TEST >> $LOG;
echo -en $YEL "\tprog output: " $DFT >> $LOG;
echo $RES >> $LOG;
echo -en $YEL "\tprog exit code: " $DFT >> $LOG;
./cub3D 2>/dev/null && echo $? >> $LOG || echo $? >> $LOG ;

echo -e $YEL; 
echo -e $TEST;

echo -en $YEL "\tOutput:\t"$DFT;
if [[ "$RES" == "Error" ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$RES" = *"Error"* ]]; then
	echo -e $YEL "OK, but not" $DFT 
else
	echo -e $RED Error $DFT
fi

echo -en $YEL "\tFD:\t"$DFT;
if [[ "$FDS" == *"FILE DESCRIPTORS: 3 open (3 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 2 open (2 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT
elif [[ "$FDS" = *"FILE DESCRIPTORS: 1 open (1 std) at exit." ]]; then
	echo -e $GRN "OK" $DFT	 
else
	echo -e $RED "Error: " $DFT $FDS 
fi

echo -en $YEL "\tLeaks:\t"$DFT;
if [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
	echo -e $GRN "OK" $DFT	
else
	echo -e $RED "Error: " $DFT $LEAK
fi

# echo -en $YEL "\tLeaks:\t"$DFT;
# if [[ "$LEAK" == *"in use at exit: 255 bytes in 5 blocks"* ]]; then
# 	echo -e $GRN "OK" $DFT
# elif [[ "$LEAK" = *"in use at exit: 0 bytes in 0 blocks"* ]]; then
# 	echo -e $GRN "OK" $DFT	
# else
# 	echo -e $RED "Error: " $DFT $LEAK
# fi


# IMPORTANT: 
# suppress stderr and restore it afterwards
# exec 3>&2
# exec 2> /dev/null
# (do stuff where you don't want to see the stderr.)
# exec 2>&3