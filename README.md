# amiga-qt6
Qt 6.2.0 for AmigaOS 4.1 Final Edition - with optional support for OpenGLES2

<h2>Build instructions</h2>

First of all : Do not try to build on AmigaOS. Get Ubuntu and go to this page :

https://github.com/sba1/adtools

Follow the instructions here to set up the adtools cross toolchain. Qt6 is known to build and work with gcc 9 and 11.

<h2>Configure and build on linux</h2>

> git clone https://github.com/alfkil/amiga-qt6.git
> 
> mkdir qt6-amiga-build
> 
> cd qt6-amiga-build
> 
> ../amiga-qt6/configure-amiga.sh
> 
> make
> 
> sudo make install

This will install Qt6 into /qt6-amiga (in the root of your linux machine). 

You need to copy this entire directory unto your amiga hd and create

> assign qt6-amiga: <yourhd>:<yourpath>

on the amiga side.

Also you need to copy your truetype fonts from FONTS:_TrueType/ and into

> qt6-amiga:lib/fonts

Qt6 will warn you of this last step, if you forget.

Keep in mind : To run Qt6 apps on OS4.1, you probably need to update the following files from adtools into SYS:sobjs/

<ul>
<li>libatomic.so</li>
<li>libgcc.so</li>
<li>libstdc++.so</li>
<li>libc.so</li>
</ul>

<br>

<h2>Recommended setup</h2>

Qt6 for amiga is known to work with the following setup :
<br>
<ul>
<li>X5000 (untested on other platforms)</li>
<li>exec-sg 54.54</li>
<li>dos.library 54.121</li>
<li>ramlib 54.2</li>
<li>elf.library 53.39</li>
<li>pthreads.library 53.12</li>
<li>newlib.library 53.83</li>
</ul>

<br>

<h2>How to build a Qt6 project</h2>

cd into the source directory containing the .pro file. Then do:

> /qt6-amiga/bin/qmake
>
> make

Transfer the resulting executable to the amiga and test. Good luck :).
