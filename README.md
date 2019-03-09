# PID Control

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

<img src="imgs/output.gif" width="480" alt="Output" />

## Overview
This project implements 2 PID controllers to control the steering angle and throttle of a self driving car as it goes around the race track. Coordinate ascent algorithm was used to tune the gain parameters. 

## Dependencies
* [Simulator](https://github.com/udacity/self-driving-car-sim/releases)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
* cmake
* gcc/g++
* make
* openssl
* libuv
* zlib

## Build Instructions
1. Clone this repo.
2. Make a build directory: `mkdir build && cd $_`
3. Compile: `cmake .. && make`

## Run
* To run `./pid <output.csv>`
* To run twiddle training `./pid train`

---
