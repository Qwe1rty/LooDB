CXX = g++
CXX_FLAGS = -g -std=c++14 -Wall -MMD
EXEC = loodb
OBJECTS = Main.o
DEPENDS = ${OBJECTS:.o=.d}

#TEST_SCRIPT = test.sh
#TEST_DIR = tests

SQLITE_DIR = sqlite
SQLITE_BIN = sqlite3

QUERY_DIR = queries


-include ${DEPENDS}
.PHONY: build test clean clean-test clean-all


all: build test

build: ${EXEC} clean-build

${EXEC}: ${OBJECTS}
	${CXX} ${CXX_FLAGS} ${OBJECTS} -o ${EXEC}

#test:
#	./${TEST_SCRIPT} ${TEST_DIR}


clean: clean-exec clean-test

clean-build:
	rm ${OBJECTS} ${DEPENDS}

clean-exec: clean-build
	rm ${EXEC}

#clean-test:
#	find ${TEST_DIR} -iregex '.*\.\(out\|out\.my\|diff\|valg\)' -delete


# The "sql" set of commands deal with the official SQLite3 database

sql:
	${SQLITE_DIR}/${SQLITE_BIN}

sql-build:
	./sqlite.sh ${SQLITE_DIR} ${SQLITE_BIN}

sql-rm:
	rm -rf ${SQLITE_DIR}

sql-gen:
	./sqlgen.sh ${SQLITE_DIR}/${SQLITE_BIN} ${QUERY_DIR}
