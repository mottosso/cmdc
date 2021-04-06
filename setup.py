from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext

import os

__version__ = "0.1.1"

ext_modules = [
    Pybind11Extension(
        "cmdc",
        ["src/main.cpp"],

        library_dirs=os.environ.get("LIBRARY_PATH", "").split(os.pathsep),
        include_dirs=os.environ.get("INCLUDE_PATH", "").split(os.pathsep),
        libraries=os.environ.get("LIBRARIES").split(),
        define_macros=[('VERSION_INFO', __version__)],
    ),
]

setup(
    name="cmdc",
    version=__version__,
    author="Marcus Ottosson",
    author_email="me@mottosso.com",
    url="https://github.com/mottosso/cmdc",
    description="A replacement for maya.api.OpenMaya",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
