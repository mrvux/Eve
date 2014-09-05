
# CMake required version.
###################################################################################################
cmake_minimum_required( VERSION 2.8.8 )


# Policy  
###################################################################################################
if( COMMAND cmake_policy )
	cmake_policy( SET CMP0045 OLD )
	cmake_policy( SET CMP0020 NEW )
endif()


# Grab active configuration.
###################################################################################################

# CMake GUI call
if( NOT CMAKE_BUILD_TYPE ) 
	option( OPTION_BUILD_TYPE_DEBUG "Set build type to Debug." ON )
	option( OPTION_BUILD_TYPE_RELEASE "Set build type to Release." OFF )

	# Debug
	if( OPTION_BUILD_TYPE_DEBUG )
		set( OPTION_BUILD_TYPE_RELEASE OFF CACHE BOOL "turn Release off" FORCE )
		set( CMAKE_BUILD_TYPE "Debug;" )
		set( CMAKE_CONFIGURATION_TYPES "Debug;" CACHE STRING "Reset the configurations to what we need" FORCE ) 
	endif( OPTION_BUILD_TYPE_DEBUG )
	# Release
	if( OPTION_BUILD_TYPE_RELEASE )
		set( OPTION_BUILD_TYPE_DEBUG OFF CACHE BOOL "turn Debug off" FORCE )
		set( CMAKE_BUILD_TYPE "Release;" )	
		set( CMAKE_CONFIGURATION_TYPES "Release;" CACHE STRING "Reset the configurations to what we need" FORCE )
	endif( OPTION_BUILD_TYPE_RELEASE )	
	
	
# Command line call
else() 
	SET( OPTION_BUILD_TYPE_DEBUG OFF )
	SET( OPTION_BUILD_TYPE_RELEASE OFF )

	# Debug
	IF( CMAKE_BUILD_TYPE MATCHES Debug )
		SET( OPTION_BUILD_TYPE_DEBUG ON )	
		set( CMAKE_CONFIGURATION_TYPES "Debug;" CACHE STRING "Reset the configurations to what we need" FORCE )
	ENDIF( CMAKE_BUILD_TYPE MATCHES Debug )
	# Release
	IF( CMAKE_BUILD_TYPE MATCHES Release )
		SET( OPTION_BUILD_TYPE_RELEASE ON )
		set( CMAKE_CONFIGURATION_TYPES "Release;" CACHE STRING "Reset the configurations to what we need" FORCE )
	ENDIF( CMAKE_BUILD_TYPE MATCHES Release )
	
endif()

	
# Prevent the user from selecting both debug and release
if( OPTION_BUILD_TYPE_DEBUG AND OPTION_BUILD_TYPE_RELEASE )
	message( FATAL_ERROR "Debug and Release are both selected -> make up your mind." )
endif()
# Prevent the user from selecting neither debug or release
if( NOT OPTION_BUILD_TYPE_DEBUG AND NOT OPTION_BUILD_TYPE_RELEASE )
	message( FATAL_ERROR "Neither Debug or Release are selected -> please select desired build type." )
endif()


# Project.
###################################################################################################
project( EVE_PROJECT )
set( BASE_SOURCE_PATH "${EVE_PROJECT_SOURCE_DIR}" )


# CMake Configuration.
###################################################################################################
# Find includes in corresponding build directories
set( CMAKE_INCLUDE_CURRENT_DIR ON )
# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC TRUE )
set( CMAKE_AUTOMOC_RELAXED_MODE TRUE )


# Set Default Folders.
###################################################################################################
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_INCLUDE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/include )


# Grab target compiler and set corresponding variables.
###################################################################################################
# Check Compiler:
# USING_GCC  			: gcc is being used for C compiler
# USING_GPP  			: g++ is being used for C++ compiler
# USING_ICC  			: icc is being used for C compiler
# USING_ICPC 			: icpc is being used for C++ compiler
# USING_WINDOWS_MSVC 	: Visual Studio's compiler
# USING_WINDOWS_ICL 	: Intel's Windows compiler 
# USING_LLVM_CLANG 		: Mac OSX 10.8 and higher (XCode) compiler
include( ${BASE_SOURCE_PATH}/CMake/CMakeCheckCompiler.cmake )
	

