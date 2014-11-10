cmake_minimum_required (VERSION 2.8.2)

set( THIRD_PARTY  $ENV{HOME}/  CACHE PATH "third party directory" )

set ( CMAKE_INCLUDE_PATH "${THIRD_PARTY}/include" )

set ( CMAKE_LIBRARY_PATH "${THIRD_PARTY}/lib/mac64" ) # TODO fix for other OS

set ( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project (instrumentrepo)


find_package ( Poco REQUIRED )

include_directories (${THIRD_PARTY}/include ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(instrumentrepo main.cpp)
target_link_libraries(instrumentrepo ${POCO_LIB_FOUNDATION} ${POCO_LIB_NET} ${POCO_LIB_NETSSL} )
