#!/bin/sh

# Generate the color files on disk immediately.
# We don't use '&' because we need these files to exist before the next steps.
wal -R

/usr/libexec/lxqt-policykit-agent &
dunst &
emacs --daemon &
kdeconnectd &
libinput-gestures-setup start &

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
        
        # Check every 5 seconds—low overhead, but fast recovery
        sleep 30
    done
) &

# Clipboard stuff
cliphist wipe &
wl-paste --watch cliphist store &
