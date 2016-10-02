To use Datv-Express on Windows you will need to install USB drivers.
The best way to do this is to use Zadig. http://zadig.akeo.ie/

You will also need to register the MajorUdpSender directshow filter
if you plan to use filtergraphs.
This can be done by ticking the filter.bat option after this message.

I will let you figure out how to set the direct show filters up.

There are no warnings if things go wrong so you need to check the 
leds on the Express board.

When you exit the server app it saves the current setup.
You can alter the various configurations from the menu (top left).

If you change any network settings you will need to restart the program.

New as of version 1.2
---------------------
NULL packet deletion
UDP multicast added
If remote IP address is unknown use 0.0.0.0
see RFC 3678 for further details about multicasting
Extra interpolator added for improved aliasing below 2 MS/s

New as of Version 1.4
---------------------
Symbol rate variable from 100K to 10 M without a re-start
Potential lock up bug at power up eliminated

Good Luck!

- Charles
