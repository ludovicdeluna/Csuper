cmake_minimum_required(VERSION 2.8)

project(Csuper C CXX)

#
# Portable
#

IF(PORTABLE MATCHES "TRUE")
	add_definitions(-DPORTABLE)
ENDIF()

#
# Glibmm, LibXML++
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
	XMLPP
	REQUIRED libxml++-2.6
)

include_directories(
	${XMLPP_INCLUDE_DIRS}
	${GLIBMM_INCLUDE_DIRS}
)
link_directories(
	${XMLPP_LIBRARY_DIRS}
	${GLIBMM_LIBRARY_DIRS}
	${PROJECT_BINARY_DIR}
)

add_definitions(
	${XMLPP_CFLAGS_OTHER}
	${GLIBMM_CFLAGS_OTHER}
)

#
# Slope
#

set(SLOPE_HAVE_GTK 0)
set(SLOPE_HAVE_PANGO 0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

pkg_check_modules(
	CAIRO
	REQUIRED cairo
)

include_directories(
	${CAIRO_INCLUDE_DIRS}
	"Externals library/Slope"
)
link_directories(
	${CAIRO_LIBRARY_DIRS}
)

add_definitions(
	${CAIRO_CFLAGS_OTHER}
)

CONFIGURE_FILE (
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
    "Externals library/Slope/slope/xyitem.c"
    "Externals library/Slope/slope/xyaxis.c"
    "Externals library/Slope/slope/legend.c"
    "Externals library/Slope/slope/slope.c"
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
	${XMLPP_LIBRARIES}
	muparser
	hpdf
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
		${XMLPP_LIBRARIES}
		muparser
		hpdf
	)

	target_compile_features(
		csuper-cli
		PRIVATE cxx_range_for
	)

ENDIF()
