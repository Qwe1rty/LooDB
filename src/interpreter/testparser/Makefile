sqloo: bison flex main.cpp
	g++ -std=c++17 main.cpp Parser.cpp sqloo.tab.cc lex.yy.c ../../schema/impl/Entry/Entry.cpp ../../schema/impl/Entry/NullEntry.cpp ../../schema/impl/Entry/IntEntry.cpp ../../schema/impl/Entry/StringEntry.cpp -o test
bison: sqloo.yy
	bison sqloo.yy
flex: sqloo.l
	flex sqloo.l