libsdisp
============
![Display/Crius](doc/img/crius.jpg "Display/Crius")

a c library with abstraction for small displays

about
-------------------------
I stumbled across some of these o-LED displays and wondered how to access them on Linux. I started with the
I2C Crius which worked fine for me, but the implementation was fully done in Python. Each draw of a pixel resulted in
a call of a specific Python function. Then one day I had to use the code on a 400MHz ARM plattform and wasted about 90% of my CPU for the display. 

So I decided to move the display and bus functions to a c library and call them later via Python.


supported displays
-------------------------
  * Crius-OLED V 1.0
    * you probably need to fix the hardware: http://forum.arduino.cc/index.php?topic=159851.45
  * Crius-OLED V 1.2
  * Generic SSD1327 - not tested
  * Generic SSD1307 - not testet

install
-------------------------
All you need is cmake and a gcc. Then simply create makefiles with cmake and feel free to compile:


<pre>
git clone https://github.com/erazor83/libsdisp
cd libsdisp
cmake .
make
make install
</pre>

There are some options to enable different additional features:
  * WITH_SHARED - build shared .so file (libsdisp_shared.so)
  * WITH_EXAMPLES - build examples
  * WITH_SWIG_PYTHON - build python lib
  

<pre>
cmake -DWITH_SHARED=ON .
</pre>

There is even a libsdisp ebuild at http://wiki.erazor-zone.de/wiki:projects:linux:gentoo


For python you should probably also define your desired python target like this:
<pre>
cmake -D WITH_SHARED=ON -D WITH_EXAMPLES=ON -D WITH_SWIG_PYTHON=ON -DPYTHON_INCLUDE_DIR=$(echo /usr/include/python2*) -DPYTHON_LIBRARY=$(echo /usr/lib/libpython2.*.so) .
</pre>

functions
-------------------------
<pre>
#create display context
sdisp_t* sdisp_new_crius(uint8_t bus_nr);
sdisp_t* sdisp_new_ssd1306(uint8_t bus_nr);
sdisp_t* sdisp_new_ssd1327(uint8_t bus_nr);
void sdisp_close(sdisp_t*);

#display info functions
int16_t sdisp_display__getWidth(sdisp_t*);
int16_t sdisp_display__getHeight(sdisp_t*);
FEATURES_TYPE sdisp_display__getFeatures(sdisp_t*);

#display core functions
int8_t sdisp_display__init(sdisp_t*);
int8_t sdisp_display__test(sdisp_t*);
int8_t sdisp_display__clear(sdisp_t*);
int8_t sdisp_display__mov_to(sdisp_t*,uint8_t,uint8_t);
int8_t sdisp_display__detect(sdisp_t *ctx);

#display buffer functions
int8_t sdisp_display__buffer_draw(sdisp_t *ctx);
int8_t sdisp_display__buffer_clear(sdisp_t *ctx);
int8_t sdisp_display__buffer_test(sdisp_t *ctx);

int8_t sdisp_display__buffer_set_pixel(sdisp_t *ctx,uint16_t x, uint16_t y, uint8_t color);
int8_t sdisp_display__buffer_set_pixels(sdisp_t *ctx,uint16_t start, uint16_t len, uint8_t* color);
</pre>

Python
-------------------------
The library is meant as a speedup for python and includes (if enabled) a swig module.

In Python things would look like this:
<pre>
I2C_BUS=7
import sdisp

sdisp_ctx=sdisp.sdisp_new_crius(I2C_BUS)

sdisp.sdisp_display__init(sdisp_ctx)
#set buffer content to 0
sdisp.sdisp_display__buffer_clear(sdisp_ctx)

#fill buffer with internal buffer image
sdisp.sdisp_display__buffer_test(sdisp_ctx)

#display buffer
sdisp.sdisp_display__buffer_draw(sdisp_ctx)

sdisp.sdisp_close(sdisp_ctx)
</pre>

Some arguments have been abstracted to better fit Python:
<pre>
int sdisp_display__buffer_set_pixels(sdisp_t *ctx,int start, list pixels);
</pre>

license
-------------------------
GNU General Public License, version 2


credits
-------------------------
  
links
-------------------------
  * http://python.org
  * https://github.com/TobiasSimon/pyssd1306
