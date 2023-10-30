# mustat
Minimalistic status bar written in c, inspired by [dwmblocks](https://github.com/torrinfail/dwmblocks).

# how it works
The status bar entries are updated periodically and updates can also be triggered by real-time [signals](https://www.man7.org/linux/man-pages/man7/signal.7.html) based on configuration.
The updated status bar is written to standard output. The commands outputting the entries, as well as the corresponding update periods and update signals are defined in `config.h`.

# usage
Build mustat by running `make`, which also instantiates `config.h` from `config.def.h`.
Install the program with `sudo make install`.
Edit `config.h` to configure your own status bar, then rebuild and reinstall to apply the changes.

Sending the real-time signal <1> to mustat:
```
pkill -RTMIN+1 mustat
```
You can then assign <1> to a status bar entry in `config.h` to have it update each time this signal is received.

Using mustat as a dwm status bar:
```
mustat | xargs -I% xsetroot -name % &
```
You can put this line in your `~/.xinitrc` or other startup script to have it start with dwm.
