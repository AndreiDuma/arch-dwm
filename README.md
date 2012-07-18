arch-dwm
========

My configuration of **dwm**.

#### Usage:

make edits to config.h / dwm.c

package with pack.sh

    $ ./pack.sh

install with install.sh (run as root)

    # ./install.sh

dwm-status
----------

Compile with:

    gcc -Wall -pedantic -std=c99 -lX11 dwm-status.c -o dwm-status

.. and add in .xinitrc:

    path/to/dwm-status &