# Visual Studio configuration.
###################################################################################################
if( WIN32 AND ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )

	# /Gr = fastCall
	# /Ob2 = inline functions expansion
	
	set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Gr /Ob2" )
	list( REMOVE_DUPLICATES CMAKE_CXX_FLAGS_RELEASE )
	
	set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Gr /Ob2" )
	list( REMOVE_DUPLICATES CMAKE_C_FLAGS_RELEASE )
	
	mark_as_advanced( CMAKE_CXX_FLAGS_RELEASE 
					  CMAKE_C_FLAGS_RELEASE 
					  )
	
	# Linker
	set( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_EXE_LINKER_FLAGS_DEBUG )	
	set( CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_SHARED_LINKER_FLAGS_DEBUG )	
	set( CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_MODULE_LINKER_FLAGS_DEBUG )

	mark_as_advanced( CMAKE_EXE_LINKER_FLAGS_DEBUG 
					  CMAKE_SHARED_LINKER_FLAGS_DEBUG 
					  CMAKE_MODULE_LINKER_FLAGS_DEBUG 
					  )
					  
	set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_EXE_LINKER_FLAGS_RELEASE )	
	set( CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_SHARED_LINKER_FLAGS_RELEASE )	
	set( CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")
	list( REMOVE_DUPLICATES CMAKE_MODULE_LINKER_FLAGS_RELEASE )

	mark_as_advanced( CMAKE_EXE_LINKER_FLAGS_RELEASE 
					  CMAKE_SHARED_LINKER_FLAGS_RELEASE 
					  CMAKE_MODULE_LINKER_FLAGS_RELEASE 
					  )
endif()


# Doxygen documentation.
###################################################################################################
option( OPTION_BUILD_DOCUMENTATION "Generating the doxygen documentation." OFF )


# Visual Leak Detector.
###################################################################################################
if( USING_WINDOWS_MSVC )  
	if( OPTION_BUILD_TYPE_DEBUG )
		option( OPTION_BUILD_USE_VLD "Use Visual Leak Detector for Visual C++ (requires Debugging Tools for Windows)" ON)
	else( OPTION_BUILD_TYPE_DEBUG )
		option( OPTION_BUILD_USE_VLD "Use Visual Leak Detector for Visual C++ (requires Debugging Tools for Windows)" OFF)		
	endif( OPTION_BUILD_TYPE_DEBUG )
endif( USING_WINDOWS_MSVC ) 


# External dependencies path.
###################################################################################################
if( WIN32 )
	message( "\n" )

	set( PATH_TO_EXTERNAL "" CACHE PATH "PATH_TO_EXTERNAL" )
	if( PATH_TO_EXTERNAL STREQUAL "" )
		message( "Please set PATH_TO_EXTERNAL to external dependencies directory." )
	endif()
	
	message( "\n" )
endif()

###################################################################################################
# NOTE:
#	These are set in root/PRODUCT_INFO.cmake
#
#  		PRODUCT_VENDOR_NAME
#  		PRODUCT_PRODUCT_NAME
#		PRODUCT_ICON_INSTALL_NAME
#		PRODUCT_ICON_UNINSTALL_NAME
#  		PRODUCT_VERSION_MAJOR
#  		PRODUCT_VERSION_MINOR
#  		PRODUCT_VERSION_PATCH
#  		PRODUCT_VERSION
#		PRODUCT_WEBSITE
#  		PRODUCT_SUPPORT_EMAIL
###################################################################################################
include( ${BASE_SOURCE_PATH}/PRODUCT_INFO.cmake )


# Versioning (GIT and PRODUCT_INFO).
###################################################################################################
include( ${CMAKE_CURRENT_SOURCE_DIR}/CMake/modules/GetGitRevisionDescription.cmake )
git_describe( GIT_VERSION )
message( "Git version: ${GIT_VERSION}" ) 

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/version/version.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/version.h )


# Platform configuration tests.
###################################################################################################
include( ${BASE_SOURCE_PATH}/CMake/CheckAtomicOps.cmake )


# Setting compilation options.
###################################################################################################

# GCC specifics.
#################################################
if( USING_GCC )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -std=c++0x" )
  set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb"  )
endif( USING_GCC )


