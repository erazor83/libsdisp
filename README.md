libsdsp
============


a speedy C library for accessing Dynamixel AX servos


about
-------------------------
TODO

supported displays
-------------------------
  * Crius-OLED
  * 

install
-------------------------
All you need is cmake and a gcc. Then simply create makefiles with cmake and feel free to compile:


<pre>
git clone https://github.com/erazor83/libsdsp
cd libsdsp
cmake .
make
make install
</pre>

There are some options to enable different additional features:
  * WITH_SHARED - build shared .so file (libdynamixel_shared.so)
  * WITH_EXAMPLES - build examples

<pre>
cmake -DWITH_SHARED=1 .
</pre>

There is even a libsdsp ebuild at http://wiki.erazor-zone.de/wiki:projects:linux:gentoo

license
-------------------------
GNU General Public License, version 2


credits
-------------------------
  
links
-------------------------
  