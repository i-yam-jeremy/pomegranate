# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

# -*- mode:cmake -*-
if(NOT UNIX)
  message(WARNING "Unsupported operating system")
endif()

set(antlr4-demo-GENERATED_SRC
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemLexer.cpp 
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemParser.cpp
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemBaseListener.cpp
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemBaseVisitor.cpp
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemListener.cpp
   ${PROJECT_SOURCE_DIR}/bin/generated/LsystemVisitor.cpp
 )

foreach(src_file ${antlr4-demo-GENERATED_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          GENERATED TRUE
          )
endforeach(src_file ${antlr4-demo-GENERATED_SRC})

set(ANTLR_JAR_LOCATION /usr/local/lib/antlr-4.8-complete.jar)

add_custom_target(GenerateParser DEPENDS ${antlr4-demo-GENERATED_SRC})
add_custom_command(OUTPUT ${antlr4-demo-GENERATED_SRC}
   COMMAND 
   ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/bin/generated/
   COMMAND
   "${Java_JAVA_EXECUTABLE}" -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -listener -visitor -o ${PROJECT_SOURCE_DIR}/bin/generated/ -package antlrcpptest ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4
   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
   DEPENDS ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 
   )

include_directories(
  ${PROJECT_BINARY_DIR}/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/runtime/src
  ${PROJECT_SOURCE_DIR}/bin/generated
  )

#file(GLOB antlr4-demo_SRC "${PROJECT_SOURCE_DIR}/bin/generated/*")
set(antlr4-demo_SRC 
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${antlr4-demo-GENERATED_SRC}
  )

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set (flags_1 "-Wno-overloaded-virtual")
else()
  set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${antlr4-demo_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
          )
endforeach(src_file ${antlr4-demo_SRC})

add_executable(antlr4-demo
  ${antlr4-demo_SRC}
  )

add_dependencies(antlr4-demo GenerateParser)

target_link_libraries(antlr4-demo antlr4_static)
