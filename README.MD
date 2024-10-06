## A complete end to end rewrite of the Freenove Robot Dog Kit for Raspberry Pi code

I borrowed this robot from school to experiment with it and get it working, and while the hardware is mostly solid, the software makes some... *interesting choices*, to put it mildly. For example, it uses a GUI version of Raspbian on the RPI, requiring the user to remote into the thing with VNC just to access the terminal, run the client script, and essentially nothing else. I get how this might help a beginner, but I still feel like it's a waste of resources. Also, the robot functions through wifi, and needs to be connected to the same network as the machine running the client that controls it, which makes it not very portable, as you'd have to connect it to wifi if you ever want to bring it somewhere other than where it was assembled, and also anywhere without a proper wifi connection becomes pretty much off limits without doing some hotspot shenanigans. The best solution for me is to rewrite the code to eliminate those problems.

### Features
- Runs on an headless version of Raspbian (no GUI), with a C++ client instead of a python one for speed
- Connects via bluetooth instead of wifi to give you an easier time carrying it around
- Uses a smartphone app instead of a windows app as a client for portability (written in react native for cross platform compatibility)
- Automatic stabilization when walking
- Made to be as independent from the client app as possible

## Bonus stuff
I'll include a couple of extra things I developed for the robot in my time experimenting with it, such as:
- Freecad model of the motor-leg attachment piece, which can be adjusted to fit different motors in case a replacement is needed (intended for 3D printing)
- Freecad model of the "feet" of the robot (the last piece of the legs) which are adjustable for the same reason as the other model above, and also offer a wider design that makes the robot more stable (intended for 3D printing)