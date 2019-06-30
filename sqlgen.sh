#!/usr/bin/env bash

# sqlgen.sh
#
# A script that runs SQL queries through the SQLite3 DB and writes the
# output to a file
#
# Parameters:
# $1 is the location of the SQLite DB binary
# $2 is the directory where all SQLite queries are held. This script will
#    recursively iterate through all .sql files found. The output will be
#    logged into a .out file with the same base file name


source "echof.sh"

SQLITE_BIN="$1"
QUERY_DIR="$2"

QUERY_INPUT_EXT=".sql"
QUERY_OUTPUT_EXT=".out"

TEMP_DB="temp.db"


# Validate parameters and necessary files/directories
validate() {

    if [[ -z "${SQLITE_BIN}" ]] ; then
        echof "Parameter for sqlite binary file location is undefined"
        exit 1
    elif [[ -z "${QUERY_DIR}" ]] ; then
        echof "Parameter for query files directory is undefined"
        exit 2
    fi

    if ! [[ -f "${SQLITE_BIN}" ]] ; then
        echof "Binary file ${SQLITE_BIN} was not found, exiting"
        exit 51
    elif ! [[ -d "${QUERY_DIR}" ]] ; then
        echof "The directory ${QUERY_DIR} does not exist, exiting"
        exit 52
    fi
}

run_query() {

    local QUERY_INPUT_FILE="$1"
    local QUERY_BASE_FILE="${QUERY_INPUT_FILE%${QUERY_INPUT_EXT}}"
    local QUERY_OUTPUT_FILE="${QUERY_BASE_FILE}${QUERY_OUTPUT_EXT}"

    echof "Running query in file ${QUERY_INPUT_FILE}"

    ./"${SQLITE_BIN}" "${TEMP_DB}" "$(cat "${QUERY_INPUT_FILE}")" | tee "${QUERY_OUTPUT_FILE}"
    rm -f "${TEMP_DB}"

    echof "Query has been executed, results have been logged in ${QUERY_OUTPUT_FILE}"
}

main() {

    validate

    echof "Attempting to run all queries in the ${QUERY_DIR} directory"

    IFS=$'\n' # Required for filenames with spaces
    for QUERY_INPUT_FILE in $(find "${QUERY_DIR}" -name "*${QUERY_INPUT_EXT}"); do
        [[ -e "$QUERY_INPUT_FILE" ]] || continue
        run_query "${QUERY_INPUT_FILE}"
    done
    unset IFS

    echof "All queries have been executed"
}

main