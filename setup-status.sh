#!/bin/sh

gcc -Wall -pedantic -std=c99 -lX11 ./src/status/dwm-status.c -o /usr/bin/dwm-status
echo 'Add "dwm-status &" (no quotes) to your .xinitrc :)'
