cmake_minimum_required(VERSION 3.4)
project(cmdc)

set(CMDC_SOURCES "src/main.cpp")

if (NOT DEFINED MAYA_VERSION)
    set(MAYA_VERSION 2020 CACHE STRING "Maya version")
endif()

if (MAYA_VERSION GREATER 2020)
    set(PYBIND11_PYTHON_VERSION "3.7" CACHE STRING "")
else()
    set(PYBIND11_PYTHON_VERSION "2.7" CACHE STRING "")
endif()

if (NOT DEFINED MAYA_DEVKIT_ROOT)
    if (WIN32)
        set(MAYA_DEVKIT_ROOT "C:/Program Files/Autodesk/Maya${MAYA_VERSION}" CACHE STRING "Maya dev kit location")
    elseif(APPLE)
        set(MAYA_DEVKIT_ROOT "/Applications/Autodesk/maya${MAYA_VERSION}/Maya.app/Contents" CACHE STRING "Maya dev kit location")
    else()
        set(MAYA_DEVKIT_ROOT "/usr/autodesk/maya${MAYA_VERSION}/" CACHE STRING "Maya dev kit location")
    endif()
endif()

if (NOT EXISTS ${MAYA_DEVKIT_ROOT})
    message(FATAL_ERROR "Can not find Maya dev kit root at: ${MAYA_DEVKIT_ROOT}")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
set(Maya_DIR "${PROJECT_SOURCE_DIR}/cmake")

find_package(Maya REQUIRED)
add_subdirectory(pybind11)

add_custom_target(BuildMFnTypes ALL python ./scripts/mfn.py parse ${MAYA_DEVKIT_ROOT}
                  BYPRODUCTS ./src/MFn.Types.inl
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED ${CMDC_SOURCES})
add_dependencies(${PROJECT_NAME} BuildMFnTypes)
add_custom_command(TARGET ${PROJECT_NAME}
                    POST_BUILD
                    COMMAND python ./mfn.py clear -
                    BYPRODUCTS ./src/MFn.Types.inl
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/scripts"
)
pybind11_extension(${PROJECT_NAME})

if (APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OSMac_)
    set_target_properties(${PROJECT_NAME} PROPERTIES OSX_ARCHITECTURES "x86_64")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
                                              Maya::Foundation
                                              Maya::OpenMaya
                                              Maya::OpenMayaRender
                                              Maya::OpenMayaUI
                                              Maya::OpenMayaAnim
                                              Maya::OpenMayaFX
                                              Python::Lib
                                              pybind11::headers
                                              pybind11::windows_extras
                                              )