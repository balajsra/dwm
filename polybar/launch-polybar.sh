#!/bin/bash

killall -q polybar
while pgrep -u $UID -x polybar >/dev/null; do sleep 1; done

rm /tmp/polybar.pids

polybar -c ~/.config/dwm/polybar/config.ini main &
echo "$!" >>/tmp/polybar.pids
