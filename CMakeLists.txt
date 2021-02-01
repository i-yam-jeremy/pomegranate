# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(thirdparty/antlr4-cpp-runtime)
add_subdirectory(thirdparty/antlr4-cpp-runtime)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(GENERATED_SOURCE_DIR "${PROJECT_BINARY_DIR}/generated")

include(SimpleANTLR)
compile_antlr("Lsystem" ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 ${GENERATED_SOURCE_DIR})

include_directories(${GENERATED_SOURCE_DIR})

file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC2 "${PROJECT_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE Pomegranate-GENERATED_SRC "${GENERATED_SOURCE_DIR}/*.cpp")
set(Pomegranate_SRC 
	${Pomegranate-GENERATED_SRC}
  	${Pomegranate-NONGENERATED_SRC}
    ${Pomegranate-NONGENERATED_SRC2}
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

add_definitions(-D_USE_MATH_DEFINES)
add_executable(Pomegranate
  ${Pomegranate_SRC}
  )
target_include_directories(Pomegranate PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_dependencies(Pomegranate GenericParser)
add_dependencies(Pomegranate antlr4_cpp_runtime)
target_link_libraries(Pomegranate antlr4_cpp_runtime ${CONAN_LIBS})
