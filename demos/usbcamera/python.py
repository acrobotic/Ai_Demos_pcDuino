#!/usr/bin/env python
import cv

Keycode = {
  'ESCAPE' : 27,
  'SPACE'  : 32,
  'UP'     : 63232,
  'DOWN'   : 63233,
  'LEFT'   : 63234,
  'RIGHT'  : 63235,
}

cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(0)

while True:
  img = cv.QueryFrame(capture)
  cv.ShowImage("camera", img)
  keyinput = cv.WaitKey(10) 
  keyinput -= 0x100000
  if keyinput == Keycode['ESCAPE']:
    break

cv.DestroyWindow("camera")

