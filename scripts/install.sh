#!/bin/bash
## Bring a vanilla Debian installation to a KingJelly state
set -e

## Verify debian installation
EXPECTED="Linux beaglebone 3.8.13-bone47 #1 SMP Fri Apr 11 01:36:09 UTC 2014 armv7l GNU/Linux"
ACTUAL="`uname -a`"

if [ "$EXPECTED" != "$ACTUAL" ]
then
  echo -e "Distro mismatch!\nExpected: $EXPECTED\nActual:   $ACTUAL"
  exit 1
fi
 

## Replace the DTB to enable PRUs
cp -n /boot/uboot/dtbs/am335x-boneblack.dtb /boot/uboot/dtbs/am335x-boneblack.dtb.old
cp debian-3.8.13-bone47.dtb /boot/uboot/dtbs/am335x-boneblack.dtb

## Install and autostart opc-server (LEDscape OPC server using PRUs)
cp opc /etc/init.d/
update-rc.d opc defaults

## Install and autostart jellybrain (custom OPC client and frame producer)
cp jellyservice /etc/init.d/
update-rc.d jellyservice defaults

echo "Reboot to enable PRUs and awaken the KingJelly'
