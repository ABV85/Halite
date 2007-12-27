Halite: A Free Open-Source BitTorrent client

Version: 0.3 released 26th December 2007

WWW: http://www.binarynotions.com/halite.php Forum:
http://www.binarynotions.com/forum.php

Developer: E�in O'Callaghan

Halite (named after the mineral) is a BitTorrent client based on Arvid
Norberg's excellent libtorrent library from Rasterbar Software. The
program also relies on the Boost libraries.

Features:

While still at an early state of development Halite is a functional
BitTorrent client. So far its list of features is pretty standard but
that is because I want to ensure it does the basic stuff well.

That said, it supports:

  + File selection and/or file priority specifications.
  + Trackerless torrents (using the Mainline kademlia DHT protocol).
  + IP filtering with eMule style ipfilter.dat import.
  + Protocol Encryption support.
  + Translations of the UI into a number of languages through the help 
    of volunteers. (if you wish to help with a translation then please do)
  + Minimize to tray with transfer rate summary.
  + Full Unicode support through UTF-8 and native Windows wide-char strings.
  + Login support where tracker requires it.
  + Ability to edit trackers specified in the torrent.
  + Transfer rate and connection limits both global and per-torrent.

Requirements: Windows 2000, XP, Server 2003 and Vista (Note currently
Vista users need to install the application to a directory where they
will have full read and write access to. The recommended solution is
to use the standalone exe distribution and not the installer.

Known Issues/Problems: 

Halite does not always gracefully accept configuration information
from previous versions. Should you experience crashes upon running
Halite you should delete any old Halite.ini.xml or Halite.xml. 

You will not lose any downloads in progress and those which do not
restart automatically can be done so manually by loading the
associated torrent file from the 'torrents' subdirectory.

Changes:

 - from v 0.2.9 to 0.3: 
   1) File selection and/or priority settings.
   2) Protocol Encryption.
   3) New tabbed interface makes better use of screen real estate.
   4) Updated to recent versions of Boost (1.34.1) and libtorrent.
   5) Numerous bug fixes.
   
 - from v 0.2.8 to 0.2.9: 
   1) Full Unicode support!
   2) Rewitten XML fileformat with greatly improved robustness.
   3) New tabbed interface makes better use of screen real estate.
   4) Ability to edit Trackers and set login details.
   5) Comprehensive logging for diagnosing problems.
   6) Windows 2000 and Server 2003 supported fully.
   7) Switched to MSVC 2005 compiler (8.0) for improved reliability
      though at the cost of slightly bigger executables.
   
- from v 0.2.7 to 0.2.8: 
   1) IP filtering support eMule style ipfilter.dat files.
   2) DHT support, thought it is turned off by default.
   3) Can select alternate save directory for torrents..
   4) New icon!

 - from v 0.2.6 to 0.2.7:
   1) By default Halite will only allow one instance to be launched 
   2) Halite can be set as the default program for '.torrent' files. 
   3) ETA indicator for torrents. 4) Minor GUI tweaks.

 - from v 0.2.5 to 0.2.6: 
   1) Fixed a silly bug (i.e. I should have caught it sooner) whereby
      exiting Halite from the tray would screw up the window layout
      next time running it.
   2) Added auto-selection to Torrents list to make it more intuitive.

 - from v 0.2 to 0.2.5: 
   1) The GUI is slightly altered so that it looks consistent and neat
      for a number of visual styles which I was able to test it on. 
   2) The ability to drag and drop torrent files into the app has been
      added.
   3) It will minimize to the tray instead of task bar and hovering
      mouse for the tray icon displays the current up and down rate. 
   4) Where previously the various limits boxes didn't validate
      properly now they do and any invalid input is interpreted as no
      limit and a nice infinity symbol is displayed. 
   5) Individual torrent info is saved and loaded when the program is
      closed and reopened allowing torrent limits to be remembered.
   6) If the program has to wait after the user clicking close for any
      active connections to shutdown down 'cleanly' an optional small
      dialog is displayed to alert the user that the program is still
      running.

Subversion: svn://svn.geekisp.com/halite

In addition you can check out the Trac site (trac.geekisp.com/halite)
but I haven't really done much with it ... yet.

Thanks:

It can be hard to remember to thank everyone but that is no excuse for
leaving someone out. If I have done so let me know.

  + Arvid Norberg- As the author of libtorrent he has made the single
    biggest contribution to this project.
    http://www.rasterbar.com/products/libtorrent/index.html

  + Christopher Kohloff- The man behind Boost.ASIO a crucial element
    of libtorrent and my own libhttp library.
    http://asio.sourceforge.net/

  + nudone (Nick Pearson)- The excellent artist who designed the icon
    for Halite. 
	wtfcody.com / nudsville.com

  + Austin- Very kindly made the Iss install script for Halite.

  + Everyone who has been in touch with me through email or the forum
    and have shared their ideas and feature requests for the client.
    They have given the project direction and purpose.

