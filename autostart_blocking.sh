#!/bin/bash

# Local cloud storage directory
local_clone_dir="$HOME/Cloud"

# List of remotes as defined in rclone
declare -a remote_array=(\
    "OneDrive - Personal" \
    "Google Drive - Personal" \
)

# Mount Remotes
for i in "${remote_array[@]}"
do
    local_path="$local_clone_dir"/"$i"
    mkdir -p "$local_path"
    rclone --vfs-cache-mode writes mount "$i": "$local_path" &
done

# Start compositor using configuration file
picom --config ~/.config/picom/picom.conf &

# Restore wallpaper
nitrogen --restore &

# Blue light filter (Farmington Hills, MI)
redshift -l 42.48531:-83.37716 &