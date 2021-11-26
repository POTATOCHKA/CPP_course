#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cpplint.py"
python3 ./linters/cpplint/cpplint.py --extensions=c project/func/* project/tests/*

print_header "SUCCESS"