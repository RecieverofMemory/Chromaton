Getting Started with Chromaton!
=====================================

Chromaton.org

No Copyright for Chromaton.  You are free to do whatever the heaven you want with it!  Power to the people!

Some of the below may want credit so there:
* Copyright (c) 2017-2018 Yenten Core Developer(s)
* Copyright (c) 2009-2017 Bitcoin Core Developers
* Copyright (c) 2013-2017 Dash Developers (DarkGravityWave3)
* Copyright (c) 2014-2017 Alexander Peslyak (Yescrypt Original)

License
-------

No licence for Chromaton.  It's yours.  It's mine.  Whatever.  It's ours.

Build chromaton on Ubuntu 16.04 (No working Windows guide yet but you can try in the doc folder following build-msw.md, there is a bounty if you are successful)
-------------------

*You will need 2 GB or more RAM on your device or else use SWAP to get it, search about SWAP for more info.

Install ubuntu 16.04.  If you are on a windows PC use this guide using rufus on a usb drive:
https://tutorials.ubuntu.com/tutorial/tutorial-create-a-usb-stick-on-windows#0

If your usb drive doesn't seem to be getting the right capacity you will need to modify it's partitions.  Use EaseUS partition master and delete the partitions off the usb drive and reformat it.  Then run the above tutorial.

After ubuntu is installed find the terminal window and do the following:

In Terminal Window:

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
    sudo apt-get install gedit
    
    git clone https://github.com/RecieverofMemory/Chromaton.git
    
  (If it says cannot resolve host github.com, you may need to restart your computer)
  
    cd Chromaton
    
  (to learn how to use cd to navigate around, see later in this guide)
  
  The following two commands may take a little time and it may look like the process stalled, just wait.  During the second command there may be some "no", unless it is of a group of things that were installed above, it should still be ok.
  
    sudo ./autogen.sh
    sudo ./configure --enable-upnp-default --without-gui --disable-tests
    
  (upnp checks may fail but it still worked for me anyway.  If during the ./configure step it says libboost no, then rerun the sudo apt-get install libboost line.)
    
    sudo make
    
  Not quite done.  Now we need to install gksu so we can modify blockchain.conf:
  
    sudo apt-get install gksu
    gksudo nautilus
    
  Now enter your password.  In the window that pops up go to computer, then to home, then to your user name folder.  At the top of the window click the Edit button, then preferences, then views.  Click the checkbox show hidden files.  Now you should see a folder named .blockchain and double click that.  you should see blockchain.conf, if not create it with the command:
    
    sudo su
    cd .. 
    
  till you are in your home folder
  
    ls -a
    
  This shows you hidden files, you should see .blockchain
  
    cd .blockchain
    gedit blockchain.conf
    
  It should open up.  Type in something and hit save.  We will come back and edit this later.  Exit the Terminal window and open up a new one so you are out of superuser mode.  Now we will need to create rpcuser and rpcpassword.  We will let the program tell us which to use by running blockchaind.  To do this  cd .. back and lets go into the chromaton folder and the src subfolder.  Then type:
  
    sudo ./blockchaind
    
  It should tell us what rpcuser and password to select.  Just copy and paste this back into your chromaton.conf file and save it.  If it doesn't allow you to save it do a web search to figure out how.
    
  To finally get started navigate to the src folder in chromaton.
    
    sudo ./blockchain-cli
    
  If it shows stuff then good work!  Basically what we will need to do is run commands by typing
  
    ./blockchain-cli help
    
  or
  
    ./blockchain-cli setgenerate true
    
    ./blockchain-cli getmininginfo
    
  You should be able to figure it out from here!
  
  Some hints:
  ----------
    
  Sudo means "super user do" basically it gives you admin (root) permissions.  If you forget to put sudo in front of a command it may say permission denied.  if you are trying to change directories (cd) and it says permission denied you need to enter superuser mode by typing sudo su (hit enter) then try to cd.
  
  Git is a program to load stuff from github.
  
  cd is "change directory".  cd Chromaton means change directory (folder) to chromaton.  You can use command ls (stands for lists) to see all the files in the current directory.  To show hidden files do ls -a.  If you want to go back a directory type: cd .. 
  
  ./ means execute file
  
  make means to do the compilation.
  


If you need help or think this guide needs to be changed, let me (chromos) know on the forums at chromaton.org!  I am here to help you!






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
