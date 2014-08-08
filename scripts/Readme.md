1. Download and flash BBB 
  1. go to http://elinux.org/BeagleBoardDebian#eMMC:_BeagleBone_Black
  2. wget https://rcn-ee.net/deb/flasher/wheezy/BBB-eMMC-flasher-debian-7.5-console-armhf-2014-07-06-2gb.img.xz
  3. follow instructions on web page 


2. Get the BBB on the internet via eth0 
  1. change /etc/network/interfaces for static IP vs dhcp


3. Login as root / root


4. Set Time/Date so that apt-get/git etc. works (otherwise its set to the future)
  1. dpkg-reconfigure tzdata
  2. ntpdate pool.ntp.org


5. Update apt and install make/gcc/etc
  1. apt-get update
  2. apt-get upgrade
  3. apt-get install build-essential


6. Install flask
  1. apt-get install python-pip
  2. pip install Flask


7. Clone kingjelly
  1. git clone https://github.com/MFornander/kingjelly.git /opt/git/kingjelly
  2. cd /opt/git/kingjelly/Release
  3. make


8. Clone LEDscape
  1. git clone https://github.com/Yona-Appletree/LEDscape.git /opt/git/LEDscape
  2. cd /opt/git/LEDscape
  3. make


9. Run install script
  1. cd /opt/git/kingjelly/scripts
  2. ./install.sh


10. Enable UART5
  1. Modify /boot/uEnv.txt such that the command line reads: "cmdline=quiet init=/lib/systemd/systemd capemgr.enable_partno=BB-UART"


11. Reboot
  1. reboot -f
