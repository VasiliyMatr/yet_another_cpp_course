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

add_problem_tests(p02_02 p02_tests.cpp)
