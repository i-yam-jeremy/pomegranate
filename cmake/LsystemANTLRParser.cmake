set(GRAMMAR_NAME "Lsystem")
set(GRAMMAR_FILE "${PROJECT_SOURCE_DIR}/src/lsystem/parser/Lsystem.g4")
set(GENERATED_SOURCE_DIR "${PROJECT_BINARY_DIR}/generated")

	set(Pomegranate-GENERATED_SRC
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Lexer.cpp 
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Parser.cpp
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}BaseListener.cpp
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}BaseVisitor.cpp
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Listener.cpp
	   ${GENERATED_SOURCE_DIR}/${GRAMMAR_NAME}Visitor.cpp
	 )

	foreach(src_file ${Pomegranate-GENERATED_SRC})
	      set_source_files_properties(
		  ${src_file}
		  PROPERTIES
		  GENERATED TRUE
		  )
	endforeach(src_file ${Pomegranate-GENERATED_SRC})

	set(ANTLR_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr-4.8-complete.jar)

	add_custom_command(OUTPUT ${Pomegranate-GENERATED_SRC}
	   COMMAND 
	   ${CMAKE_COMMAND} -E make_directory ${GENERATED_SOURCE_DIR}
	   COMMAND
	   java -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -listener -visitor -o ${GENERATED_SOURCE_DIR} -package lsystem ${GRAMMAR_FILE}
	   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	   DEPENDS ${GRAMMAR_FILE}
	   COMMENT "Compiling ${GRAMMAR_NAME} grammar"
	   )
	set(Pomegranate-GENERATED_SRC ${Pomegranate-GENERATED_SRC} PARENT_SCOPE)
