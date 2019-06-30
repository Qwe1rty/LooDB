#!/usr/bin/env bash

# echof.sh
#
# Function that prints text but with a tag containing the scripts' name


echof() {

    local CALLER_NAME=$(ps -o comm= $PPID)
    printf "[%s] %s\n" "${CALLER_NAME}" "$1"
}