set(TEST_SOURCES
    test_bim_object.c
    test_bim_polygon_tools.c
    test_bim_evac.c
)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/thirdparty/arraylist
        ${PROJECT_SOURCE_DIR}/tests
)

foreach(test IN LISTS TEST_SOURCES)
    add_executable(${test} ${test})
    target_compile_definitions(${test}
        PRIVATE
            ROOT_PATH="${CMAKE_SOURCE_DIR}/res"
    )
    target_include_directories(${test}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/thirdparty/arraylist
    )
    target_link_libraries(${test}
        PRIVATE
            ${PROJECT_LIB_STATIC}
    )
    add_test(
        NAME ${test}
        COMMAND ${test}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
    )
endforeach()
