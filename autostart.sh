#!/bin/sh

# Generate the color files on disk immediately.
# We don't use '&' because we need these files to exist before the next steps.
wal -R

rm ~/.config/waybar -r
ln -s ~/.ashdwl/waybar/ ~/.config/waybar

# Startup
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
dbus-launch waybar &
dunst &
swaybg -i $(cat ~/.cache/wal/wal) &

# Clipboard stuff
cliphist wipe &
wl-paste --watch cliphist store &