# Visual Studio specifics.
#################################################
if( WIN32 )

	# Warning Level 3 for Debug builds
	set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3" )
	list( REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG )

	# With Visual Studio 2005, Microsoft deprecates the standard C library, for
	# example fopen() and sprintf(), to non-portable functions fopen_s() and
	# sprintf_s(). These functions are considered by Microsoft more secure. This is
	# a worthwhile exercise ! The use of these deprecated functions causes a lot of
	# warnings. To suppress it, we add the _CRT_SECURE_NO_DEPRECATE and _CRT_NONSTDC_NO_DEPRECATE preprocessor
	# definition -fprofile-arcs -ftest-coverage
	add_definitions( -D_CRT_SECURE_NO_DEPRECATE  -D_CRT_NONSTDC_NO_DEPRECATE )
	
	# /D_CRT_SECURE_NO_WARNINGS : This switch disables the warnings that Visual Studio spits out if you use any of the C RunTime functions that Microsoft has provided secure replacements for (such as strncpy). 
	# This isn�t necessarily a bad idea, but their safe functions are not part of the standard and are thus non-portable:
	# reference : http://msdn.microsoft.com/en-us/library/8ef0s5kh.aspx
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
	
	# /D_SCL_SECURE_NO_WARNINGS : Just like the switch above, only for the Standard C++ Library (anything in the std namespace):
	# reference : http://msdn.microsoft.com/en-us/library/aa985974.aspx	
	add_definitions( -D_SCL_SECURE_NO_WARNINGS )	
	
	# /D_SECURE_SCL=0 : Disables checked iterators. Disabling this feature can improve performance when using iterators, at the expense of less protection against unsafe iterator use.
	# Generally there isn�t too much of a performance difference 
	# (a Visual C++ lead states that they measured about a 6% difference in this feedback / bug page) so it may be worth leaving it on most of the time.
	# reference : http://msdn.microsoft.com/en-us/library/aa985896.aspx
	OPTION( OPTION_BUILD_SECURE_SCL "Activate _SECURE_SCL=0 and _HAS_ITERATOR_DEBUGGING=0 optimizations" OFF )
	if( OPTION_BUILD_SECURE_SCL )
		add_definitions( -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0 )
	endif()
	
	# __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS are a workaround to allow C++ programs to use macros specified in the C99 standard that aren't in the C++ standard. 
	# The macros, such as UINT8_MAX, INT64_MIN, and INT32_C() may be defined already in C++ applications in other ways. 
	# To allow the user to decide if they want the macros defined as C99 does, many implementations require that __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS be defined before stdint.h is included
	add_definitions( -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS )
		
	# Unicode
	add_definitions( -D_UNICODE -DUNICODE )
	
	# Remove Windows "min" and "max" defines conflicting with "std::min" and "std::max"
	add_definitions( -DNOMINMAX )
	
endif()


# CLANG specifics.
#################################################
if( APPLE )

	set( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x" )
	set( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++" )
	set( CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ ${CMAKE_CXX_FLAGS}" )
	set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall" )
  
	# c++11 features
	include( ${BASE_SOURCE_PATH}/CMake/test_cxx11/CheckCXX11Features.cmake )
	foreach( flag ${CXX11_FEATURE_LIST} )
		add_definitions( -D${flag} )
	endforeach()

	set( CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "CMAKE_OSX_ARCHITECTURES" FORCE)

	if( OPTION_BUILD_TYPE_DEBUG ) 
		add_definitions(-g -O0 -Wall -pipe -v -DDEBUG -D_DEBUG -ObjC++)
	endif()

	if( OPTION_BUILD_TYPE_RELEASE )
		add_definitions( -O3 -pipe -DNDEBUG -D_NDEBUG -ObjC++)	
	endif()
	
endif()


# Doxygen documentation.
#################################################
if( OPTION_BUILD_DOCUMENTATION )
	find_package(Doxygen)
	add_subdirectory( ${BASE_SOURCE_PATH}/doc )
endif()


# Platform configuration flags.
###################################################################################################
if( WIN32 )
	if( CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64" )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" )
	else( CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64" )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )		
	endif( CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64" )
endif()

if( APPLE )
	set( CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} )

	set( COVERAGE_FLAGS -fprofile-arcs -ftest-coverage )
	set( COVERAGE_LIB -lgcov )

	set( CMAKE_MACOSX_RPATH TRUE )
	if(CMAKE_SYSTEM_PROCESSOR STREQUAL "ia64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -single_module -headerpad_max_install_names ${COVERAGE_LIB}") 
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -single_module -headerpad_max_install_names ${COVERAGE_LIB}") 			
	endif()
endif()
	
# GCC -> kept for future use
# if(CMAKE_SYSTEM_PROCESSOR STREQUAL "ia64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,--export-dynamic")
	# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
# else()
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--export-dynamic")
# endif()


# Include folders to build process
###################################################################################################
add_subdirectory( eve )


# Include installer folder
###################################################################################################
include( ${BASE_SOURCE_PATH}/CPack/Installer.cmake )