CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

set(CMAKE_CXX_STANDARD 14)

find_package(openmesh REQUIRED)
find_package(glm CONFIG REQUIRED)
link_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib) # for antlr4

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(GENERATED_SOURCE_DIR "${PROJECT_BINARY_DIR}/generated")

include(SimpleANTLR)
compile_antlr("Lsystem" ${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4 ${GENERATED_SOURCE_DIR})

include_directories(${GENERATED_SOURCE_DIR})

file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE Pomegranate-GENERATED_SRC "${GENERATED_SOURCE_DIR}/*.cpp")
message(STATUS ${Pomegranate-GENERATED_SRC})
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

add_dependencies(Pomegranate GenericParser)
target_include_directories(Pomegranate PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_include_directories(Pomegranate PRIVATE ${OPENMESH_INCLUDE_DIRS})
target_link_libraries(Pomegranate PRIVATE ${OPENMESH_LIBRARIES})
target_link_libraries(Pomegranate PRIVATE glm)
target_include_directories(Pomegranate PRIVATE ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE uuid)
