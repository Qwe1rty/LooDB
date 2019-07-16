sqloo: bison flex main.cpp
	sed -i 's/return \*new (yyas_<T> ()) T (t)/return \*new (yyas_<T> ()) T (std\:\:move((T\&)t))/g' sqloo.tab.hh
	g++ -std=c++17 main.cpp Parser.cpp sqloo.tab.cc lex.yy.c "../statements/impl/Statement.cpp" "../statements/impl/Create.cpp" "../statements/impl/Drop.cpp" "../statements/impl/Insert.cpp" ../../schema/impl/Entry/Entry.cpp ../../schema/impl/Entry/NullEntry.cpp ../../schema/impl/Entry/IntEntry.cpp ../../schema/impl/Entry/StringEntry.cpp -o test
bison: sqloo.yy
	bison sqloo.yy
flex: sqloo.l
	flex sqloo.l