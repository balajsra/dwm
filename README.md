# dwm - dynamic window manager

Sravan's custom build of dwm. Original dwm build by suckless team found here: [https://dwm.suckless.org/](https://dwm.suckless.org/)
Choice of patches heavily inspired by [Palmdrop's custom build of dwm](https://github.com/palmdrop/dwm).

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

Most patches can be found on the suckless website: [https://dwm.suckless.org/patches/](https://dwm.suckless.org/patches/)

* [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/) - Actually toggle fullscreen for a window, instead of toggling the status bar and the monocle layout
* [alwaysfullscreen](https://dwm.suckless.org/patches/alwaysfullscreen/) - Do not allow the focus to drift from the active fullscreen client when using focusstack()
* [anybar](https://github.com/mihirlad55/dwm-anybar) (Polybar Tray Fix Version) - Enables dwm to manage external status bars such as lemonbar and polybar
* [aspectresize](https://dwm.suckless.org/patches/aspectresize/) - Allows you to resize a window while maintaining aspect ratio
* [attachbelow](https://dwm.suckless.org/patches/attachbelow/) (Toggleable) - Make new clients attach below the selected client, instead of always becoming the new master
* [autoresize](https://dwm.suckless.org/patches/autoresize/) - Windows that are not visible when requesting a resize/move will get resized/moved
* [center](https://dwm.suckless.org/patches/center/) - Add an `iscentered` rule to automatically center clients on the current monitor
* [cfacts](https://dwm.suckless.org/patches/cfacts/) - Assign different weights to clients in their respective stack in tiled layout
* [cfacts-vanitygaps](https://github.com/bakkeby/patches/blob/master/dwm/dwm-cfacts-vanitygaps-6.2.diff) - Vanity gaps patch compatible with cfacts patch
* [combo](https://dwm.suckless.org/patches/combo/) - Select multiple tags for tag or view by pressing all the right keys as a combo
* [cool autostart](https://dwm.suckless.org/patches/cool_autostart/) - Execute commands from `autostart` array in `config.h` on startup and kill processes upon dwm exit
* [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/) - Cycle through all available layouts
* [dwmc](https://dwm.suckless.org/patches/dwmc/) - Simple dwmc client using a fork of [fsignal](https://dwm.suckless.org/patches/fsignal/) to communicate with dwm
* [fixborders](https://dwm.suckless.org/patches/alpha/) - Make borders opaque
* [ipc](https://github.com/mihirlad55/dwm-ipc) - Allows third party programs (e.g. polybar) to query window manager for information
* [movestack](https://dwm.suckless.org/patches/movestack/) - Move clients around in the stack and swap them with the master
* [noborder](https://dwm.suckless.org/patches/noborder/) (Floating Fix) - Remove the border when there is only one window visible
* [swallow](https://dwm.suckless.org/patches/swallow/) - Programs opened from terminal will "swallow" the terminal
* [unfloatvisible](https://dwm.suckless.org/patches/unfloatvisible/) - Resets `isfloating` on any visible windows that have it set
* [xresources](https://dwm.suckless.org/patches/xresources/) - Allows dwm settings (e.g. colors) to be set in Xresources

## Polybar

The anybar and ipc patches above allow dwm to use an external status bar.
I am using polybar. My config can be found [here](https://github.com/balajsra/polybar).

* [Polybar DWM Module](https://github.com/mihirlad55/polybar-dwm-module)
* [Polybar](https://github.com/polybar/polybar)
