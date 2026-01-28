# Set wallpaper
/usr/libexec/lxqt-policykit-agent &
swaybg -i $(cat ~/.cache/wal/wal) &
xrdb -merge ~/.Xresources 
dunst &
emacs --daemon &
libinput-gestures-setup start &
cliphist wipe &
wl-paste --watch cliphist store &

