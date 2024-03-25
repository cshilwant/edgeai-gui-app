# edgeai-gui-app
EdgeAI QT5 Demo for TI SoC based platforms

This document walks through how to build, install, and run edgeai-gui-app

# Installation

## Pre-requisites

#### Install the Linux SDK package for Qt tools

Download and install linux installer 9.0 or later version

- [TDA4VM](https://dr-download.ti.com/software-development/software-development-kit-sdk/MD-4K6R4tqhZI/09.00.00.08/ti-processor-sdk-linux-edgeai-j721e-evm-09_00_00_08-Linux-x86-Install.bin)

Follow the installation instructions and complete the SDK installation.

#### Clone this repo
```
git clone https://git.ti.com/git/apps/edgeai-gui-app/git
```

## Cross-Compilation for the target
```
# Setup the environment for Qt cross-compilation
source <linux_installer_path>/linux-devkit/environment-setup

# This should change the prompt to show something line "[linux-devkit]:~>"
[linux-devkit]:~> cd edgeai-gui-app
[linux-devkit]:~> mkdir build
[linux-devkit]:~> cd build
[linux-devkit]:~> qmake ../edgeai-gui-app.pro
[linux-devkit]:~> make
```
If all goes well then an executable by name `edgeai-gui-app` will be generated under the `build` directory

Copy this executable to the target

## Running the GUI on the target

Connect a mouse and optionally a keyboard to the SK board to control the GUI.

Transfer the following content to the target under a common directory, say `edgeai-gui-app`
- edgeai-gui-app/build/edgeai-gui-app

Run the following on the target. For the following, it is assumed that the project has been copied to `/home/root`.
Also, the platform is chosen to be TDA4VMID-SK for demonstration purposes.

```
root@tda4vm-sk:~# cd /home/root/edgeai-gui-app
root@tda4vm-sk:~# export SOC=j721e  #(j721e,am62a,j721s2,j784s4,j722s)
root@tda4vm-sk:~/edgeai-gui-app# ./edgeai-gui-app -platform linuxfb

```
This will launch the GUI.

