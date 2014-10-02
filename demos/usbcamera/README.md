# USB Camera

## Driver

pcDuino supports USB cameras that are compliant with the USB Video Class (UVC) specification using the `uvcvideo` driver. Supported cameras will be accessible via the device nodes `/dev/video0`, `/dev/video1`, etc...

## Program

### Viewer

To monitor your USB camera install the application `guvcview` (`sudo apt-get install guvcview`). 

### Simple Catpure

  sudo apt-get install streamer
  ./bash.sh

### Advanced Capture

Using Python and OpenCV you can control when frames are captured and perform some image processing to further control what is done.

  sudo apt-get install python-opencv python-numpy
  ./python.py
