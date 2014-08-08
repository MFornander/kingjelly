#!/bin/bash
## Bring a vanilla Debian installation to a KingJelly state
set -e

## Verify debian installation
EXPECTED="Linux arm 3.8.13-bone59 #1 SMP Fri Jul 4 22:52:56 UTC 2014 armv7l GNU/Linux"
ACTUAL="`uname -a`"

if [ "$EXPECTED" != "$ACTUAL" ]
then
  echo -e "Distro mismatch!\nExpected: $EXPECTED\nActual:   $ACTUAL"
  exit 1
fi
 

## Replace the DTB to enable PRUs
cp -n /boot/dtbs/3.8.13-bone59/am335x-boneblack.dtb /boot/dtbs/3.8.13-bone59/am335x-boneblack.dtb.old
cp debian-3.8.13-bone59.dtb /boot/dtbs/3.8.13-bone59/am335x-boneblack.dtb

## Copy network config
cp -n interfaces /etc/network/interfaces

## Install and autostart opc-server (LEDscape OPC server using PRUs)
cp ledscape-service /etc/init.d/
update-rc.d ledscape-service defaults

## Install and autostart kingjelly-service (custom OPC client and frame producer)
cp kingjelly-service /etc/init.d/
update-rc.d kingjelly-service defaults

## Disable Apache2 so we can use flask. There are 2 warnings during disable which 
## can be ignored
update-rc.d apache2 disable

## Install and autostart flask
cp flask-service /etc/init.d/
update-rc.d flask-service defaults

## TODO: Enable UART5 automatically
echo "Please edit /boot/uEnv.txt such that cmdline reads:
echo "cmdline=quiet init=/lib/systemd/systemd capemgr.enable_partno=BB-UART5"
echo

echo "Reboot to enable PRUs and awaken the KingJelly"
