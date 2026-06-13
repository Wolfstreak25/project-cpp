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

# Locate SFML 3
find_package(SFML 3 COMPONENTS graphics audio network window system REQUIRED)

# Build Timber as executable
add_executable(Timber ${SOURCE_FILES} ${HEADER_FILES})

# Configure C++ standard
target_compile_features(Timber PRIVATE cxx_std_20)

# Link SFML libraries
target_link_libraries(Timber PRIVATE 
    SFML::Graphics 
    SFML::Audio 
    SFML::Network 
    SFML::Window 
    SFML::System
)

# Set debugger working directory to current source folder (where assets folder resides)
set_target_properties(Timber PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Post-build step to copy all required DLLs next to executable
add_custom_command(TARGET Timber POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-audio-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-audio-d-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-graphics-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-graphics-d-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-network-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-network-d-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-system-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-system-d-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-window-3.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/sfml-window-d-3.dll"
        $<TARGET_FILE_DIR:Timber>
)
