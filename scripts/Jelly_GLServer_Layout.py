#!/usr/bin/python

from math import *

MULTIPLIER = 1
# number of strands
NUM_STRANDS = 16

# number of LEDs per strand
NUM_LEDS = 100

# horizontal radius in m
RADIUS_H = 1 * MULTIPLIER 

# vertical radius in m
RADIUS_V = 0.6 * MULTIPLIER  

# length of LED strand in m
LEN_STRAND = 3.0 * MULTIPLIER

# distance between LEDs in m
DIST_BTWN_LEDS = LEN_STRAND / NUM_LEDS


lines = []

# Arrange the strands in a circular pattern around the y axis for RADIUS_H
for delta in map(radians, [x * 360.0 / NUM_STRANDS for x in range(NUM_STRANDS)]):
    # per led on a strand, draw a 90d arc with RADIUS_V and then a vertical part
    for t in [l * DIST_BTWN_LEDS for l in range(NUM_LEDS)]:
        theta = t / RADIUS_H
      
        if(theta <= pi / 2):
            x = cos(delta) * sin(theta) * RADIUS_H
            y = cos(theta) * RADIUS_V   
            z = sin(delta) * sin(theta) * RADIUS_H
        else:
            # we are past 90deg
            y = y - DIST_BTWN_LEDS

         
        lines.append('  {"point": [%.2f, %.2f, %.2f]}' % (x, y, z))

        
print '[\n' + ',\n'.join(lines) + '\n]'
