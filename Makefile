SOURCES = $(shell find src/ -name "*.cpp")
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
#DEPENDS = ${OBJECTS:.o=.d}

CXX = g++
CXX_FLAGS = -g -std=c++17 -Wall -MMD
EXEC = loodb

SQLITE_DIR = sqlite
SQLITE_BIN = sqlite3

QUERY_DIR = queries


-include ${DEPENDS}
.PHONY: build clean test

build: ${EXEC} clean

clean:
	@rm ${OBJECTS}

run:
	@./${EXEC}

debug:
	@gdb ./${EXEC}

dry-run:
	@echo ${SRC_DIR}
	@echo ${SOURCES}
	@echo ${OBJECTS}

${EXEC}: ${OBJECTS}
	@${CXX} ${CXX_FLAGS} ${OBJECTS} -o ${EXEC}


# The "sql" set of commands deal with the official SQLite3 database

sql:
	${SQLITE_DIR}/${SQLITE_BIN}

sql-build:
	./sqlite.sh ${SQLITE_DIR} ${SQLITE_BIN}

sql-rm:
	rm -rf ${SQLITE_DIR}

sql-gen:
	./sqlgen.sh ${SQLITE_DIR}/${SQLITE_BIN} ${QUERY_DIR}
