#!/usr/bin/env python


import os.path
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))+'/'
sys.path.append(BASE_DIR+"../../src/")

import sdisp

print("sdisp version:")
print(
	sdisp.libsdisp_version_major,
	sdisp.libsdisp_version_minor,
	sdisp.libsdisp_version_micro
)
