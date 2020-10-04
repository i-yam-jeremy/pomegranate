# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE /usr/local/lib/antlr-4.8-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(LsystemGrammar ${CMAKE_SOURCE_DIR}/lsystem/parser/Lsystem.g4
	LEXER PARSER VISITOR
	PACKAGE lsystem
	DEPENDS ${CMAKE_SOURCE_DIR}/lsystem/parser/Lsystem.g4)

# include generated files in project environment
include_directories(${ANTLR_LsystemGrammar_OUTPUT_DIR})

# add generated grammar to demo binary target
file(GLOB ANTLR_LsystemGrammar_CXX_OUTPUTS
	"${ANTLR_LsystemGrammar_OUTPUT_DIR}/src/lsystem/parser/*.h"
	"${ANTLR_LsystemGrammar_OUTPUT_DIR}/src/lsystem/parser/*.cpp"
)
add_executable(Pomegranate src/main.cpp
	${ANTLR_LsystemGrammar_CXX_OUTPUTS})
target_link_libraries(Pomegranate antlr4_static)
