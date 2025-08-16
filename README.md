# amiga-qt6
Qt 6.2.0 for AmigaOS 4.1 Final Edition - with optional support for OpenGLES2

<h2>Build instructions</h2>

Build instructions no longer apply. Instead, download the latest release and follow instructions therein.<br>

  
<h2>Shared object dependencies</h2>

Qt6 is currently configured to support static builds only.  
<br>

<h2>Recommended setup</h2>

Qt6 for amiga is known to work with the following setup :
<br>
<ul>
<li>X5000 (unconfirmed on other platforms)</li>
</ul>

<br>

<h2>How to build a Qt6 project</h2>

cd into the source directory containing the .pro file. Then do:

> /qt6-amiga/bin/qmake
>
> make

Transfer the resulting executable to the amiga and test. Good luck :).


<h2>Credits</h2>

Qt6 for AmigaOS4 is used under the GNU Lesser General Public License version 3 (LGPLv3).
Source code is available at: https://github.com/elfpipe/amiga-qt6