#!/bin/bash
### Patch a Debian DTB to enable the PRUs
set -e

LIVE="/boot/uboot/dtbs/am335x-boneblack"
TEMP="debian-`uname -r`"


### FETCH DTB to DTS
dtc -O dts -o $TEMP.dts -I dtb $LIVE.dtb

### PATCH DTS
#(sed todo)

### STORE DTS to DTB
#dtc -O dtb -o $TEMP.dtb -I dts $TEMP.dts
#cp -n $LIVE.dtb $LIVE.dtb.old
#cp $TEMP.dtb $LIVE.dtb

