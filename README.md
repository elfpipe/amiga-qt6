# amiga-qt6
Qt 6.2.0 for AmigaOS 4.1 Final Edition with OpenGLES2

Build instructions:

First of all : Do not try to build on AmigaOS. Get Ubuntu and download this toolchain:

https://drive.google.com/file/d/16DZ1GGv6vHmHtu1Mh3Doj2ptnDOZ2jF2/view?usp=sharing

Extract to /opt/adtools and do

> PATH=$PATH:/opt/adtools/bin

This will get you ready to build Qt6.

Notes: Qt 6 builds with GCC 11 and a slightly modified minimal SDK. Both are contained in the above link.

Configure and build:

> git clone https://github.com/alfkil/amiga-qt6.git
> mkdir qt6-amiga-build
> cd qt6-amiga-build
> ../amiga-qt6/configure-amiga.sh
> make
> sudo make install

This will give you an almost full install in /qt5-amiga. There are a few files, that are not copied automatically, so you need to

> sudo cp lib/* /qt5-amiga/lib

If you succeed in building Qt6, please send me a note. :)

HOW TO BUILD A Qt6 PROJECT:

cd into the directory containing the .pro file. Then do:

> /qt5-amiga/bin/qmake
> make

Transfer your files to the amiga and test. Good luck :).
