# set required cmake version
cmake_minimum_required(VERSION 3.14...3.19)

# project definition
project(DDPackage
        LANGUAGES CXX
        VERSION 2.0.2
        DESCRIPTION "JKQ decision diagram package tailored to quantum computing")

# enable organization of targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# configuration options
option(DEPLOY "Configure for deployment")
option(BINDINGS "Configure for building Python bindings")
option(COVERAGE "Configure for coverage report generation")
option(BUILD_DD_PACKAGE_TESTS "Also build tests for DD package")

# build type settings
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()


set(USE_SANITIZER
        "Address;Undefined"
        CACHE
        STRING
        "Compile with a sanitizer. Options are: Address, Memory, MemoryWithOrigins, Undefined, Thread, Leak, 'Address;Undefined'"
        )

function(append value)
    foreach(variable ${ARGN})
        set(${variable}
                "${${variable}} ${value}"
                PARENT_SCOPE)
    endforeach(variable)
endfunction()

if(USE_SANITIZER)
    append("-fno-omit-frame-pointer" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)

    if(UNIX)

        if(USE_SANITIZER MATCHES "([Aa]ddress);([Uu]ndefined)"
                OR USE_SANITIZER MATCHES "([Uu]ndefined);([Aa]ddress)")
            message(STATUS "Building with Address, Undefined sanitizers")
            append("-fsanitize=address,undefined" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        elseif(USE_SANITIZER MATCHES "([Aa]ddress)")
            # Optional: -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
            message(STATUS "Building with Address sanitizer")
            append("-fsanitize=address" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        elseif(USE_SANITIZER MATCHES "([Mm]emory([Ww]ith[Oo]rigins)?)")
            # Optional: -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2
            append("-fsanitize=memory" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
            if(USE_SANITIZER MATCHES "([Mm]emory[Ww]ith[Oo]rigins)")
                message(STATUS "Building with MemoryWithOrigins sanitizer")
                append("-fsanitize-memory-track-origins" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
            else()
                message(STATUS "Building with Memory sanitizer")
            endif()
        elseif(USE_SANITIZER MATCHES "([Uu]ndefined)")
            message(STATUS "Building with Undefined sanitizer")
            append("-fsanitize=undefined" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
            if(EXISTS "${BLACKLIST_FILE}")
                append("-fsanitize-blacklist=${BLACKLIST_FILE}" CMAKE_C_FLAGS
                        CMAKE_CXX_FLAGS)
            endif()
        elseif(USE_SANITIZER MATCHES "([Tt]hread)")
            message(STATUS "Building with Thread sanitizer")
            append("-fsanitize=thread" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        elseif(USE_SANITIZER MATCHES "([Ll]eak)")
            message(STATUS "Building with Leak sanitizer")
            append("-fsanitize=leak" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        else()
            message(
                    FATAL_ERROR "Unsupported value of USE_SANITIZER: ${USE_SANITIZER}")
        endif()
    elseif(MSVC)
        if(USE_SANITIZER MATCHES "([Aa]ddress)")
            message(STATUS "Building with Address sanitizer")
            append("-fsanitize=address" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
        else()
            message(
                    FATAL_ERROR
                    "This sanitizer not yet supported in the MSVC environment: ${USE_SANITIZER}"
            )
        endif()
    else()
        message(FATAL_ERROR "USE_SANITIZER is not supported on this platform.")
    endif()

endif()

# add main library code
include(GNUInstallDirs)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Complex.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/ComplexCache.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/ComplexNumbers.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/ComplexValue.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Control.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Definitions.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Edge.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Export.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/GateMatrixDefinitions.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/Package.hpp>

        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/ComplexTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/ComputeTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/MagnitudeTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/NoiseOperationTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/PhaseTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/ToffoliTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/UnaryComputeTable.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/dd/tables/UniqueTable.hpp>)

# set include directories
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>)

# set required C++ standard and disable compiler specific extensions
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# set compiler flags depending on compiler
if (MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE /utf-8)
else ()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra $<$<CONFIG:DEBUG>:-Og> -fno-math-errno -ffinite-math-only -fno-rounding-math -fno-signaling-nans -fno-signed-zeros)
    if (NOT DEPLOY)
        # only include machine-specific optimizations when building for the host machine
        target_compile_options(${PROJECT_NAME} INTERFACE -mtune=native -march=native)
    endif ()
endif ()

# add coverage compiler and linker flag to the library and all targets that link against it, if COVERAGE is set
if (COVERAGE)
    target_compile_options(${PROJECT_NAME} INTERFACE --coverage)
    target_link_libraries(${PROJECT_NAME} INTERFACE --coverage)
endif ()

# add JKQ alias
add_library(JKQ::DDPackage ALIAS ${PROJECT_NAME})

macro(enable_lto TARGET_NAME)
    # enable interprocedural optimization if it is supported (Clang's ThinLTO does not work with Ubuntu 20.04's default linker at the moment)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported)
    if (ipo_supported AND NOT ((${CMAKE_SYSTEM_NAME} MATCHES "Linux") AND (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")))
        set_target_properties(${TARGETNAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif ()
endmacro()

# add test code
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR BUILD_DD_PACKAGE_TESTS)
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
        message(FATAL_ERROR "GoogleTest submodule not cloned properly. Please run `git submodule update --init --recursive` from the main project directory")
    endif ()

    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()
