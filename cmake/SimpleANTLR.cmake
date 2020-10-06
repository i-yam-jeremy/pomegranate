function(compile_antlr GRAMMAR_NAME GRAMMAR_FILE GENERATED_SOURCE_DIR)
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

	add_custom_target(GenericParser DEPENDS ${Pomegranate-GENERATED_SRC})
	add_custom_command(OUTPUT ${Pomegranate-GENERATED_SRC}
	   COMMAND 
	   ${CMAKE_COMMAND} -E make_directory ${GENERATED_SOURCE_DIR}
	   COMMAND
	   java -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -listener -visitor -o ${GENERATED_SOURCE_DIR} -package lsystem ${GRAMMAR_FILE}
	   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	   DEPENDS ${GRAMMAR_FILE}
	   COMMENT "Compiling ${GRAMMAR_NAME} grammar"
	   )
endfunction(compile_antlr)
