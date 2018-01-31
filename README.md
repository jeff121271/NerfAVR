# NerfAVR
Guarantee this won't be useful to you if you've just stumbled upon this page.

This is part of a small project involving a nerf gun.
I took it as an excuse to try and write a simple task scheduler with limited resources.

Currently the code was only tested on Windows using MinGW.  The printf() statements
and my timer setup under the HAL will need to be abstracted away or conditionally compiled
out for the actual implementation.

Project structure:

src
  general
    Contains main.c and any files that don't fit into a specific slot.
  drivers
    Contains driver definitions.  Or will, anyway.
  hal
    Hardware abstraction layer.  Will be used for things like register
    manipulation.
  os
    "Operating System", in very dubious quotes.  Defines a very primitive
    scheduler of sorts that I'm looking for an excuse to use.
