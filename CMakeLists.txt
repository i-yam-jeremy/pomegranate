# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(GENERATED_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/lsystem/parser/generated")

include_directories("${PROJECT_SOURCE_DIR}/thirdparty/antlr-runtime/src")
link_directories(thirdparty/antlr-runtime)

include_directories("C:/Program Files/Autodesk/FBX/FBX SDK/2020.0.1/include")
link_directories("C:/Program Files/Autodesk/FBX/FBX SDK/2020.0.1/lib/vs2017/x64/debug")

include_directories("${PROJECT_SOURCE_DIR}/thirdparty/glm")
add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparty/glm")

include(SimpleANTLR)
compile_antlr("Lsystem" ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 ${GENERATED_SOURCE_DIR})

include_directories(${GENERATED_SOURCE_DIR})

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
target_link_libraries(Pomegranate antlr4-runtime libfbxsdk)
