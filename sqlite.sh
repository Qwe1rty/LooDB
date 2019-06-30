#!/usr/bin/env bash

# sqlite.sh
#
# Downloads the official SQLite3 DB and builds it with extra compilation
# settings that allow for easier analysis
#
# Parameters:
# $1 is the directory in which the SQLite DB will be built in
# $2 is the name of the compiled SQLite binary


source "echof.sh"

SQLITE_DIR="$1"
SQLITE_BIN="$2"

SQLITE_URL_SRC='https://www.sqlite.org/2019/sqlite-amalgamation-3280000.zip'
SQLITE_ZIP_SRC=$(basename "${SQLITE_URL_SRC}")

SQLITE_OPTIONS="\
    -lpthread \
    -ldl \
    -DSQLITE_ENABLE_EXPLAIN_COMMENTS \
    -DSQLITE_OMIT_BTREECOUNT \
"

PREREQUISITES=(
    'unzip'
    'gcc'
)


# Validate parameters and installed prerequisites
validate() {

    if [[ -z "${SQLITE_DIR}" ]] ; then
        echof "Parameter for sqlite build directory is undefined"
        exit 1
    elif [[ -z "${SQLITE_BIN}" ]] ; then
        echof "Parameter for sqlite binary name is undefined"
        exit 2
    fi

    for (( i = 0; i < ${#PREREQUISITES[@]} ; i++ )) ; do
        if ! [[ -x "$(command -v ${PREREQUISITES[i]})" ]] ; then
            echof "Prerequisite not found; please install with 'sudo apt install ${PREREQUISITES[i]}' and try again"
            exit $(( 101 + i ))
        fi
    done
}

# Retrieve the sqlite source code and unpack the zip
unpack() {

    if [[ -f "${SQLITE_BIN}" ]] ; then
        echof "Binary file '${SQLITE_BIN}' already exists, so no need to recompile; exiting script"
        exit 0
    else
        echof "Attempting to download and unpack source code"
    fi

    wget "${SQLITE_URL_SRC}"
    unzip -j "${SQLITE_ZIP_SRC}"
    rm -f "${SQLITE_ZIP_SRC}"

    echof "Unpacking successful"
}

# Build the amalgamation
build() {

    echof "Attempting to build source code"

    gcc shell.c sqlite3.c ${SQLITE_OPTIONS} -o ${SQLITE_BIN}
    rm -f *.c *.h

    echof "Compilation successful"
}

main() {

    validate

    if [[ ! -d "${SQLITE_DIR}" ]] ; then
        echof "Creating directory ${SQLITE_DIR}"
        mkdir "${SQLITE_DIR}"
    fi
    echof "Changing to directory ${SQLITE_DIR}"
    cd "${SQLITE_DIR}"

    unpack
    build

    echof "Installation successful"
}

main