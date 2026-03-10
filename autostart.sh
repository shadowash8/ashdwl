#!/bin/sh

rm ~/.config/waybar -r
ln -s ~/.ashdwl/waybar/ ~/.config/waybar

# Startup
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
dbus-launch waybar &
dunst &
swaybg -i $(cat ~/.cache/cwal/cwal) &

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
        
        # Check every 30 seconds—low overhead, but fast recovery
        sleep 30
    done
) &


# Clipboard stuff
cliphist wipe &
wl-paste --watch cliphist store &
