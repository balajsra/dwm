#!/bin/bash

# Start compositor using configuration file
picom --config ~/.config/picom/picom.conf &

# Restore wallpaper
nitrogen --restore &

# Blue light filter (Farmington Hills, MI)
redshift -l 42.48531:-83.37716 &

