: '
 * build.sh
 * @author Omar Elhogaraty 101302440
 * @author Ahmad El-Jabi 101303269
'
#This is to save time typing for compiling, running, and killing (it's tedious!!!).
#Do not run this file, just copy and paste into bash/zsh terminal whatever you want to compile, run, or kill.

gcc Q1_P2_101302440_101303269.cpp -o Q1_P2_101302440_101303269

gcc Q2_P2_Process1_101302440_101303269.cpp -o Q2_P2_Process1_101302440_101303269
gcc Q2_P2_Process2_101302440_101303269.cpp -o Q2_P2_Process2_101302440_101303269

gcc Q3_P2_Process1_101302440_101303269.cpp -o Q3_P2_Process1_101302440_101303269
gcc Q3_P2_Process2_101302440_101303269.cpp -o Q3_P2_Process2_101302440_101303269

gcc Q4_P2_Process1_101302440_101303269.cpp -o Q4_P2_Process1_101302440_101303269
gcc Q4_P2_Process2_101302440_101303269.cpp -o Q4_P2_Process2_101302440_101303269

gcc Q5_P2_Process1_101302440_101303269.cpp -o Q5_P2_Process1_101302440_101303269
gcc Q2_P2_Process2_101302440_101303269.cpp -o Q5_P2_Process2_101302440_101303269

./Q1_P2_101302440_101303269

./Q2_P2_Process1_101302440_101303269
./Q2_P2_Process2_101302440_101303269

./Q3_P2_Process1_101302440_101303269
./Q3_P2_Process2_101302440_101303269

./Q4_P2_Process1_101302440_101303269
./Q4_P2_Process2_101302440_101303269

./Q5_P2_Process1_101302440_101303269
./Q5_P2_Process2_101302440_101303269

kill "pid1" "pid2"
#or
pkill Q1_P2
pkill Q2_P2
pkill Q3_P2
pkill Q4_P2
pkill Q5_P2
#or
pkill -f Q