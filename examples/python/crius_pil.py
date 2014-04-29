#!/usr/bin/env python


import os.path
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))+'/'
sys.path.append(BASE_DIR+"../../src/")

I2C_BUS=0
import sdisp

from PIL import Image, ImageDraw, ImageFont

sdisp_ctx=sdisp.sdisp_new_crius(I2C_BUS)

sdisp.sdisp_display__init(sdisp_ctx)
#set buffer content to 0
sdisp.sdisp_display__buffer_clear(sdisp_ctx)

#fill buffer with internal buffer image
#sdisp.sdisp_display__buffer_test(sdisp_ctx)


BLACK=0
WHITE=1

image = Image.new("1", (128, 64), BLACK)
draw = ImageDraw.Draw(image)
#draw.line([(0, h), (W - 1, h)], WHITE)
 

print(list(image.getdata()))


sdisp.sdisp_display__buffer_set_pixel(sdisp_ctx,0,0,1)

#display buffer
sdisp.sdisp_display__buffer_draw(sdisp_ctx)

sdisp.sdisp_close(sdisp_ctx)