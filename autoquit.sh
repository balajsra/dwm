#!/bin/bash

########################
# Startup Applications #
########################
# List of applications to kill on exit
declare -a applications_array=(\
    # System Tray Applications
    "volctl" \          # PulseAudio Volume Control
    "nyrna" \           # Nyrna Application Suspend
    "blueman-tray" \    # Blueman Bluetooth Manager
    "nm-applet" \       # Network Manager Applet
    "kdeconnect-indi" \ # KDE Connect
    "flameshot" \       # Flameshot Screenshot Tool
    "redshift-gtk" \    # Redshift Blue Light Filter
    # Background Processes
    "picom" \           # Picom Compositor
    "deadd-notificat" \ # Deadd Notification Center
    "greenclip" \       # Greenclip Clipboard Manager
    "redshift" \        # Redshift Blue Light Filter
    "polkit-gnome-au" \ # GNOME Polkit Authentication Agent
    "slstatus" \        # slstatus status bar
    "light-locker" \    # LightDM Locker
    # Hardware Driver Applications
    "solaar" \          # Logitech Mouse Driver
    "polychromatic-t" \ # Razer Keyboard Customization
    "optimus-manager" \ # Optimus Manager Qt
)

# Kill applications
for i in "${applications_array[@]}"
do
    pkill -9 $i &
done

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

# Unmount Remotes
for i in "${remote_array[@]}"
do
    local_path="$local_clone_dir"/"$i"
    fusermount -u "$local_path" &
done
