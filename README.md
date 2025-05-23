# Minecraft Education Edition All Ports PoC
## Description
This program will send "Hello from Minecraft Education Edition All Ports PoC" to any device sending a message to it on port 6666 over UDP.

The server is intended to be used on Android devices. The tester is meant to be ran on any POSIX-compliant system.

## Details about the vulnerability
This vulnerability is similar to qbittorrent/qBittorrent#1758.

Prerequisites:

* A router that supports UPnP
* Minecraft Education Edition

Steps to reproduce:

1. Launch the game
2. Choose "If you don't have an account, try a demo lesson."
3. Tick "Accept Terms"
4. Press the button that says "Play"
5. Press "Start Lesson"
6. Press the "Confirm" button in the screen safe area window
7. Choose "Fantastic Fairgrounds"
8. Press "CREATE WORLD"

After doing these steps, there should be open external port 0 in your router, which opens [all ports](https://github.com/qbittorrent/qBittorrent/issues/1758#issuecomment-47003605), and you can run the tester program with your public IP address to confirm.

## Building
```
ANDROID_NDK_HOME=/path/to/ndk make
```

Optionally set the `ARCH` environment variable to whatever architecture you're compiling the server for (armv7a is the default).

You can also set the minimum API level you're compiling for with the `ANDROID_API_LEVEL` environment variable (optional) (defaults to 21).

Optionally set the `ANDROID_CFLAGS` variable to change the compiler flags for the server program (defaults to the same value of `CFLAGS`).

## Installation
Through ADB:
```
adb push /path/to/edu-edition-all-ports-server /data/local/tmp
```

## Usage
Run `/path/to/edu-edition-all-ports-server` on an Android device, and then send something to port 6666 over UDP to that device using its public IP address.
It should send "Hello from Minecraft Education Edition All Ports PoC" in a packet back.

Use `/path/to/edu-edition-all-ports-tester <public IP>` to test if a device is vulnerable.
If you get a whole lot of retransmits, it's probably not.

Through `adb shell`:
```
cd /data/local/tmp
./edu-edition-all-ports-server
```

## License
MIT License. Full text available in LICENSE.txt.

## Notes
The vulnerability doesn't open all UDP ports for me, but it creates a pinhole
that shows as internal port 0, external port 0 in my router.

I suspect my router is not [standard-compliant](https://github.com/qbittorrent/qBittorrent/issues/1758#issuecomment-47003605).

If you have a known standard-compliant UPnP router, and it works for you, create an issue on this repository.

This vulnerability is only known by me to work on Android, although it will probably work on other platforms too.
