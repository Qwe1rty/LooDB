sqloo: bison flex Orchestrator.cpp
	g++ -std=c++17 Orchestrator.cpp sqloo.tab.cc lex.yy.c ../schema/impl/Entry/Entry.cpp ../schema/impl/Entry/StringEntry.cpp -lfl -o Orchestrator
bison: parser/sqloo.y
	bison -d parser/sqloo.y
flex: parser/sqloo.l
	flex parser/sqloo.l