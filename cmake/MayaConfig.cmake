add_library(Python::Lib SHARED IMPORTED)

if (WIN32)
    set(PYTHON_OS_NAME "windows")
    string(REPLACE "." "" PYTHON_VERSION_NO ${PYBIND11_PYTHON_VERSION})
    set(PYTHON_LIB_FILENAME "python${PYTHON_VERSION_NO}.lib")

    if (${MAYA_VERSION} VERSION_GREATER_EQUAL "2022")
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python${PYTHON_VERSION_NO}/Python")
    elseif(${MAYA_VERSION} VERSION_EQUAL "2018" OR ${MAYA_VERSION} VERSION_EQUAL "2019")
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python${PYBIND11_PYTHON_VERSION}")
    else()
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python")
    endif()

elseif (APPLE)
    set(PYTHON_OS_NAME "mac")
    set(PYTHON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/os/mac/${PYBIND11_PYTHON_VERSION}/include")

    if (${PYBIND11_PYTHON_VERSION} VERSION_EQUAL "3.7")
        set(PYTHON_LIB_FILENAME "libpython${PYBIND11_PYTHON_VERSION}m.dylib")
    else()
        set(PYTHON_LIB_FILENAME "libpython${PYBIND11_PYTHON_VERSION}.dylib")
    endif()
else()
    set(PYTHON_OS_NAME "linux")
    if (${MAYA_VERSION} VERSION_GREATER_EQUAL "2022")
        string(REPLACE "." "" PYTHON_VERSION_NO ${PYBIND11_PYTHON_VERSION})
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python${PYTHON_VERSION_NO}/Python")
    elseif(${MAYA_VERSION} VERSION_EQUAL "2018" OR ${MAYA_VERSION} VERSION_EQUAL "2019")
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python${PYBIND11_PYTHON_VERSION}")
    else()
        set(PYTHON_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include/Python")
    endif()

    if (${PYBIND11_PYTHON_VERSION} VERSION_EQUAL "3.7")
        set(PYTHON_LIB_FILENAME "libpython${PYBIND11_PYTHON_VERSION}m.so")
    else()
        set(PYTHON_LIB_FILENAME "libpython${PYBIND11_PYTHON_VERSION}.so")
    endif()

endif()

set(PYTHON_LIB "${PROJECT_SOURCE_DIR}/os/${PYTHON_OS_NAME}/${PYBIND11_PYTHON_VERSION}/lib/${PYTHON_LIB_FILENAME}")

message("Python library set to: ${PYTHON_LIB}")
message("Python include set to: ${PYTHON_INCLUDE_DIR}")

add_library(Maya::Foundation SHARED IMPORTED)
add_library(Maya::OpenMaya SHARED IMPORTED)
add_library(Maya::OpenMayaRender SHARED IMPORTED)
add_library(Maya::OpenMayaUI SHARED IMPORTED)
add_library(Maya::OpenMayaAnim SHARED IMPORTED)
add_library(Maya::OpenMayaFX SHARED IMPORTED)

set(MAYA_INCLUDE_DIR "${MAYA_DEVKIT_ROOT}/include")
set(MAYA_LIB_DIR "${MAYA_DEVKIT_ROOT}/lib")

if (WIN32)
    set_target_properties(Python::Lib PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PYTHON_INCLUDE_DIR}
        IMPORTED_IMPLIB ${PYTHON_LIB}
    )

    set_target_properties(Maya::Foundation PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/Foundation.lib"
    )

    set_target_properties(Maya::OpenMaya PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/OpenMaya.lib"
    )

    set_target_properties(Maya::OpenMayaRender PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/OpenMayaRender.lib"
    )

    set_target_properties(Maya::OpenMayaUI PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/OpenMayaUI.lib"
    )

    set_target_properties(Maya::OpenMayaAnim PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/OpenMayaAnim.lib"
    )

    set_target_properties(Maya::OpenMayaFX PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_IMPLIB "${MAYA_LIB_DIR}/OpenMayaFX.lib"
)
elseif(APPLE)
    set_target_properties(Python::Lib PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PYTHON_INCLUDE_DIR}
        IMPORTED_LOCATION ${PYTHON_LIB}
        IMPORTED_SONAME "libpython${PYBIND11_PYTHON_VERSION}m.dylib"
    )

    set_target_properties(Maya::Foundation PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libFoundation.dylib"
        IMPORTED_SONAME "libFoundation.dylib"
    )

    set_target_properties(Maya::OpenMaya PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMaya.dylib"
        IMPORTED_SONAME "libOpenMaya.dylib"
    )

    set_target_properties(Maya::OpenMayaRender PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaRender.dylib"
        IMPORTED_SONAME "libOpenMayaRender.dylib"
    )

    set_target_properties(Maya::OpenMayaUI PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaUI.dylib"
        IMPORTED_SONAME "libOpenMayaUI.dylib"
    )

    set_target_properties(Maya::OpenMayaAnim PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaAnim.dylib"
        IMPORTED_SONAME "libOpenMayaAnim.dylib"
    )

    set_target_properties(Maya::OpenMayaFX PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaFX.dylib"
        IMPORTED_SONAME "libOpenMayaFX.dylib"
    )
else()
    set_target_properties(Python::Lib PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PYTHON_INCLUDE_DIR}
        IMPORTED_LOCATION ${PYTHON_LIB}
        IMPORTED_SONAME "libpython${PYBIND11_PYTHON_VERSION}m.so"
    )

    set_target_properties(Maya::Foundation PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libFoundation.so"
        IMPORTED_SONAME "libFoundation.so"
    )

    set_target_properties(Maya::OpenMaya PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMaya.so"
        IMPORTED_SONAME "libOpenMaya.so"
    )

    set_target_properties(Maya::OpenMayaRender PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaRender.so"
        IMPORTED_SONAME "libOpenMayaRender.so"
    )

    set_target_properties(Maya::OpenMayaUI PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaUI.so"
        IMPORTED_SONAME "libOpenMayaUI.so"
    )

    set_target_properties(Maya::OpenMayaAnim PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaAnim.so"
        IMPORTED_SONAME "libOpenMayaAnim.so"
    )

    set_target_properties(Maya::OpenMayaFX PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${MAYA_INCLUDE_DIR}
        IMPORTED_LOCATION "${MAYA_LIB_DIR}/libOpenMayaFX.so"
        IMPORTED_SONAME "libOpenMayaFX.so"
    )
endif()