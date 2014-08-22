cmake_minimum_required(VERSION 2.6)

project(Csuper C)


#Libcsuper
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
	csuper
)
