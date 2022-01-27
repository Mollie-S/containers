#!/bin/bash
green=`tput setaf 2`
reset=`tput sgr0`
echo "${green}Compiling files for running ft_containers tests... ${reset}"
make -s
echo "${green}Compiling files for running std_containers tests... ${reset}"
make -s std
cd build  && mkdir output

echo "${green}Running ft_containers_tests... ${reset}"
echo "Timing:"
time ./ft_containers_tests > output/ft.txt
echo ""
echo "You will find the tests output in 'build/output/ft.txt'"
echo ""
echo "${green}Running std_containers_tests... ${reset}"
echo "Timing:"
time ./std_containers_tests > output/std.txt
echo ""
echo "You will find the tests output in 'build/output/std.txt'"
echo ""
# echo "Real is wall clock time - time from start to finish of the call. 
# User is the amount of CPU time spent in user-mode code (outside the kernel) within the process. 
# Sys is the amount of CPU time spent in the kernel within the process."
# echo ""
echo "${green}To check the difference run${reset} cd build/output && diff std.txt ft.txt "
