#!/usr/bin/env python

import socket
import time
import sys
import random
from struct import *

HOST = 'localhost'    # The remote host
PORT = 30000              # The same port as used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#for i in range (0,255,50):
#	for j in range (0,2):
#		msg = pack('!?BBBB', j,i,255,255,255)
#		s.sendto(msg,(HOST, PORT))
#		time.sleep(5)
#		print "%d %d" % (j,i)

while True:
	values = [0] + [int(255*random.random()) for i in range(4)]
	print values
	msg = pack('!?BBBB', *values) 
	s.sendto(msg,(HOST, PORT))
	time.sleep(5);

s.close()