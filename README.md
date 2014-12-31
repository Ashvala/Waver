Waver
=====

A simple wave file writer that I wrote for my EP-353 Audio Programming in C class. 

----

Compiling: 

- Run

    `make`

It ought to create an executable called "waver".


----

To read a more detailed doc, open README.html.

----

####Warning: 

This thing is built on top of OS X. If you want to execute this on more recent linux distributions, you will need to use the -lm flag to link the `math.h` library. Also, running --help will not help you out in this case either, unless you have a command on your linux box that does the equivalent of `open` on OS X. 

