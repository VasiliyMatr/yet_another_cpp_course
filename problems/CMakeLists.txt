add_subdirectory(p06_01)

add_executable(p01_01 p01_01.cpp)

if (NOT GTest_FOUND)
    return()
endif ()

function (add_problem_tests PROBLEM_NAME SRC)
    set(TARGET ${PROBLEM_NAME}_tests)
    add_executable(${TARGET} tests_main.cpp ${SRC})

    target_link_libraries(${TARGET}
    PRIVATE
        ${GTEST_LIBRARIES}
        pthread
    )

    gtest_discover_tests(${TARGET})
endfunction ()

add_problem_tests(p02 p02_tests.cpp)
add_problem_tests(p03 p03_tests.cpp)
add_problem_tests(p04 p04_tests.cpp)
add_problem_tests(p11 p11_tests.cpp)
