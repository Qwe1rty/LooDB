SOURCES = $(shell find src/ -name "*.cpp")
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
#DEPENDS = ${OBJECTS:.o=.d}

CXX = g++
CXX_FLAGS = -g -std=c++17 -MMD
EXEC = loodb

SQLITE_DIR = sqlite
SQLITE_BIN = sqlite3

PARSER_DIR = src/interpreter/parser
QUERY_DIR = queries


-include ${DEPENDS}
.PHONY: build clean test


## Application build/utility commands
##########################################################

build: bison flex replace ${EXEC} clean

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
	@${CXX} ${CXX_FLAGS} ${OBJECTS} ${PARSER_DIR}/sqloo.tab.cc ${PARSER_DIR}/lex.yy.c -o ${EXEC}


## Parser related build/utility commands
##########################################################

bison:
	cd ${PARSER_DIR} && bison sqloo.yy

flex:
	cd ${PARSER_DIR} && flex sqloo.l

replace:
	cd ${PARSER_DIR} && sed -i 's/return \*new (yyas_<T> ()) T (t)/return \*new (yyas_<T> ()) T (std\:\:move((T\&)t))/g' sqloo.tab.hh


## The "sql" set of commands deal with the official SQLite3 database
##########################################################

sql:
	${SQLITE_DIR}/${SQLITE_BIN}

sql-build:
	./sqlite.sh ${SQLITE_DIR} ${SQLITE_BIN}

sql-rm:
	rm -rf ${SQLITE_DIR}

sql-gen:
	./sqlgen.sh ${SQLITE_DIR}/${SQLITE_BIN} ${QUERY_DIR}
