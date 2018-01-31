Getting Started with Chromaton!
=====================================

Chromaton.org

No Copyright for Chromaton.  You are free to do whatever the hell you want with it!  Power to the people!

Some of the below may want credit so there:
* Copyright (c) 2017-2018 Yenten Core Developer(s)
* Copyright (c) 2009-2017 Bitcoin Core Developers
* Copyright (c) 2013-2017 Dash Developers (DarkGravityWave3)
* Copyright (c) 2014-2017 Alexander Peslyak (Yescrypt Original)

License
-------

No licence for Chromaton.  It's yours.  It's mine.  Whatever.  It's ours.

Build chromaton on Ubuntu 16.04
-------------------

*You will need 2 GB or more RAM on your device or else use SWAP to get it, search about SWAP for more info.

The below will probably also work on "Window's Subsystem for Linux" aka Ubuntu for windows 10.  You will need to search how to
get it, it uses the microsoft store and you will need to click the update button to the upper right before it will allow you to
download ubuntu.  Right now there are no windows binaries or installation guide, a bounty is made for someone to do this for us,
but for now use ubuntu for windows or linux.

    sudo apt-get install build-essential
    sudo apt-get install libtool autotools-dev autoconf
    sudo apt-get install libssl-dev
    sudo apt-get install libboost-all-dev
    sudo apt-get install pkg-config
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev
    sudo apt-get install libdb4.8++-dev
    sudo apt-get install git
    
    git clone https://github.com/RecieverofMemory/Chromaton.git
    
  (If it says cannot resolve host github.com, you may need to restart your computer)
  
    cd Chromaton
    
  (to learn how to use cd to navigate around, see later in this guide)
  
  The following two commands may take a little time and it may look like the process stalled, just wait.  During the second command there may be some "no", unless it is of a group of things that were installed above, it should still be ok.
  
    sudo ./autogen.sh
    sudo ./configure --enable-upnp-default --without-gui --disable-tests
    
  (upnp checks may fail but it still worked for me anyway.  If during the ./configure step it says libboost no, then rerun the sudo apt-get install libboost line.)
    
    sudo make
    
  Not quite done.  Now we need to install gksu so we can modify chromaton.conf:
  
    sudo apt-get install gksu
    gksudo nautilus
    
  Now enter your password.  In the window that pops up go to computer, then to home, then to your user name folder.  At the top of the window click the Edit button, then preferences, then views.  Click the checkbox show hidden files.  Now you should see a folder named .chromaton and double click that.  you should see chromaton.conf, if not create it (may need to search online for how to create a configuration file).  Now we will need to create rpcuser and rpcpassword.  We will let the program tell us which to use by running chromatond.  cd .. back and lets go into the chromaton folder and the src subfolder.
  
    sudo ./chromatond
    
  It should tell us what rpcuser and password to select.  Just copy and paste this back into your chromaton.conf file and save it.  If it doesn't allow you to save it do a web search to figure out how.
    
  To finally get started navigate to the src folder in chromaton.
    
    sudo ./chromaton-cli
    
  If it shows stuff then good work!  Basically what we will need to do is run commands by typing
  
    ./chromaton-cli help
    
  or
  
    ./chromaton-cli setgenerate true
    
    ./chromaton-cli getmininginfo
    
  You should be able to figure it out from here!
  
  Some hints:
  ----------
    
  Sudo means "super user do" basically it gives you admin (root) permissions.  If you forget to put sudo in front of a command it may say permission denied.
  
  Git is a program to load stuff from github.
  
  cd is "change directory".  cd Chromaton means change directory (folder) to chromaton.  you can use command ls (stands for lists) to see all the files in the current directory.   If you want to go back a directory type: cd .. 
  
  ./ means execute file
  
  make means to do the compilation.
  









Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging message are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play bitcoins" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regest mode.

**DEBUG_LOCKORDER**

Bitcoin Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of what locks
are held, and adds warning to the debug.log file if inconsistencies are detected.
