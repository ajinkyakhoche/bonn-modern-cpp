#################### Import the 'io_tools' library here ########################
find_library(
    IO_TOOLS 
    NAMES io_tools 
    PATHS ${LIBRARY_OUTPUT_PATH})

#################### Create a library 'image' below this line ##################
add_library(IMAGE image.cpp)

# link io_tools with 'image' library
target_link_libraries(IMAGE ${IO_TOOLS})    # why ${IO_TOOLS} and not IO_TOOLS????

add_executable(MAIN main.cpp)

target_link_libraries(MAIN IMAGE)