[Deprecated] Generic/Windows Classes and Functions Library
==========================================================

Author: metamaker

This library provides framework over Win32 API to create GUI applications under Windows. It is only
an example of how such framework could be built and isn't intended to be used by anyone.

Building the library
--------------------

You need CMake (<http://www.cmake.org/>) to build this library. Example of how to build the library is for
Visual Studio's nmake but you can use pretty same steps sequence for any other generator. Building steps are
next:

1. Open command line and change current directory with **cd** command to the directory where you unpacked the library's source code.
2. Create new empty directory **build** and change your working directory to it by running **mkdir build**, **cd build**.
3. Run **cmake -G "NMake Makefiles" ..** to create Makefile.
4. Run **nmake** to build the library.
5. Optionally you can run **nmake install** to install newly built library.

Usage examples
--------------

See the WCFL/samples folder for GUI application example, GCFL/samples folder for console application.
    
License agreement
-----------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published
by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
 
Release history
---------------

04.03.2015:
- Initial release. Last change to the source code was made on 06.12.2010.
