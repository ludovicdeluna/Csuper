cmake_minimum_required(VERSION 2.6)

project(Csuper C)

#
#Libcsuper
#

find_package(LibXml2 REQUIRED)

message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})

include_directories(${LIBXML2_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

file(
        GLOB
        source_files_libcsuper
        Sources/libcsuper/*.c
)

add_library(
	csuper
	SHARED
	${source_files_libcsuper}
)

if(WIN32)
	target_link_libraries(
		csuper 
		-lhpdf
		-lintl
		${LIBXML2_LIBRARIES}
	)
else (WIN32)
	target_link_libraries(
		csuper 
		-lhpdf
		${LIBXML2_LIBRARIES}
	)
endif (WIN32)

#
#csuper-cli
#

IF(CLI MATCHES "TRUE")

	file(
		    GLOB
		    source_files_csuper-cli
		    Sources/csuper-cli/*.c
	)

	add_executable(
		csuper-cli
		${source_files_csuper-cli}
	)
	target_link_libraries(
		csuper-cli 
		csuper
		${LIBXML2_LIBRARIES}
	)

ENDIF()

#
# Slope
#

IF(GUI MATCHES "TRUE")

	set(SLOPE_HAVE_GTK 1)
    set(SLOPE_HAVE_PANGO 0)

	find_package(
		PkgConfig 
		REQUIRED
	)
	pkg_check_modules(
		GTK3
		REQUIRED gtk+-3.0>=3.6
	)

	include_directories(
		${GTK3_INCLUDE_DIRS}
		"Externals library/Slope"
	)
	link_directories(
		${GTK3_LIBRARY_DIRS}
	)

	add_definitions(
		${GTK3_CFLAGS_OTHER}
	)

	CONFIGURE_FILE (
		"Externals library/Slope/slope-config.h.in"
		"Externals library/Slope/slope-config.h"
	)

	file(
		    GLOB
		    source_files_slope
		    "Externals library/Slope/slope/*"
		    "Externals library/Slope/slope-config.h"
	)

	ADD_LIBRARY(
		slope
		STATIC
		${source_files_slope}
	)

	TARGET_LINK_LIBRARIES(
		slope 
		${GTK3_LIBRARIES}
	)

ENDIF()


#
#Csuper-gui
#

IF(GUI MATCHES "TRUE")

	file(
		    GLOB
		    source_files_csuper
		    Sources/csuper-gui/*.c
	)

	add_executable(
		csuper-gui
		${source_files_csuper}
	)

	target_link_libraries(
		csuper-gui 
		${GTK3_LIBRARIES}
		${LIBXML2_LIBRARIES}
		csuper
		slope
	)

ENDIF()
