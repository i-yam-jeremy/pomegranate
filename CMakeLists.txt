CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

set(CMAKE_CXX_STANDARD 14)

find_package(openmesh REQUIRED)
find_package(glm CONFIG REQUIRED)
link_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib) # for antlr4

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(GENERATED_SOURCE_DIR "${PROJECT_BINARY_DIR}/generated")
set(GRAMMAR_NAME "Lsystem")
set(GRAMMAR_FILE "${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4")
set(Pomegranate-GENERATED_SRC
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Lexer.cpp" 
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Parser.cpp"
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}BaseListener.cpp"
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}BaseVisitor.cpp"
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Listener.cpp"
	   "${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Visitor.cpp"
	 )

	set(ANTLR_JAR_LOCATION "${PROJECT_SOURCE_DIR}/thirdparty/antlr-4.8-complete.jar")

	message(STATUS "${GENERATED_SOURCE_DIR}")
	add_custom_command(OUTPUT ${Pomegranate-GENERATED_SRC}
	   COMMAND 
	   ${CMAKE_COMMAND} -E make_directory ${GENERATED_SOURCE_DIR}
	   COMMAND
	   java -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -listener -visitor -o ${GENERATED_SOURCE_DIR} -package lsystem ${GRAMMAR_FILE}
	   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
	   DEPENDS ${GRAMMAR_FILE}
	   COMMENT "Compiling ${GRAMMAR_NAME} grammar"
	   )

	   	foreach(src_file ${Pomegranate-GENERATED_SRC})
	      set_source_files_properties(
		  ${src_file}
		  PROPERTIES
		  GENERATED TRUE
		  )
	endforeach(src_file ${Pomegranate-GENERATED_SRC})
#include(SimpleANTLR)
#compile_antlr("Lsystem" ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 ${GENERATED_SOURCE_DIR})

include_directories(${GENERATED_SOURCE_DIR})

file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
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

add_definitions(-D_USE_MATH_DEFINES)
add_executable(Pomegranate
  ${Pomegranate_SRC}
  )

target_include_directories(Pomegranate PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_include_directories(Pomegranate PRIVATE ${OPENMESH_INCLUDE_DIRS})
target_link_libraries(Pomegranate PRIVATE ${OPENMESH_LIBRARIES})
target_link_libraries(Pomegranate PRIVATE glm)
target_include_directories(Pomegranate PRIVATE ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE uuid)
