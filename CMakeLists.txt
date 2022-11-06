cmake_minimum_required(VERSION 3.16.3)

set(This linalg)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Testing

enable_testing()

# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()
endif()

# CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodules was not downloaded! GIT_SUBMODULE was turned off or failed")
endif()

add_subdirectory(googletest)

set (Headers
    linalg/Vector.hpp linalg/Matrix.hpp linalg/LinSys.hpp
)

set (Sources
    linalg/Vector.cpp linalg/Matrix.cpp linalg/LinSys.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)