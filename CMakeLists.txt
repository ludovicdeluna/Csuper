cmake_minimum_required(VERSION 2.6)

project(Csuper C)


#Libcsuper
find_package(LibXml2 REQUIRED)

message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})

include_directories(${LIBXML2_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

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
	)
endif (WIN32)


#csuper-cli
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
	${LIBXML2_LIBRARIES}
)



#Csuper-gui

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(
	PkgConfig 
	REQUIRED
)
pkg_check_modules(
	GTK3
	REQUIRED gtk+-3.0>=3.6
)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(
	${GTK3_INCLUDE_DIRS}
)
link_directories(
	${GTK3_LIBRARY_DIRS}
)

# Add other flags to the compiler
add_definitions(
	${GTK3_CFLAGS_OTHER}
)

file(
        GLOB
        source_files_csuper
        Sources/csuper-gui/*
)

add_executable(
	csuper-gui
	${source_files_csuper}
)


#Configuration de l'édition de liens

# Link the target to the GTK+ and csuper libraries
target_link_libraries(
	csuper-gui 
	${GTK3_LIBRARIES}
	${LIBXML2_LIBRARIES}
	csuper
)
