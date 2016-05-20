cmake_minimum_required ( VERSION 2.8 )
project ( PQSORT_LIB C )

set ( LIBRARY_NAME "pqsort_lib" )
set ( LIBRARY_HEADER 
	pqsort.h
)
set ( LIBRARY_SOURCE_FILES  
	pqsort.c
)

set ( LIBRARY_TYPE "STATIC" CACHE PATH "Static or shared version of library" )

if ( MSVC )
	add_definitions ( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC )

add_library ( ${LIBRARY_NAME} ${LIBRARY_TYPE} ${LIBRARY_SOURCE_FILES} )
