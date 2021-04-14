# main project library
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
               Complex.hpp
               ComplexCache.hpp
               ComplexNumbers.hpp
               ComplexTable.hpp
               ComplexValue.hpp
               ComputeTable.hpp
               Control.hpp
               DDexport.hpp
               DDpackage.hpp
               Definitions.hpp
               Edge.hpp
               GateMatrixDefinitions.hpp
               NoiseOperationTable.hpp
               ToffoliTable.hpp
               UnaryComputeTable.hpp
               UniqueTable.hpp)

# set include directories
target_include_directories(${PROJECT_NAME} INTERFACE .)

# set required C++ standard and disable compiler specific extensions
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# set compiler flags depending on compiler
if (MSVC)
	target_compile_options(${PROJECT_NAME} INTERFACE /utf-8)
else ()
	target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra $<$<CONFIG:DEBUG>:-Og>)
	if (BINDINGS)
		# adjust visibility settings for building Python bindings
		target_compile_options(${PROJECT_NAME} INTERFACE -fvisibility=hidden)
	endif ()
	if (NOT DEPLOY)
		# only include machine-specific optimizations when building for the host machine
		target_compile_options(${PROJECT_NAME} INTERFACE -mtune=native -march=native)
	endif ()
endif ()

if (GENERATE_POSITION_INDEPENDENT_CODE OR BINDINGS)
	include(CheckPIESupported)
	check_pie_supported()
	set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
endif ()

# add coverage compiler and linker flag to the library and all targets that link against it, if COVERAGE is set
if (COVERAGE)
	target_compile_options(${PROJECT_NAME} INTERFACE --coverage)
	target_link_libraries(${PROJECT_NAME} INTERFACE --coverage)
endif ()

# add JKQ alias
add_library(JKQ::DDpackage ALIAS ${PROJECT_NAME})
