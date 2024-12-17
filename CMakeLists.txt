cmake_minimum_required(VERSION 3.10)
project(ExerciseProject)

# Function to create executables for each subdirectory
function(add_subdirectory_executable dir count)
  add_executable(${count} "exercises/${dir}/main.cpp")  # Create executable named after directory
endfunction()

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Iterate through subdirectories of "exercise"
set(cnt 0)
file(GLOB subdirectories "exercises/*")
foreach(subdir ${subdirectories})
  if(IS_DIRECTORY ${subdir})  # Check if item is a directory
    # get_filename_component(LAST_DIR_NAME ${subdir} DIRECTORY)
    get_filename_component(LAST_DIR_NAME ${subdir} NAME)
    # message(STATUS ${LAST_DIR_NAME})
    # message(STATUS ${cnt})
    add_subdirectory_executable(${LAST_DIR_NAME} ${cnt})
    math(EXPR cnt "${cnt} + 1")
  endif()
endforeach()

