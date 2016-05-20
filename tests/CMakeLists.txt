enable_testing()

set(LIBS ${LIBS} pqsort_lib)
set(GLIBS ${LIBS} gtest gtest_main)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_pqsort_int pqsort_int.cpp)
target_link_libraries (test_pqsort_int ${GLIBS})
add_test(test_pqsort_int test_pqsort_int)


add_executable(pqsort_gen_int_file pqsort_gen_int_file.cpp)
target_link_libraries (pqsort_gen_int_file ${LIBS})

add_executable(pqsort_int_file pqsort_int_file.cpp)
target_link_libraries (pqsort_int_file ${LIBS})
