#!/bin/bash

# Start compositor using configuration file
picom --config ~/.config/picom/picom.conf &

# Restore wallpaper
nitrogen --restore &
