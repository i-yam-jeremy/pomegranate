# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(GENERATED_SOURCE_DIR ${PROJECT_BINARY_DIR}/generated)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

# -*- mode:cmake -*-
if(NOT UNIX)
  message(WARNING "Unsupported operating system")
endif()

include(SimpleANTLR)
compile_antlr("Lsystem" ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 ${GENERATED_SOURCE_DIR})

include_directories(
  ${PROJECT_BINARY_DIR}/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/runtime/src
  ${GENERATED_SOURCE_DIR}
  )

file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE Pomegranate-GENERATED_SRC "${GENERATED_SOURCE_DIR}/*.cpp")
set(Pomegranate_SRC 
	${Pomegranate-GENERATED_SRC}
  	${Pomegranate-NONGENERATED_SRC}
  )

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set (flags_1 "-Wno-overloaded-virtual")
else()
  set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${Pomegranate_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
          )
endforeach(src_file ${Pomegranate_SRC})

add_executable(Pomegranate
  ${Pomegranate_SRC}
  )

add_dependencies(Pomegranate GenericParser)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

target_link_libraries(Pomegranate antlr4_static)
