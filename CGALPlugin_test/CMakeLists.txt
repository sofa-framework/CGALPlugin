cmake_minimum_required(VERSION 3.12)

project(CGALPlugin_test)

set(HEADER_FILES
)

set(SOURCE_FILES
)

sofa_find_package(Sofa.Testing REQUIRED)
sofa_find_package(image QUIET)

list(APPEND SOURCE_FILES Refine2DMesh_test.cpp)

if(image_FOUND)
    find_package(Sofa.Component.StateContainer REQUIRED)    

    list(APPEND SOURCE_FILES MeshGenerationFromImage_test.cpp)
endif()

add_definitions("-DSOFACGAL_TEST_RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/../scenes/data/\"")
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} CGALPlugin Sofa.Testing SceneCreator )

if(image_FOUND)
    target_link_libraries(${PROJECT_NAME} Sofa.Component.StateContainer image)
endif()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
