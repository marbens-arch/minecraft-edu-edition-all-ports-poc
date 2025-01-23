# Minecraft Education Edition All Ports PoC
## Description
This program will send "Hello from Minecraft Education Edition All Ports PoC" to any device sending a message to it on port 6666 over UDP.

This is intended to be used on Android devices for the security bug in Minecraft Education Edition, where it opens all UDP ports, instead of just the needed ones.

## Installation
```
ANDROID_NDK_HOME=/path/to/ndk make -e
```

Optionally set the `ARCH` environment variable to whatever architecture you're compiling for (armv7a is the default).

You can also set the minimum API level you're compiling for with the `ANDROID_API_LEVEL` environment variable (optional) (defaults to 21).

## Usage
Run `/path/to/edu-edition-all-ports` on a device, and then send something to port 6666 over UDP to that device using its public IP address.
It should send "Hello from Minecraft Education Edition All Ports PoC" in a packet back.

`nc -u <public ip> 6666` on Linux should output the same packet data to stdout, as long as you put some data in stdin, for example, by typing something in the terminal and pressing enter. `nc` sends unencrypted packets, so don't put anything private in there!

## License
Temporarily all rights reserved, to prevent people from publishing this exploit, which will also publish the vulnerability, which is currently unfixed.
