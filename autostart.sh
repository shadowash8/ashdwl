# Set wallpaper
if [ -f ~/.cache/wal/wal ]; then
    pkill swaybg
    swaybg -i $(cat ~/.cache/wal/wal) &
fi

xrdb -merge ~/.Xresources
