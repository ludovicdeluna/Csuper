cmake_minimum_required(VERSION 2.8)

project(Csuper C CXX)

#
# Portable
#

IF(PORTABLE MATCHES "TRUE")
	add_definitions(-DPORTABLE)
ENDIF()

#
# Delete depreciated warning on GCC because of Glibmm
#
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0)
    	set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
    endif()
endif()

#
# Glibmm, LibXML++, Cairo
#

find_package(
	PkgConfig 
	REQUIRED
)

pkg_check_modules(
	GLIBMM
	REQUIRED glibmm-2.4
)

pkg_check_modules(
	GIOMM
	REQUIRED  giomm-2.4
)

pkg_check_modules(
	XMLPP
	REQUIRED libxml++-2.6
)

pkg_check_modules(
	CAIRO
	REQUIRED cairo
)

include_directories(
	${XMLPP_INCLUDE_DIRS}
	${GIOMM_INCLUDE_DIRS}
	${GLIBMM_INCLUDE_DIRS}
	${CAIRO_INCLUDE_DIRS}
)
link_directories(
	${XMLPP_LIBRARY_DIRS}
	${GLIBMM_LIBRARY_DIRS}
	${GIOMM_LIBRARY_DIRS}
	${CAIRO_LIBRARY_DIRS}
	${PROJECT_BINARY_DIR}
)

add_definitions(
	${XMLPP_CFLAGS_OTHER}
	${GLIBMM_CFLAGS_OTHER}
	${GLIOMM_CFLAGS_OTHER}
	${CAIRO_CFLAGS_OTHER}
)

#
# Slope
#

set(SLOPE_HAVE_GTK 0)
set(SLOPE_HAVE_PANGO 0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 


include_directories(
	"Externals library/Slope"
)

CONFIGURE_FILE(
	"Externals library/Slope/slope-config.h.in"
	"Externals library/Slope/slope-config.h"
)

file(
    GLOB
    source_files_slope
    "Externals library/Slope/slope/primitives.c"
    "Externals library/Slope/slope/text.c"
    "Externals library/Slope/slope/list.c"
    "Externals library/Slope/slope/figure.c"
    "Externals library/Slope/slope/metrics.c"
    "Externals library/Slope/slope/item.c"
    "Externals library/Slope/slope/xymetrics.c"
    "Externals library/Slope/slope/funcplot.c"
    "Externals library/Slope/slope/xyaxis.c"
    "Externals library/Slope/slope/legend.c"
    "Externals library/Slope/slope/slope.c"
    "Externals library/Slope/slope/custom-item.c"
    "Externals library/Slope/slope-config.h"
)

ADD_LIBRARY(
	slope
	STATIC
	${source_files_slope}
)

TARGET_LINK_LIBRARIES(
	slope 
	${CAIRO_LIBRARIES}
)


#
# libcsuper
#


file(
        GLOB
        source_files_libcsuper
        Sources/libcsuper/*.cpp
)

add_library(
	csuper
	SHARED
	${source_files_libcsuper}
)


target_link_libraries(
	csuper
	${GLIBMM_LIBRARIES}
	${GIOMM_LIBRARIES}
	${XMLPP_LIBRARIES}
	muparser
	podofo
	slope
)

target_compile_features(
	csuper
	PRIVATE cxx_range_for
)

#
# csuper-cli
#

IF(CLI MATCHES "TRUE")

	file(
		    GLOB
		    source_files_csuper-cli
		    Sources/csuper-cli/*.cpp
	)

	add_executable(
		csuper-cli
		${source_files_csuper-cli}
	)
	target_link_libraries(
		csuper-cli 
		csuper
		${GLIBMM_LIBRARIES}
		${GIOMM_LIBRARIES}
		${XMLPP_LIBRARIES}
		muparser
	)
	
	IF(UNIX)
		target_link_libraries(
			csuper-cli 
			curses
		)
	ENDIF() # UNIX

	target_compile_features(
		csuper-cli
		PRIVATE cxx_range_for
	)

ENDIF() # CLI


#
# csuper-gtk
#

IF(GTK MATCHES "TRUE")

	pkg_check_modules(
		GTKMM
		REQUIRED gtkmm-3.0>=3.10
	)

	include_directories(
		${GTKMM_INCLUDE_DIRS}
	)
	
	link_directories(
		${GTKMM_LIBRARY_DIRS}
	)

	add_definitions(
		${GTKMM_CFLAGS_OTHER}
	)


	file(
	    GLOB
	    source_files_csuper-gtk
	    Sources/csuper-gtk/*.cpp
	)

	add_executable(
		csuper-gtk
		${source_files_csuper-gtk}
	)
	
	target_link_libraries(
		csuper-gtk
		csuper
		${GLIBMM_LIBRARIES}
		${XMLPP_LIBRARIES}
		${GTKMM_LIBRARIES}
		muparser
	)
	
	target_compile_features(
		csuper-gtk
		PRIVATE cxx_range_for
	)
	

ENDIF() # CLI
