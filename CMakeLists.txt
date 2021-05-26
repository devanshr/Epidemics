# Author: 

# Name of your plugin and sources.
set(pluginName	Epidemics)
set(SOURCES		epidemics_plugin.cpp
			)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_cxx_flag("-pthread")
	add_cxx_flag("-std=c++17")
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS}-pthread -std=c++17 -march=native")
	add_cxx_flag("-march=native")
endif()

IF(NOT ConstrainedOptimization)
	message(FATAL_ERROR "\nEpidemics needs ConstrainedOptimization plugin activated:\ncmake -DConstrainedOptimization=ON ..")
ENDIF()	
################################################################################
# The code below doesn't have to be changed (usually)
################################################################################
cmake_minimum_required(VERSION 2.6)

project(UG_PLUGIN_${pluginName})

# include the definitions and dependencies for ug-plugins.
include(${UG_ROOT_CMAKE_PATH}/ug_plugin_includes.cmake)

if(buildEmbeddedPlugins)
	# add the sources to ug4's sources
	EXPORTSOURCES(${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES})
else(buildEmbeddedPlugins)
	# create a shared library from the sources and link it against ug4.
	add_library(${pluginName} SHARED ${SOURCES})
	target_link_libraries (${pluginName} ug4)
endif(buildEmbeddedPlugins)
