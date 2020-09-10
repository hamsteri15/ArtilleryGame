CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


PROJECT(ArtilleryGame)

message("COMPILER ID " ${CMAKE_CXX_COMPILER_ID})
INCLUDE(cmake/StandardProjectSettings.cmake)


message("BINARY DIR" ${CMAKE_BINARY_DIR})



# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_11)
#target_compile_features(project_options INTERFACE cxx_std_20)


#Global compiler flags

set(OptimizationFlags
    -pedantic 
    -msse3 
    -mavx 
    -mfpmath=sse 
    -O3
    -ffast-math 
    -march=native 
    -ftree-vectorize 
)

add_compile_options(${OptimizationFlags})






# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

#set(SFML_DIR "/usr/share/SFML")
set(SFML_DIR "/usr/include/SFML")
message(${SFML_DIR})

#find_package(SFML REQUIRED COMPONENTS graphics window system)


option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)



#Set library and binary paths
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)




    

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/containers)
#Build solvers
INCLUDE_DIRECTORIES(src)
ADD_SUBDIRECTORY(src)




