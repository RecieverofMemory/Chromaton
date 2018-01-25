WINDOWS BUILD NOTES
===================


Compilers Supported
-------------------
Note: releases are cross-compiled using mingw running on Linux.

Primer:
I am using Ubuntu on windows 10 (google it to find out how to get it, in the microsoft store there will be an "update" button to the right of the "get ubuntu" button so you will need to update if you can't get ubuntu.  You can also just use linux ubuntu.)
If you are using windows ubuntu I think you will need to have windows mingw installed in the C: drive.

Finding your linux files in your windows system; once you untar (don't worry we will get to this later) from the C: your new folders will be located here:

C:\Users\your_user_name\AppData\Local\Packages\CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc\LocalState\rootfs\home

Some important commands to know:

sudo and sudo su
	
	the sudo command makes you the root user which is required if you ever try something and it says "permission denied".  If you try to cd into a directory and it says permission denied, then do sudo su then hit enter, then try to cd into the directory.  This puts you in a root user state for the rest of your session (super user).
cd and cd ..

	cd (change directory) command picks a folder to enter.  cd ..  takes you back up a level in the directory.
	
ls

	ls (lists) command lists all the files in the folder you are currently in.  this is essential to know the directory to "cd" into.
./

	this runs a given file.


Dependencies
------------
Libraries you need to download separately and build:

	name            default path               download
	--------------------------------------------------------------------------------------------------------------------
	OpenSSL         \openssl-1.0.1k		http://www.openssl.org/source/
	Berkeley DB     \db-4.8.30.NC		http://www.oracle.com/technology/software/products/berkeley-db/index.html
	Boost           \boost_1_55_0		http://www.boost.org/users/download/
	Boost Jam	\boost-jam-3.1.18	https://sourceforge.net/projects/boost/files/boost-jam/3.1.18/
	miniupnpc       \miniupnpc-2.0		http://miniupnp.tuxfamily.org/files/

Their licenses:

	OpenSSL        Old BSD license with the problematic advertising requirement
	Berkeley DB    New BSD license with additional requirement that linked software must be free open source
	Boost          MIT-like license
	Boost Jam      MIT-Like liscence?
	miniupnpc      New (3-clause) BSD license

Versions used in this release:

	OpenSSL      1.0.1k
	Berkeley DB  4.8.30.NC
	Boost        1.55.0
	Boost Jam    3.1.18
	miniupnpc    2.0

First:

un-tar sources with MSYS 'tar xfz' to avoid issue with symlinks (OpenSSL ticket 2377)

https://pureinfotech.com/extract-tar-gz-files-windows-10/

put the downloaded tar files into the C: then:

	sudo tar -xvzf /mnt/c/PATH/TO/TAR-FILE/FILE-NAME.tar.gz 
	
Do this for all the packages above plus boost jam.

OpenSSL
-------
MSYS shell (or the Ubuntu window in WSL -windows subsystem linux-):	
	
change 'MAKE' env. variable from 'C:\MinGW32\bin\mingw32-make.exe' to '/c/MinGW32/bin/mingw32-make.exe'

For me it was 'C:\MinGW\bin\mingw32-make.exe' to '/c/MinGW/bin/mingw32-make.exe'

	cd /openssl-1.0.1k
	sudo ./config
	sudo make

Berkeley DB
-----------
MSYS/WSL shell:

	cd /db-4.8.30.NC
	cd /build_unix
	sudo sh ../dist/configure --enable-mingw --enable-cxx
	sudo make

Boost
-----
MSYS/WSL shell:
download boost jam 3.1.18

building boost jam http://boost.sourceforge.net/doc/html/jam/building.html

	cd /boost-jam-3.1.18
	sudo sh ./build.sh
	cd /boost_1_55_0
	sudo bjam toolset=gcc --layout=versioned --build-type=complete stage

MiniUPnPc
---------
UPnP support is optional, make with `USE_UPNP=` to disable it.

MSYS/WSL shell:

	cd /miniupnpc-2.0
	sudo make -f Makefile.mingw  //need to be mingw version or just Makefile?
	sudo mkdir miniupnpc
	sudo cp *.h miniupnpc/
	//sudo su
	//sudo make install
	//exit

Yenten
-------
MSYS/WSL shell:

	cd \yenten
	sudo sh autogen.sh
	sudo sh configure
	sudo mingw32-make
	sudo strip yentend.exe
