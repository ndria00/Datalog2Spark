#
CXX = g++

CXXFLAGS := -std=c++17 -Wall -Wextra 

LIB		:= Compiler/lib
ANTLR	:= libantlr4-runtime.a
COMPILER_SRC	:= Compiler
OUTPUT	:= dist
SRC 	:= .
REQUIRED_LIB	:= $(LIB)/linux-$(ANTLR)
ifeq ($(OS),Windows_NT)
		
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		REQUIRED_LIB	:= $(LIB)/macos-$(ANTLR)
	endif
endif

compile:
	if [ ! -d "$(OUTPUT)" ]; then \
        mkdir $(OUTPUT); \
    fi

	cp $(REQUIRED_LIB) $(LIB)/$(ANTLR)
	$(MAKE) -C $(COMPILER_SRC) clean
	$(MAKE) -C $(COMPILER_SRC) -j
	