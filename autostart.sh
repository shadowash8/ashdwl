#!/bin/sh
# Startup
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
hypridle &
dunst &
dbus-launch waybar &
swaybg -i $(cat ~/.cache/ashwal/ashwal) &
wlsunset -o eDP-1 -g 0.8 &

# Handle the XWayland/XRDB mess in a delayed block.
(
    while true; do
        # Check if xeyes (XWayland anchor) is running
        if ! pgrep -x "xeyes" > /dev/null; then
            # Re-anchor XWayland
            xeyes -geometry 1x1-1-1 &
            
            sleep 1

            # Re-merge the database
            xrdb -merge ~/.Xresources
        fi
        
        # Check every 30 seconds—low overhead
        sleep 30
    done
) &


# Clipboard stuff
cliphist wipe &
wl-paste --watch cliphist store &
