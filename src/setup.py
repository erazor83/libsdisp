#!/usr/bin/env python

"""
setup.py file for libsdisp bindings.
"""

from distutils.core import setup,Extension

libsdisp_module = Extension('_sdisp',
	libraries=['sdisp'],
	sources=['sdispPYTHON_wrap.c'],
	)

setup (name = 'libsdisp',
	version = '0.1.0',
	author = "Alexander Krause",
	description = """Simple libsdisp bindings.""",
	ext_modules = [libsdisp_module],
	py_modules = ["sdisp"],
)
