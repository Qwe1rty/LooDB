sqloo: bison flex Orchestrator.cpp
	sed -i 's/return \*new (yyas_<T> ()) T (t)/return \*new (yyas_<T> ()) T (std\:\:move((T\&)t))/g' sqloo.tab.hh
	g++ -std=c++17 Orchestrator.cpp Parser.cpp sqloo.tab.cc lex.yy.c "../statements/impl/Statement.cpp" "../statements/impl/Create.cpp" "../statements/impl/Drop.cpp" "../statements/impl/Insert.cpp" "../statements/impl/Select.cpp" ../../schema/impl/Entry/Entry.cpp ../../schema/impl/Entry/NullEntry.cpp ../../schema/impl/Entry/IntEntry.cpp ../../schema/impl/Entry/StringEntry.cpp -o Orchestrator
bison: sqloo.yy
	bison sqloo.yy
flex: sqloo.l
	flex sqloo.l