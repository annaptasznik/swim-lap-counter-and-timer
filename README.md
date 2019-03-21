# Raspberry Pi Swim Lap Counter and Timer
A poolside device for swimmers to count and time their laps, as well as track speed/distance progress between sessions.

Project completed for UW's Software Engineering for Embedded Systems course.

## Overview
The purpose of this project is to build a device to assist swimmers with counting, timing, and tracking progress of their swim laps. 

Using a Raspberry Pi,button, and LED, the device will register every button click as the beginning of a new lap. It will count the number of laps (ie, button clicks), as well as count the time between clicks. LED color indicates whether the most recent lap was slower or faster than the last. Finally, a swimmer registers the end of their session by holding down the button, after which their results are written to disk for later review.

The primary goal of this project is to extend Event Loop Manager (elma) for use on the Raspberry Pi, as well as to implement hardware features with WiringPi.

## Project progress
The following are project milestones.

| Goal Date | Description | Date Accomplished |
|---------- | ----------- | ----------------- |
| 3/12/2019 | Create skeleton code with core elma functions/ stopwatch / counter | 3/16/2019 |
| 3/15/2019 | Add ability to update Google Sheet | No API for C++, rethinking |
| 3/18/2019 | Port C++ code to Raspberry Pi | 3/18/2019 |
| 3/22/2019 | Get button working on Raspberry Pi with C++ | 3/18/2019 |
| 3/25/2019 | Add button function into code | 3/19/2019 |
| 3/25/2019 | Complete documentation for project | |

## Installation
### Hardware
The following items are necessary to get started:
* Raspberry Pi 3 Model B
* 1 [Squid](https://github.com/simonmonk/squid) RGB Light
* A button

LED and button leads are connected as per the below diagram.
![Image of Schematic](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/pi_schematic.PNG)

Of course, it's nice to see a photo as well.

![Image of Pi](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/pi_photo.png)

### Software
To install the swim lap timer and counter, do the following on the Raspberry Pi.

First, make sure dependencies are installed. This asssumes Raspbian OS.

```
sudo apt-get update
sudo apt-get install -y cmake
sudo apt-get install -y doxygen
sudo apt-get install -y cmake
sudo apt-get install -y libssl-dev
sudo apt-get install -y wiringPi
```

Next, clone and build the swim lap counter.
```
git clone https://github.com/annaptasznik/swim-lap-counter-and-timer
cd swim-lap-counter-and-timer
make
make docs
```

Finally, execute it using:
```
cd examples
bin/stopwatch
```

## Architecture
To do: how was this designed, what choices were made, how are things organized?

## Results
### Running Program
When running `bin/stopwatch`, the program runs and waits for a button click. When the first button click is registered, it begins timing and counting the swim lap.
This state is reflected in the console messaging, as well as by the blue LED light.

![Image of Blue](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/blue.PNG)

With every subsequent click, the time in seconds is printed to the console. The light color indicates whether the current lap is faster (green) or slower (red) than the previous lap.

![Image of Green](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/green.PNG)
![Image of Red](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/red.PNG)

Finally, to end all stopwatch() processes and turn off the program, the user must hold the button down for longer than a second. Session results are printed to the console and the LED turns off.

![Image of End](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/end.PNG)


## Acknowledgements
Many thanks to those who helped me, including but not limited to [Professor Klavins](https://github.com/klavinslab), ECEP520 TAs Justin and Henry, Juan Escobar, David Wu, and other classmates.

## References
* [Elma](https://github.com/klavinslab/elma) (Event Loop Manager) library
* Example code from previous ECEP520 assignments as well as [Elma-project](https://github.com/klavinslab/elma_project)
* [WiringPi](http://wiringpi.com/) documentation and example code
* [Fritzing](http://fritzing.org/home/) for schematic graphic