# Music Visualizer

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

**Author**: Benjamin Kulis - [`bkulis2@illinois.edu`](mailto:bkulis2@illinois.edu)
## Overview
This is a music visualizer that was created via Cinder and KissFFT. In the visualization there are two lines: the top
one (blue) represents the time (aka the sound waves) and the bottom one (fuscia) represents the frequency (while the
amplitude represents the volume of said frequency). There are two modes you chose between see [Modes](##Modes).

## Build Requirements
To run this Music Visualizer you need:
1. 64-bit Microsoft Windows
2. Visual Studio 2010 Ultimate
3. Cinder 0.8.4 VC10
4. KissFFT CinderBlock

## Installation
1. If you don't have Visual Studio 2010 Ultimate, [download it here](https://download.cnet.com/Microsoft-Visual-Studio-2010-Ultimate/3000-2383_4-75450998.html).
2. If you don't have Cinder, [download it here](https://libcinder.org/download) and follow the instructions in the [setup guide](https://libcinder.org/docs/guides/windows-setup/index.html).
3. Install the [Cinder-KissFFT library](https://github.com/BanTheRewind/Cinder-KissFft) and link it to VC10 via 
[this guide](https://www.tutorialspoint.com/how-to-include-libraries-in-visual-studio-2012).
4. Clone this repository using 
```git clone https://github.com/CS126SP20/final-project-bkulis2```
5. Build and run the project from Visual Studio.

## Documentation
This codebase attempts to follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with
Javados documentation ([see guide here](https://www.oracle.com/technical-resources/articles/java/javadoc-tool.html)).

## Modes
1. __For the Interactive Sine Visualizer:__
* Click on the sine wave image and press play. 
* You can then interact with your mouse to play a sine wave:
    * Adjust frequency by moving your mouse horizontally
    * Adjust its volume by moving your mouse vertically
2. __To Run the Visualizer for a Song:__ 
* Enter a commandline argument for the name of a song you want to play (make sure its located in the ``/assets`` folder).
* On the home screen, you should see text for the song name you chose. 
* Click music note to run the visualizer and enjoy.