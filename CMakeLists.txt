cmake_minimum_required(VERSION 2.6)

project(Csuper)

#
#Glibmm
#

find_package(
	PkgConfig 
	REQUIRED
)
pkg_check_modules(
	GLIBMM
	REQUIRED glibmm-2.4
)

include_directories(
	${GLIBMM_INCLUDE_DIRS}
)
link_directories(
	${GLIBMM_LIBRARY_DIRS}
)

add_definitions(
	${GLIBMM_CFLAGS_OTHER}
)

#
#Libcsuper
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
)

#
#csuper-cli
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
)
