#!/bin/bash

########################
# Startup Applications #
########################
# List of applications to run on start
declare -a applications_array=(\
    # System Restore Processes
    "bash /home/sravan/.screenlayout/default-screen-layout.sh" \    # Restore default screen layout
    "nitrogen --restore" \                                          # Restore wallpaper
    # System Tray Applications
    "volctl" \                                                      # PulseAudio Volume Control
    "nyrna" \                                                       # Nyrna Application Suspend
    "blueman-tray" \                                                # Blueman Bluetooth Manager
    "nm-applet" \                                                   # Network Manager Applet
    "kdeconnect-indicator" \                                        # KDE Connect
    "flameshot" \                                                   # Flameshot Screenshot Tool
    # Background Processes
    "picom --config /home/sravan/.config/picom/picom.conf" \        # Picom Compositor
    "/usr/lib/xfce4/notifyd/xfce4-notifyd" \                        # Xfce Notification Daemon
    "greenclip daemon" \                                            # Greenclip Clipboard Manager
    "redshift -x" \                                                 # Reset redshift display gamma
    "redshift-gtk" \                                                # Redshift Blue Light Filter
    "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1" \   # GNOME Polkit Authentication Agent
    "slstatus" \                                                    # slstatus status bar
    "light-locker --lock-on-suspend --lock-on-lid" \                # LightDM Locker
    # Hardware Driver Applications
    "solaar --window=hide" \                                        # Logitech Mouse Driver
    "polychromatic-tray-applet" \                                   # Razer Keyboard Customization
    "optimus-manager-qt" \                                          # Optimus Manager Qt
)

# Run applications (ignore if they don't exist)
for i in "${applications_array[@]}"
do
    if ! command -v $i > /dev/null
    then
        do_nothing() { :; }
    else
        $i &
    fi
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

# Mount Remotes
for i in "${remote_array[@]}"
do
    local_path="$local_clone_dir"/"$i"
    mkdir -p "$local_path"
    rclone mount "$i": "$local_path" &
done
