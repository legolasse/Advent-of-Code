# Advent-of-Code-2022

For day XX, program PXX.cpp is created with top.cpp being common for all days.

Test files are then named PXXY.txt, Y=a,b,c,d,e,etc., so that compile and testing is done using:

cat top.cpp PXX.cpp > tmp.cpp && g++ -Wall tmp.cpp -o a.bin && ./a.bin < PXXY.txt
