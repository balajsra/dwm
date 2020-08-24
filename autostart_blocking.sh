#!/bin/bash

##############################
# Startup Blocking Processes #
##############################
# List of processes to run on start
declare -a processes_array=(\
    "picom --config /home/sravan/.config/picom/picom.conf" \        # Start compositor using configuration file
    "bash /home/sravan/.screenlayout/default-screen-layout.sh" \    # Restore default screen layout
    "nitrogen --restore" \                                          # Restore wallpaper
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
