######
######   LOOKING FOR EXTERNAL LIBRARIES
######
#------------------------------------------------
##############################################################################
##Function for finding libraries.
##############################################################################
function(find_library_shared LIBRARY_NAME BASE_PATH FIND_LIBRARY_FILE FIND_LIBRARY_PATH LIBRARY_FOUND USE_DEFAUT_PATH)
	FOREACH(next_ITEM ${CMAKE_CONFIGURATION_TYPES})
	IF (NOT ${LIBRARY_FOUND})
		IF(USE_DEFAUT_PATH)
			FIND_LIBRARY(${FIND_LIBRARY_FILE} ${LIBRARY_NAME} ${BASE_PATH}/${next_ITEM})
		ELSE(USE_DEFAUT_PATH)
			FIND_LIBRARY(${FIND_LIBRARY_FILE} ${LIBRARY_NAME} ${BASE_PATH}/${next_ITEM} NO_DEFAULT_PATH)
		ENDIF(USE_DEFAUT_PATH)
		IF(NOT ${${FIND_LIBRARY_FILE}} MATCHES ".+(-NOTFOUND)" AND NOT ${LIBRARY_FOUND})
			SET (${LIBRARY_FOUND} 1)
			SET (${FIND_LIBRARY_PATH} ${BASE_PATH}/${next_ITEM})
			MESSAGE("${LIBRARY_NAME} file: ${${FIND_LIBRARY_FILE}} ")
		ENDIF(NOT ${${FIND_LIBRARY_FILE}} MATCHES ".+(-NOTFOUND)" AND NOT ${LIBRARY_FOUND})
	ENDIF (NOT ${LIBRARY_FOUND})
	ENDFOREACH(next_ITEM ${CMAKE_CONFIGURATION_TYPES})
endfunction()

function(find_library_binary LIBRARY_NAME BASE_PATH FIND_LIBRARY_FILE FIND_LIBRARY_PATH LIBRARY_FOUND USE_DEFAUT_PATH )
	FOREACH(next_ITEM ${CMAKE_CONFIGURATION_TYPES})
	IF (NOT ${LIBRARY_FOUND})
		IF(USE_DEFAUT_PATH)
			FIND_FILE(${FIND_LIBRARY_FILE} 
					"${LIBRARY_NAME}" 
					"${BASE_PATH}/${next_ITEM}")
		ELSE(USE_DEFAUT_PATH)
					FIND_FILE(${FIND_LIBRARY_FILE} 
							"${LIBRARY_NAME}" 
							"${BASE_PATH}/${next_ITEM}" 
							NO_DEFAULT_PATH)
		ENDIF(USE_DEFAUT_PATH)
		IF(NOT ${${FIND_LIBRARY_FILE}} MATCHES ".+(-NOTFOUND)" AND NOT ${LIBRARY_FOUND})
			SET (${LIBRARY_FOUND} 1)
			SET (${FIND_LIBRARY_PATH} ${BASE_PATH}/${next_ITEM})
			MESSAGE("${LIBRARY_NAME} file: ${${FIND_LIBRARY_FILE}} ")
		ENDIF(NOT ${${FIND_LIBRARY_FILE}} MATCHES ".+(-NOTFOUND)" AND NOT ${LIBRARY_FOUND})
	ENDIF (NOT ${LIBRARY_FOUND})
	ENDFOREACH(next_ITEM ${CMAKE_CONFIGURATION_TYPES})
endfunction()


#------------------------------------------------
# Finding OpenGL
IF(NOT APPLE)
	find_package(OpenGL REQUIRED)
ELSE(NOT APPLE)
	set(OpenGL_LIBRARY_NAMES OpenGL)
	find_library(OPENGL_gl_LIBRARY
		NAMES ${OpenGL_LIBRARY_NAMES}
		HINTS ${OpenGL_LIB_SEARCH_PATH} NO_DEFAULT_PATH
		)
ENDIF(NOT APPLE)


#------------------------------------------------
# Finding openCL
INCLUDE (${BASE_SOURCE_PATH}/CMake/FindOpenCL.cmake)


#------------------------------------------------
# Finding Visual Leak Detector for Visual C++ 2008/2010
IF(WIN32)
	IF(OPTION_BUILD_USE_VLD)
		INCLUDE (${BASE_SOURCE_PATH}/CMake/FindVld.cmake)
	ENDIF(OPTION_BUILD_USE_VLD)
	IF(OPTION_BUILD_USE_VLD OR OPTION_BUILD_USE_STACKWALKER)
		INCLUDE (${BASE_SOURCE_PATH}/CMake/FindWinDbg.cmake)
	ENDIF(OPTION_BUILD_USE_VLD OR OPTION_BUILD_USE_STACKWALKER)
ENDIF(WIN32)


# #------------------------------------------------
# # Finding OpenCV
# IF(OPTION_BUILD_USE_SOURCE_FROM_GIT)
	# SET(OpenCV_DIR ${BASE_BINARY_PATH}/OpenCV/src/OpenCV-build)
# ELSE(OPTION_BUILD_USE_SOURCE_FROM_GIT)
	# SET(OpenCV_DIR ${BASE_BINARY_PATH}/OpenCV)
# ENDIF(OPTION_BUILD_USE_SOURCE_FROM_GIT)
# INCLUDE(  ${BASE_SOURCE_PATH}/CMake/FindOpenCV.cmake )



