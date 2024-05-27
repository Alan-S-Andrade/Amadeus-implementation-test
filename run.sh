#!/bin/bash

# Verify correct number of arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <xml|json> <filename>"
    exit 1
fi

FORMAT=$1
FILENAME=$2

# Compile using g++
g++ -o employee_util main.cpp -ltinyxml2 -lstdc++fs

# Run executable
./employee_util $FORMAT $FILENAME
