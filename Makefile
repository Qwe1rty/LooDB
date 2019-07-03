SRC_DIR = $(wildcard src/**/)
SOURCES = $(wildcard $(addsuffix *.cpp,$(SRC_DIR)))
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS = ${OBJECTS:.o=.d}

CXX = g++
CXX_FLAGS = -g -std=c++17 -Wall -MMD
EXEC = loodb

#TEST_SCRIPT = test.sh
#TEST_DIR = tests

SQLITE_DIR = sqlite
SQLITE_BIN = sqlite3

QUERY_DIR = queries


-include ${DEPENDS}
.PHONY: build clean

build: ${EXEC} clean

clean:
	rm ${OBJECTS} ${DEPENDS}

run:
	./${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXX_FLAGS} ${OBJECTS} -o ${EXEC}


# The "sql" set of commands deal with the official SQLite3 database

sql:
	${SQLITE_DIR}/${SQLITE_BIN}

sql-build:
	./sqlite.sh ${SQLITE_DIR} ${SQLITE_BIN}

sql-rm:
	rm -rf ${SQLITE_DIR}

sql-gen:
	./sqlgen.sh ${SQLITE_DIR}/${SQLITE_BIN} ${QUERY_DIR}
