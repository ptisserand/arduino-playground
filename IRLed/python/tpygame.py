#!/usr/bin/env python

import serial
import Queue
import threading
import time
import pygame

keys = {
    0x51: ("left", pygame.K_LEFT),
    0x52: ("up", pygame.K_UP),
    0x53: ("right", pygame.K_RIGHT),
    0x54: ("down", pygame.K_DOWN),
    0x0d: ("OK", pygame.K_RETURN)
    }

running = True

class SerialThread(threading.Thread):
    def __init__(self, dev, baudrate):
        threading.Thread.__init__(self)
        self.ser = serial.Serial(dev, baudrate, timeout=3)
        
    def run(self):
        while running:
            dd = self.ser.read()
            if len(dd) == 1:
                val = ord(dd)
                if keys.has_key(val):
                    print keys[val][0]
                    pygame.event.post(pygame.event.Event(pygame.KEYDOWN, key=keys[val][1]))
                    


w = 500
h = 500

screen = pygame.display.set_mode((w, h))
clock = pygame.time.Clock()

def my_event(event):
    if event.key == pygame.K_UP:
        print "Key UP"
    elif event.key == pygame.K_DOWN:
        print "Key Down"
    elif event.key == pygame.K_LEFT:
        print "Key left"
    elif event.key == pygame.K_RIGHT:
        print "Key right"

dath = SerialThread("/dev/ttyUSB0", 9600)
dath.start()

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            my_event(event)
    pygame.display.flip()
