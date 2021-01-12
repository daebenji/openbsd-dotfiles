#!/bin/sh

# include user executables into path
export PATH=$HOME/.bin:$HOME/.local/bin:$PATH

# set shell
export ENV=$HOME/.zshrc

# allow ctrl+alt+backspace to kill X
setxkbmap -option "terminate:ctrl_alt_bksp"

# capslock shall be escape
setxkbmap -option caps:escape

# turn this annoying bell off
xset -b

# set keyboard layout
setxkbmap "de"

# accelerate mouse
xinput set-prop /dev/wsmouse 290 0.3
Xinput set-prop /dev/wsmouse 291 1.4
xinput set-prop /dev/wsmouse 292 0.3
Xinput set-prop /dev/wsmouse 293 1.4

# accelerate keyboard
xset r rate 300 65

# xkeyboard preferences
export XKB_DEFAULT_LAYOUT=de
export XKB_DEFAULT_VARIANT=,nodeadkeys
export XKB_DEFAULT_OPTIONS=grp:alt_shift_toggle

# set w3mimg patch for ranger
export W3MIMGDISPLAY_PATH="/usr/local/libexec/w3m/w3mimgdisplay"

# force webkit to one process mode
export WEBKIT_USE_SINGLE_WEB_PROCESS="TRUE"

# fixes
#export LIBGL_DRI3_DISABLE=1
#export XLIB_SKIP_ARGB_VISUALS=1

# accelerate firefox
export MOZ_ACCELERATED=1
export MOZ_WEBRENDER=1

# locales
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
export LC_TIME=en_US.UTF-8
export LC_NUMERIC=en_US.UTF-8
export LC_MESSAGES=C

# gtk/qt scaling
#export QT_AUTO_SCREEN_SCALE_FACTOR=1
#export QT_SCALE_FACTOR=1
#export QT_QPA_PLATFORMTHEME=qt5ct
#export GDK_DPI_SCALE=1

export PRINTER=rp

# java fonts
# export _JAVA_OPTIONS='-Dawt.useSystemAAFontSettings=gasp -Dswing.defaultlaf=com.sun.java.swing.plaf.gtk.GTKLookAndFeel -Dawt.useSystemAAFontSettings=on'
# export _JAVA_AWT_WM_NONREPARENTING=1

# no cores from here
ulimit -c 0

# add all the fonts paths
xset fp+ $HOME/.fonts
find /usr/local/share/fonts/* -type d -maxdepth 1 -exec xset fp+ "{}" \;
xset fp rehash

# load x resources
xrdb -merge $HOME/.Xresources

# keep clipboards in sync
autocutsel -fork
autocutsel -selection PRIMARY -fork

# dim screen
doas wsconsctl display.brightness=20

# mute all sounds
mixerctl outputs.master.mute=off
mixerctl outputs.master=0,0

# set background
xsetroot -solid rgb:08/08/08

# compositor?
# xcompmgr -f -I 0.01 -O 0.01 -D 2 &
# xcompmgr &
#hsetroot -solid "#080808"

# allow local users to access X (root)
xhost +local:

# lock screen after 10 minutes
xautolock -time 15 -locker slock &

doas chown sdk /dev/video*

twmnd &

# select dock output
/home/sdk/.bin/dock

while true
do
    # Set root title
    [ -f .xsetroot.sh ] && sh .xsetroot.sh

    # Update every 10s
    sleep 10s
done &

# Set up rotated dual screen without touching my xorg.conf
xrandr --output DVI-1 --auto --rotate left --pos 0x0 --output DVI-0 --auto --pos 1080x720 --rotate normal

xrandr -s 1920x1080

# start status bar
/usr/local/bin/dwmstatus &

# start WM
/usr/local/bin/dwm
#/usr/local/bin/dbus-launch --sh-syntax --exit-with-session /usr/local/bin/i3
#/usr/local/bin/dbus-launch --sh-syntax --exit-with-session /usr/local/bin/spectrwm > /home/sdk/.spectrwm 2>&1
#/usr/local/bin/dbus-launch --sh-syntax --exit-with-session /usr/local/bin/bspwm > /home/sdk/.bspwm.log 2>&1
#/usr/local/bin/dbus-launch --sh-syntax --exit-with-session /usr/X11R6/bin/cwm
