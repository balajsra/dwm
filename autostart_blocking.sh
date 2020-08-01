#!/bin/bash

##############################
# Startup Blocking Processes #
##############################
# List of processes to run on start
declare -a processes_array=(\
    "picom --config ~/.config/picom/picom.conf" \   # Start compositor using configuration file
    "nitrogen --restore" \                          # Restore wallpaper
)

# Run processes (ignore if they don't exist)
for i in "${processes_array[@]}"
do
    if ! command -v $i > /dev/null
    then
        do_nothing() { :; }
    else
        $i &
    fi
done
