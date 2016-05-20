cmake_minimum_required ( VERSION 2.8 )

option ( BUILD_TESTING "Enable/disable testing" ON )


find_package(OpenMP)
if (OPENMP_FOUND)
    message ( "-- OpenMP enabled" )
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message ( "-- OpenMP don't enabled, but not found" )
endif(OPENMP_FOUND)

add_subdirectory(src)

INCLUDE(CTest)

if ( BUILD_TESTING )
	message ( "-- Testing enabled" )
	add_subdirectory(gtest)
	add_subdirectory(tests)
endif ( BUILD_TESTING )