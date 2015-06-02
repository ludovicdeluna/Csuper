cmake_minimum_required(VERSION 2.6)

project(Csuper CXX)

#
# Portable
#

IF(PORTABLE MATCHES "TRUE")
	add_definitions(-DPORTABLE)
ENDIF()

#
# Glibmm
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
)

add_definitions(
	${XMLPP_CFLAGS_OTHER}
	${GLIBMM_CFLAGS_OTHER}
)

#
# libcsuper
#


file(
        GLOB
        source_files_libcsuper
        Sources/libcsuper/*
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
)

target_compile_features(
	csuper
	PRIVATE cxx_range_for
)

#
# csuper-cli
#

file(
        GLOB
        source_files_csuper-cli
        Sources/csuper-cli/*
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
)

target_compile_features(
	csuper-cli
	PRIVATE cxx_range_for
)
