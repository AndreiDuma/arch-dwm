#!/bin/sh

makepkg -g >> PKGBUILD
makepkg -ef
rm dwm-6.0.tar.gz ./src/dwm-6.0/{dwm,dwm.o}
