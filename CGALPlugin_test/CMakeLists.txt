cmake_minimum_required(VERSION 3.12)

project(CGALPlugin_test)

set(HEADER_FILES
)

set(SOURCE_FILES
)

sofa_find_package(Sofa.Testing REQUIRED)
sofa_find_package(image QUIET)


if(image_FOUND)
    find_package(Sofa.Component.StateContainer REQUIRED)
    find_package(SceneCreator REQUIRED)

    list(APPEND SOURCE_FILES MeshGenerationFromImage_test.cpp)

    # IMPORTANT NOTICE:
    # the following 4 lines must be put outside of the "if" section as soon as there is another source file added to the project
    add_definitions("-DSOFACGAL_TEST_RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/../scenes/data/\"")
    add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} CGALPlugin Sofa.Testing Sofa.Component.StateContainer SceneCreator image)
    add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

else()
    message(STATUS "CGALPlugin: could not find image, won't build MeshGenerationFromImage_test")
endif()
