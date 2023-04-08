# EVDEV Actions

## Functionality

This tool allows certain configurable actions to be taken upon events from `evdev` devices. These actions include feeding a new event back into a device (useful for button remapping) and running an arbitrary command. This tool **cannot** prevent the original event from being processed by other userspace programs listening for `evdev` events, for example ones using `libinput`. It was originally created because there currently is no way to give extra mouse buttons functionality when using Mutter.

## Long-Term Solution

The functionality of this tool should ideally be moved into `libinput` and/or Wayland compositors.

## Todos

- Switch to libevdev, find out how to link to it using CMake
- Pass `/dev/input/by-id/` to libevdev
- Add file-based configuration for device(s) and actions
- Write Systemd unit file
- Write Arch Linux PKGBUILD file
