file(GLOB TESTS "*_test.c")

find_package(CMocka REQUIRED)

message(STATUS "CMocka vars: ${CMOCKA_LIBRARIES} ${CMOCKA_INCLUDE_DIR}")

foreach (TEST ${TESTS})
    string(REGEX REPLACE ".*/([^/]+).c" "\\1" NAME ${TEST})
    message("Adding test ${NAME}")
    add_executable(${NAME} "${NAME}.c" assertions.c stream_expectations.c)
    target_link_libraries(${NAME} ${CMOCKA_LIBRARIES})
    target_link_libraries(${NAME} cbor)
    target_include_directories(${NAME} PUBLIC ${CMOCKA_INCLUDE_DIR})
    # See https://stackoverflow.com/a/10824578/499521
    ADD_TEST(ctest_build_test_${NAME}
            "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${NAME})
    ADD_TEST(ctest_run_${NAME} ${NAME})
    SET_TESTS_PROPERTIES(ctest_run_${NAME}
            PROPERTIES DEPENDS ctest_build_test_${NAME})
    add_dependencies(coverage ${NAME})
endforeach (TEST)

add_executable(cpp_linkage_test cpp_linkage_test.cpp)
target_link_libraries(cpp_linkage_test cbor)