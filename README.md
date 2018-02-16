# NerfAVR
Guarantee this won't be useful to you if you've just stumbled upon this page.

This is part of a small project involving a nerf gun.
I took it as an excuse to try and write a simple task scheduler with limited resources.

The code has currently only been tested in a simulated environment using Atmel studio.
The basics, however, seem to be working fine.

Project structure:

general: Contains main.c and any files that don't fit into a specific slot.
  
drivers: Contains driver definitions.  Or will, anyway.
  
hal: Hardware abstraction layer.  Will be used for things like register manipulation.
  
os: "Operating System", in very dubious quotes.  Defines a very primitive scheduler of sorts that I'm looking for an excuse to use.
