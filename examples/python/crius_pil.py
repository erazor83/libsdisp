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
#draw.line([(0, 0), (128, 64)], WHITE)
#draw.line([(0, 64), (128, 0)], WHITE)
 
font1 = ImageFont.truetype("verdana.ttf", 12)
font2 = ImageFont.truetype("verdana.ttf", 10)

draw.text((0, 0),"libsdisp",WHITE,font=font1)
draw.text((0, 10),"   Small",WHITE,font=font2)
draw.text((0, 18),"     Device",WHITE,font=font2)
draw.text((0, 26),"       Display",WHITE,font=font2)
draw.text((0, 34),"         Library",WHITE,font=font2)
draw.line([(0, 60), (128, 60)], WHITE)
 
#print(list(image.getdata()))


#sdisp.sdisp_display__buffer_set_pixel(sdisp_ctx,0,0,1)
sdisp.sdisp_display__buffer_set_pixels(
	sdisp_ctx,
	0,
	list(image.getdata())
)



#display buffer
sdisp.sdisp_display__buffer_draw(sdisp_ctx)

sdisp.sdisp_close(sdisp_ctx)