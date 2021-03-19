CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Pomegranate)

set(CMAKE_CXX_STANDARD 17)

find_package(glm CONFIG REQUIRED)
add_definitions(-DANTLR4CPP_STATIC)
link_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib) # for antlr4

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories("${PROJECT_SOURCE_DIR}/thirdparty/include")

include(LsystemParser)
include_directories(${GENERATED_SOURCE_DIR})

if (MSCV)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

file(GLOB_RECURSE Pomegranate-NONGENERATED_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(Pomegranate_SRC 
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
    $<TARGET_OBJECTS:LsystemParser>
    ${Pomegranate_SRC}
)

target_include_directories(Pomegranate PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(Pomegranate PRIVATE glm)
target_include_directories(Pomegranate PRIVATE ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE antlr4-runtime)
target_link_libraries(Pomegranate PRIVATE uuid)
