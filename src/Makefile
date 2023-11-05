CXX := g++
CXX_FLAGS := -Wall -w -Wextra -std=c++17
GCOVFLAGS := -L. --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	TEST_FLAGS := $(shell pkg-config --libs gtest)
else
	TEST_FLAGS := -lgtest
endif

LIB_SRC_MOD := $(wildcard model/*.cc)
LIB_SRC_CON := $(wildcard controllers/*.cc)
LIB_SRC_VIE := $(wildcard view/*.cpp)
LIB_HDR_MOD := $(wildcard model/*.h)
LIB_HDR_CON := $(wildcard controllers/*.h)
LIB_HDR_VIE := $(wildcard view/*.h)

TESTS_SRC := $(wildcard tests/*.cc) $(wildcard tests/*/*.cc)
TESTS_HDR := $(wildcard tests/*.h) $(wildcard tests/*/*.h)
TESTS_BIN := tests.out

ifeq ($(OS), Linux)
	MEM_CHECK := valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(TESTS_BIN)
else
	MEM_CHECK := CK_FORK=no leaks --atExit -- ./$(TESTS_BIN)
endif

all: test

clean:
	- rm -rf *.a *.o .clang-format $(TEST_BIN) $(TEST_BIN_SAN) *.out gcov_report* *.info report *.gcno tests.out.dSYM
	- rm -rf backend/*.txt
	- rm -rf view/SmartCalc.app
	- rm -rf view/CMakeCache.txt
	- rm -rf view/CMakeFiles
	- rm -rf view/Makefile
	- rm -rf view/cmake_install.cmake
	- rm -rf view/.qmake.stash
	- rm -rf view/*.o
	- rm -rf view/moc_*
	- rm -rf view/.qtc_clangd
	- rm -rf ../archive
	- rm -rf tests_sanitiz*
	- rm -rf *.gcda

test: clean test_build
	./$(TESTS_BIN)

test_build:
	$(CXX) $(CXX_FLAGS) $(TESTS_SRC) $(LIB_SRC_MOD) -o $(TESTS_BIN) $(TEST_FLAGS)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++11 --language=c++ $(LIB_SRC_MOD) $(LIB_SRC_CON) $(LIB_SRC_VIE) \
			$(LIB_HDR_MOD) $(LIB_HDR_CON) $(LIB_HDR_VIE) \
			$(TESTS_SRC) $(TESTS_HDR)

codestyle:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(LIB_SRC_MOD) $(LIB_SRC_CON) $(LIB_SRC_VIE) \
			$(LIB_HDR_MOD) $(LIB_HDR_CON) $(LIB_HDR_VIE) \
			$(TESTS_SRC) $(TESTS_HDR)

install:
	- cd ..; mkdir build
	cd view/; qmake .; make;
	cp -R view/SmartCalc.app ../build/SmartCalc.app
	chmod +rwx ../build
	chmod +rwx ../build/SmartCalc.app
	@chmod +rwx ../build
	@chmod +rwx ../build/SmartCalc.app
	- open ../build/SmartCalc.app

uninstall:
	rm -rf ../build/*.app

dist: install
	- rm -rf ../archive
	- mkdir ../archive
	- mkdir ../archive/SmartCalc_v2.0
	- cp -r ../build/SmartCalc.app ../archive/SmartCalc_v2.0
	- cp -r Manual ../archive/SmartCalc_v2.0
	- cd ../archive && tar cvzf Archive_SmartCalc_v2.0.tgz SmartCalc_v2.0 && rm -rf SmartCalc_v2.0

gcov_report:
	$(CXX) $(CXX_FLAGS) $(LIB_SRC_MOD) $(TESTS_SRC) $(TEST_FLAGS) $(GCOVFLAGS) -o $@
	- ./$@
	lcov -t $@ -o rep.info -c -d . --ignore-errors mismatch
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info
