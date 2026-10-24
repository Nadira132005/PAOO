cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(calculator STATIC src/Calculator.cpp)
add_library(Calculator::calculator ALIAS calculator)

target_compile_features(calculator PUBLIC cxx_std_17)
set_target_properties(calculator PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(calculator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS calculator
    EXPORT CalculatorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(calculator_cmake_dir "${CMAKE_INSTALL_LIBDIR}/cmake/Calculator")

install(EXPORT CalculatorTargets
    FILE CalculatorTargets.cmake
    NAMESPACE Lib::
    DESTINATION ${calculator_cmake_dir}
)

configure_package_config_file(
    cmake/CalculatorConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/CalculatorConfig.cmake"
    INSTALL_DESTINATION ${calculator_cmake_dir}
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CalculatorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CalculatorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CalculatorConfigVersion.cmake"
    DESTINATION ${calculator_cmake_dir}
)
