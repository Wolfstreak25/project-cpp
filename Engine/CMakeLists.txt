# Automatically find all headers and source files for this specific project
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Map physical folders to Visual Studio filters
foreach(FILE_PATH IN LISTS HEADER_FILES SOURCE_FILES)
    get_filename_component(PARENT_DIR "${FILE_PATH}" DIRECTORY)
    file(RELATIVE_PATH REL_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${PARENT_DIR}")
    string(REPLACE "/" "\\" FILTER_GROUP "${REL_DIR}")
    
    if(FILTER_GROUP)
        source_group("${FILTER_GROUP}" FILES "${FILE_PATH}")
    else()
        source_group("Root" FILES "${FILE_PATH}")
    endif()
endforeach()

# Engine is a library
add_library(Engine STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Expose include directories for targets that link Engine
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
