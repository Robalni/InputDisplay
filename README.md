InputDisplay
============

This program displays a controller and what inputs you do.  Any
controller works but you need to edit config.txt or a file in the
config directory to make it display the right things.  Right now you
get n64 and xbox 360 controller images.  I may add more later.

![screenshot Nintendo 64](http://www.robalni.org/input-display/n64.png)
![screenshot Xbox 360](http://www.robalni.org/input-display/xbox360.png)

## Compile

### Debian

Building InputDisplay requires these packages: cmake g++ libsdl2-dev
libsdl2-image-dev.

Commands (after you download and cd to this directory):

```sh
su -c "apt-get install cmake g++ libsdl2-dev libsdl2-image-dev"

# Type Debug instead of Release if you want to debug.
cmake -DCMAKE_BUILD_TYPE=Release .

make
```

### Fedora

Building InputDisplay requires these packages: cmake gcc-c++
SDL2-devel SDL2_image-devel.

Commands (after you download and cd to this directory):

```sh
su -c "dnf install cmake gcc-c++ SDL2-devel SDL2_image-devel"

# Type Debug instead of Release if you want to debug.
cmake -DCMAKE_BUILD_TYPE=Release .

make
```
