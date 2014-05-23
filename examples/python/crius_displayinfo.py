#!/usr/bin/env python


import os.path
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))+'/'
sys.path=[BASE_DIR+"../../src/"]+sys.path

I2C_BUS=int(sys.argv[1])
import sdisp

sdisp_ctx=sdisp.sdisp_new_crius(I2C_BUS)
print("width",sdisp.sdisp_display__getWidth(sdisp_ctx))
print("height",sdisp.sdisp_display__getHeight(sdisp_ctx))

sdisp.sdisp_close(sdisp_ctx)
