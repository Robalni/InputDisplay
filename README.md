InputDisplay
============

This program displays a controller and what inputs you do.  Any
controller works but you need to edit config.txt or a file in the
config directory to make it display the right things.  Right now you
get n64 and xbox 360 controller images.  I may add more later.

![screenshot Nintendo 64](https://i.imgur.com/VWgd9ip.png)
![screenshot Xbox 360](https://i.imgur.com/0d1oc5a.png)

## Compile

### Debian

Building InputDisplay requires these packages: cmake g++ libsdl2-dev
libsdl2-image-dev.

Commands (after you download and cd to this directory):

```sh
su -c "apt-get -y install cmake g++ libsdl2-dev libsdl2-image-dev"

# Type Debug instead of Release if you want to debug.
cmake -DCMAKE_BUILD_TYPE=Release .

make
```
