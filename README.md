# Raspberry Pi Swim Lap Counter and Timer
A poolside device for swimmers to count and time their laps, as well as track speed/distance progress between sessions.

Project completed for UW's Software Engineering for Embedded Systems course.

## Overview
The purpose of this project is to build a device prototype that assists swimmers with counting, timing, and tracking progress of their swim laps. 

Using a Raspberry Pi, button, and LED, the device registers every button click as the beginning of a new lap. It counts the number of laps (ie, button clicks), as well the time between clicks. LED color indicates whether the most recent lap was slower or faster than the last. Finally, a swimmer registers the end of their session by holding down the button, after which their results are written to disk for later review.

The primary goal of this project is to extend Event Loop Manager (elma) for use on the Raspberry Pi, as well as to implement hardware features with WiringPi.

## Project progress
The following are project milestones.

| Goal Date | Description | Date Accomplished |
|---------- | ----------- | ----------------- |
| 3/12/2019 | Create skeleton code with core elma functions/ stopwatch / counter | 3/16/2019 |
| 3/15/2019 | Add ability to write file | 3/21/2019 |
| 3/18/2019 | Port C++ code to Raspberry Pi | 3/18/2019 |
| 3/22/2019 | Get button working on Raspberry Pi with C++ | 3/18/2019 |
| 3/23/2019 | Add button function into code | 3/19/2019 |
| 3/23/2019 | Complete documentation for project |3/22/2019 |

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
To install the swim lap timer and counter, do the following on the Raspberry Pi (Raspbian OS).

First, install dependencies.

```
sudo apt-get update
sudo apt-get install -y cmake
sudo apt-get install -y doxygen
sudo apt-get install -y cmake
sudo apt-get install -y libssl-dev
sudo apt-get install -y wiringPi
```

Next,to clone and build the swim lap counter:
```
git clone https://github.com/annaptasznik/swim-lap-counter-and-timer
cd swim-lap-counter-and-timer
make
```

Finally, execute it using (note, you may execute without building. A compiled version is located at `bin/laps`):
```
cd examples
bin/laps
```

## Architecture
### Design Overview
This project is largely built around a custom elma process called `Stopwatch` which handles time tracking and lap counting. When the `Stopwatch` process is initialized via `init()`, it defines how various events will be handled, including the initial `start`, final `stop`, and consistent `lap` clicks. These events are emitted in `main()`, where button clicks are registered using WiringPi functions. In other words, button clicks are registered  in `main()` and used to trigger an action defined in `Stopwatch`.

The events `start`, `lap`, and `stop` correspond to different LED responses. This behavior was designed to give a swimmer quick feedback about their speed.

![Image of Events](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/events.PNG)


## Results
### Running the Program
When running `bin/stopwatch`, the program runs and waits for a button click. When the first button click is registered, it begins timing and counting the swim lap.
This state is reflected in the console messaging, as well as by the blue LED light.

![Image of Blue](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/blue.png)

With every subsequent click, the time in seconds is printed to the console. The light color indicates whether the current lap is faster (green) or slower (red) than the previous lap.

![Image of Green](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/green.png)

![Image of Red](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/red.png)

Finally, to end all stopwatch() processes and turn off the program, the user must hold the button down for longer than a second. Session results are printed to the console and the LED turns off.

![Image of End](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/end.png)

When a session is completed, all results are written to a file `/examples/session_results.csv`. This file simply shows each lap time (in seconds).

![Image of CSV](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/session_results.PNG)

## Acknowledgements
Many thanks to those who helped me, including but not limited to [Professor Klavins](https://github.com/klavinslab), ECEP520 TAs Justin and Henry, Juan Escobar, David Wu, and other classmates.

## References
* [Elma](https://github.com/klavinslab/elma) (Event Loop Manager) library
* Example code from previous ECEP520 assignments as well as [Elma-project](https://github.com/klavinslab/elma_project)
* [WiringPi](http://wiringpi.com/) documentation and example code
* [Fritzing](http://fritzing.org/home/) for schematic graphic