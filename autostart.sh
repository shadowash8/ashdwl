# Set wallpaper
/usr/libexec/lxqt-policykit-agent &
swaybg -i $(cat ~/.cache/wal/wal) &
xrdb -merge ~/.Xresources 
dunst &
emacs --daemon &
libinput-gestures-setup start
