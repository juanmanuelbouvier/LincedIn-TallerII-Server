cmake_minimum_required (VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# ----- Sphinx ----- #
find_package(Sphinx)

if (SPHINX_FOUND)
	set(SPHINX_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx")
 
	if(NOT DEFINED SPHINX_THEME)
    		set(SPHINX_THEME default)
	endif()
 
	if(NOT DEFINED SPHINX_THEME_DIR)
    		set(SPHINX_THEME_DIR)
	endif()
 
	# configured documentation tools and intermediate build results
	set(BINARY_BUILD_DIR "${SPHINX_BINARY_DIR}/_build")
 
	# Sphinx cache with pickled ReST documents
	set(SPHINX_CACHE_DIR "${SPHINX_BINARY_DIR}/_doctrees")
 
	# HTML output directory
	set(SPHINX_HTML_DIR "${SPHINX_BINARY_DIR}/html")
 
	configure_file(
    		"${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in"
    		"${BINARY_BUILD_DIR}/conf.py"
    	@ONLY)
 
	add_custom_target(my_project_docs ALL
    		${SPHINX_EXECUTABLE}
        		-q -b html
        		-c "${BINARY_BUILD_DIR}"
        		-d "${SPHINX_CACHE_DIR}"
        		"${CMAKE_CURRENT_SOURCE_DIR}"
        		"${SPHINX_HTML_DIR}"
    		COMMENT "Building HTML documentation with Sphinx")
endif()
# ----- ! Sphinx ----- #

# ----- Doxygen ----- #
macro(add_sphinx_target TARGET_NAME BUILDER COMMENT_STR)
    add_custom_target(${TARGET_NAME}
    COMMAND sphinx-build -b ${BUILDER} . ${CMAKE_CURRENT_BINARY_DIR}/${BUILDER}
        WORKING_DIRECTORY doxymentation
        DEPENDS doxygen
        COMMENT ${COMMENT_STR}
    )

endmacro(add_sphinx_target)

add_custom_target(doxygen ALL
    COMMAND doxygen ../Doxyfile
    COMMENT "Build doxygen xml files used by sphinx/breathe."
)

add_sphinx_target(docs-html
    html
    "Build html documentation"
)
# ----- ! Doxygen ----- #



