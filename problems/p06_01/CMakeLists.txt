add_library(p06_01 src/p06_01.cpp)
target_include_directories(p06_01 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(p06_01_exe src/p06_01_main.cpp)
target_link_libraries(p06_01_exe PRIVATE p06_01)
