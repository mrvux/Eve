
###################################################################################################
# NOTE:
# 	BASE_SOURCE_PATH is defined in ROOT\CMakeLists.txt
# 	PATH_TO_EXTERNAL is defined in ROOT\CMakeLists.txt
###################################################################################################


###################################################################################################
# NOTE:
#	These are set in root/PRODUCT_INFO.cmake
#
#  		PRODUCT_VENDOR_NAME
#  		PROJECT_NAME
#		PRODUCT_ICON_INSTALL_NAME
#		PRODUCT_ICON_UNINSTALL_NAME
#  		PRODUCT_VERSION_MAJOR
#  		PRODUCT_VERSION_MINOR
#  		PRODUCT_VERSION_PATCH
#  		PRODUCT_VERSION
#		PRODUCT_WEBSITE
#  		PRODUCT_SUPPORT_EMAIL
###################################################################################################

macro( add_project PROJECT_NAME_IN )
		
	# CMake Configuration.
	###################################################################################################
	# Find includes in corresponding build directories
	set( CMAKE_INCLUDE_CURRENT_DIR ON )
	# Instruct CMake to run moc automatically when needed.
	set( CMAKE_AUTOMOC TRUE )
	set( CMAKE_AUTOMOC_RELAXED_MODE TRUE )


	# Project.
	###################################################################################################

	# Project name.
	set( PROJECT_NAME ${PRODUCT_PRODUCT_NAME}_${PROJECT_NAME_IN} )
	project( ${PROJECT_NAME} )

	# Source files.
	set( SOURCE_FILES 
		 ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_IN}/main.cpp )
		 
	set_source_files_properties( ${SOURCE_FILES} PROPERTIES GENERATED true )

	# Include directories
	include_directories( ${BASE_SOURCE_PATH}/${PRODUCT_PRODUCT_NAME} )
	include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_IN} )

	# Windows resources file.
	if( WIN32 )
		# Generate rc files
		configure_file( ${BASE_SOURCE_PATH}/${PRODUCT_PRODUCT_NAME}/${PRODUCT_PRODUCT_NAME}.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc @ONLY )
		# Set properties to generated files
		set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc PROPERTIES GENERATED TRUE )	
		set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc )
	endif()

	# Create executable
	set( exe_name "${PROJECT_NAME}_exe" )
	if( WIN32 )
		add_executable( ${exe_name} WIN32 ${SOURCE_FILES} )
	endif()

	if( APPLE )
		# Info.plist content ----------
		set( MACOSX_BUNDLE TRUE )
		set( MACOSX_BUNDLE_INFO_STRING 			"${PROJECT_NAME}" )
		set( MACOSX_BUNDLE_ICON_FILE 			"${PRODUCT_ICON_INSTALL_NAME}.icns" )
		set( MACOSX_BUNDLE_GUI_IDENTIFIER 		"com.${PRODUCT_VENDOR_NAME}.${PROJECT_NAME}" )
		set( MACOSX_BUNDLE_BUNDLE_NAME 			"${PROJECT_NAME}" )
		set( MACOSX_BUNDLE_LONG_VERSION_STRING 	"${PRODUCT_VERSION}" )
		set( MACOSX_BUNDLE_SHORT_VERSION_STRING "${PRODUCT_VERSION_MAJOR}" )
		set( MACOSX_BUNDLE_BUNDLE_VERSION 		"${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}" )
		set( MACOSX_BUNDLE_COPYRIGHT 			"Copyright 2014 ${PRODUCT_VENDOR_NAME}. All rights reserved." )

		# RPATH ---------- do not force RPATH in OSX 10.8 and above ---- RC
		set( CMAKE_SKIP_BUILD_RPATH FALSE )
		set( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
		set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )
		set( CMAKE_INSTALL_RPATH "Contents/MacOSX" )
		set( INSTALL_NAME_DIR @rpath )

		# Icone ----------
		set( APP_ICNS_FILE "${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.icns" )
		set_source_files_properties( "${APP_ICNS_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
		set( SOURCE_FILES ${SOURCE_FILES} ${APP_ICNS_FILE} )

		# CURL crt ----------
		set( CURL_CRT_FILE "${BASE_SOURCE_PATH}/asset/data/curl-ca-bundle.crt" )
		set_source_files_properties( "${CURL_CRT_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
		set( SOURCE_FILES ${SOURCE_FILES} ${CURL_CRT_FILE} )

		# qt.conf file ----------
		set( QT_CONF_FILE "${BASE_SOURCE_PATH}/CPack/osx/qt.conf" )
		set_source_files_properties( "${QT_CONF_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
		set( SOURCE_FILES ${SOURCE_FILES} ${QT_CONF_FILE} )

		add_executable( ${exe_name} MACOSX_BUNDLE ${SOURCE_FILES} )
	endif()

	# Link packages to executable.
	if( APPLE )
		# Set executable properties.
		set_target_properties( ${exe_name} PROPERTIES MACOSX_RPATH 0 )
		set_target_properties( ${exe_name} PROPERTIES SKIP_BUILD_RPATH 1 INSTALL_RPATH "@executable_path" )
		set_target_properties( ${exe_name} PROPERTIES LINK_FLAGS " -framework AppKit  -framework ApplicationServices -framework CoreFoundation -framework CoreServices -framework DiskArbitration -framework Security" )

		# Info.plist
		set( APP_ICNS "${PRODUCT_PRODUCT_NAME}.icns" )
		configure_file( ${BASE_SOURCE_PATH}/CPack/osx/Info.plist.in ${PROJECT_BINARY_DIR}/Info.plist @ONLY )
		set_target_properties( ${exe_name} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist )
	endif()	

	# Link executable to libraries.
	if( WIN32 )
		set( LIBS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${PRODUCT_PRODUCT_NAME}.lib )
	elseif( APPLE )
		set( LIBS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${PRODUCT_PRODUCT_NAME}.a )
	endif()
	target_link_libraries( ${exe_name} ${LIBS} )

	# Executable properties
	add_dependencies( ${exe_name} ${PRODUCT_PRODUCT_NAME} )
	set_target_properties( ${exe_name} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )

	# Executable install target
	install( TARGETS ${exe_name} BUNDLE DESTINATION . COMPONENT ${PROJECT_NAME} 
								 RUNTIME DESTINATION . COMPONENT ${PROJECT_NAME} )

	# Windows icon file.
	if( WIN32 )
		configure_file( ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_ICON_INSTALL_NAME}.ico COPYONLY )	
		install( FILES  ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico DESTINATION . COMPONENT ${PROJECT_NAME} )
		
		if( OPTION_BUILD_TYPE_DEBUG )  
			install( FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${exe_name}.pdb DESTINATION . COMPONENT ${PROJECT_NAME} )
		endif() 
	endif()

endmacro()













 