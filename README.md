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

## Details
For the steering PID controller, the proportional section is used to minimize the cross track error and keep the car in the middle of the road; the derivate is used to damped the oscillations; the system did not have a inherent bias, however the integral part was still useful to get to minimize the error over time.

The hyper-parameters were manually tuned by a trial method. Once we had a good estimate, coordinate ascent was used to fine tune the parameters. The coordinate ascent (twiddle) algorithm was used to go through multiple parameters and pick the ones with the lowest error. Additional error cost was added to the function if the vehicle drove off the road.

The algorithm did not perform too well at speeds above 60 MPH. To drive the vehicle at faster speeds, the reference speed was lowered based on the cross train error.

One other improvement to the system was adding a windowed smoothing filter to the error difference. This helped remove high frequency components from the final output.

![alt text](docs/diff_filter.png)
