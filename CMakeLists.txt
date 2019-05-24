cmake_minimum_required(VERSION 3.5)
project (LifeGame VERSION 1.0.0 LANGUAGES CXX )

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Driver target ===

add_executable( glife "src/driver_life.cpp" "src/lodepng.cpp" )
