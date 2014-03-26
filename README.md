libsdisp
============
![Display/Crius](doc/img/crius.jpg "Display/Crius")

a c library with abstraction for small displays

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
git clone https://github.com/erazor83/libsdisp
cd libsdisp
cmake .
make
make install
</pre>

There are some options to enable different additional features:
  * WITH_SHARED - build shared .so file (libsdisp_shared.so)
  * WITH_EXAMPLES - build examples

<pre>
cmake -DWITH_SHARED=1 .
</pre>

There is even a libsdisp ebuild at http://wiki.erazor-zone.de/wiki:projects:linux:gentoo

license
-------------------------
GNU General Public License, version 2


credits
-------------------------
  
links
-------------------------
  
