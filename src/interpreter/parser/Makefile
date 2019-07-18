sqloo: bison flex
	sed -i 's/return \*new (yyas_<T> ()) T (t)/return \*new (yyas_<T> ()) T (std\:\:move((T\&)t))/g' sqloo.tab.hh
	g++ -std=c++17 sqloo.tab.cc lex.yy.c *.cpp ../virtualmachine/impl/*.cpp ../../schema/impl/*.cpp ../../schema/impl/Column/*.cpp ../../schema/impl/Entry/*.cpp ../statements/impl/*.cpp ../../filesystem/pagination/interface/impl/*.cpp ../../filesystem/pagination/page/impl/*.cpp -o Orchestrator
bison: sqloo.yy
	bison sqloo.yy
flex: sqloo.l
	flex sqloo.l