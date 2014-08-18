.) download and flash BBB 
	a.) go to http://elinux.org/BeagleBoardDebian#eMMC:_BeagleBone_Black
	b.) wget https://rcn-ee.net/deb/flasher/wheezy/BBB-eMMC-flasher-debian-7.5-console-armhf-2014-07-06-2gb.img.xz
	c.) follow instructions on a.) 

1.) get the BBB on the internet via eth0 
	a.) change /etc/network/interfaces for static IP vs dhcp

2.) login as root 

3.) Set Time/Date so that apt-get/git etc. works (otherwise its set to the future)
	a.) dpkg-reconfigure tzdata
	b.) ntpdate pool.ntp.org

4.) update apt and install make/gcc/etc
	a.) apt-get update
	b.) apt-get upgrade
	c.) apt-get install build-essential

5.) install flask
           a.) apt-get install python-pip
	b.) pip install Flask

5.) git clone https://github.com/MFornander/kingjelly.git /opt/git/kingjelly
6.) cd /opt/git/kingjelly;make


7) git clone https://github.com/Yona-Appletree/LEDscape.git /opt/git/LEDscape
8.) cd /opt/git/LEDscape; make

	
9.) cd /opt/git/kingjelly/scripts
10.) ./install.sh

11.) reboot

