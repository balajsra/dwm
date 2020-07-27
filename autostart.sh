#!/bin/bash

############################
# System Tray Applications #
############################
# PulseAudio volume control
volctl &

# Nyrna
nyrna &

# Blueman
blueman-tray &

# Network Manager Applet
nm-applet &

# Deadd Notification Center
deadd-notification-center &

#####################
# Cloud Drive Rsync #
#####################
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