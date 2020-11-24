# dwm - dynamic window manager

Sravan's custom build of dwm. Original dwm build by suckless team found here: [https://dwm.suckless.org/](https://dwm.suckless.org/)

## Requirements

In order to build dwm you need the Xlib header files.

## Installation

Edit [config.mk](config.mk) to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

```
make clean install
```

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

```
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Patches

Most patches can be found on the suckless website: [https://dwm.suckless.org/patches/]

* [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/) - Actually toggle fullscreen for a window, instead of toggling the status bar and the monocle layout
* [alwaysfullscreen](https://dwm.suckless.org/patches/alwaysfullscreen/) - Do not allow the focus to drift from the active fullscreen client when using focusstack()
* [fixborders](https://dwm.suckless.org/patches/alpha/) - Make borders opaque
