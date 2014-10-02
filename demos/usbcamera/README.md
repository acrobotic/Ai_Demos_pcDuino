# USB Camera

## Driver

pcDuino supports USB cameras that are compliant with the USB Video Class (UVC) specification using the `uvcvideo` driver. Supported cameras will be accessible via the device nodes `/dev/video0`, `/dev/video1`, etc...

## Program

### Viewer

To monitor your USB camera install the application `guvcview` (`sudo apt-get install guvcview`). 

### Simple Catpure

  sudo apt-get install streamer
  streamer -c /dev/video0 -b 16 -o output.jpg
