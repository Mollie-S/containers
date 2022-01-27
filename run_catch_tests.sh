#!/bin/bash
green=`tput setaf 2`
reset=`tput sgr0`
echo "${green}Compiling Catch2 tests ${reset}"
make -s catch
echo "${green}Running Catch2 tests ${reset}"
cd build && ./catch2_containers_tests

