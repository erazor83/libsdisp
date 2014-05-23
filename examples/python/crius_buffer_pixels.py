#!/usr/bin/env python


import os.path
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))+'/'
sys.path.append(BASE_DIR+"../../src/")

I2C_BUS=7
import sdisp

sdisp_ctx=sdisp.sdisp_new_crius(I2C_BUS)

sdisp.sdisp_display__init(sdisp_ctx)
#set buffer content to 0
sdisp.sdisp_display__buffer_clear(sdisp_ctx)

#fill buffer with internal buffer image
#sdisp.sdisp_display__buffer_test(sdisp_ctx)


sdisp.sdisp_display__buffer_set_pixels(sdisp_ctx,0,[1,0,1,0,0,1,1,1])


#display buffer
sdisp.sdisp_display__buffer_draw(sdisp_ctx)

sdisp.sdisp_close(sdisp_ctx)
