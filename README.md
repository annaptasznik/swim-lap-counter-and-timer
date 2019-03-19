# Raspberry Pi Swim Lap Counter and Timer
A poolside device for swimmers to count and time their laps, as well as track speed/distance progress between sessions. The swimmer presses a button with each lap; the device does the rest!

## Overview
The purpose of this project is to build a device to assist swimmers with counting, timing, and tracking progress of their swim laps. Using a Raspberry Pi and button, the device will register every button click as the beginning of a new lap. It will count the number of laps (ie, button clicks), as well as count the time between clicks. This tracks the speed of the swim laps, as well a total distance of the swim, important metrics to training swimmers. A swimmer registers the end of their session with two button clicks, after which their results are uploaded to a Google Spreadsheet using the Google Sheets API.

The primary goal of this project is to extend Event Loop Manager (elma) for use on the Raspberry Pi, as well as to implement hardware features with WiringPi and logging through the Google Sheets API.

## Installation
### Software
To do: installation instructions / list dependencies

### Hardware
The following items are necessary to get started:
* Raspberry Pi 3 Model B
* 1 [Squid](https://github.com/simonmonk/squid) RGB Light
* A button


![Image of Pi](https://github.com/annaptasznik/swim-lap-counter-and-timer/blob/master/images/pi_photo.png)

## Execution
To do: how do you run this?

## Architecture
To do: how was this designed, what choices were made, how are things organized?

## Results
To do: Show results of testing/running your code.

## Acknowledgements
To do: Mention anyone who helped you.

## References
* [Elma](https://github.com/klavinslab/elma) (Event Loop Manager) library
* Example code from previous ECEP520 assignments as well as [Elma-project](https://github.com/klavinslab/elma_project)
* [WiringPi](http://wiringpi.com/) documentation and example code

## Defining Success
The following are milestones that will define the success of my project.

| Goal Date | Description | Date Accomplished |
|---------- | ----------- | ----------------- |
| 3/12/2019 | Create skeleton code with core elma functions/ stopwatch / counter | |
| 3/15/2019 | Add ability to update Google Sheet | No API for C++, rethinking |
| 3/18/2019 | Port C++ code to Raspberry Pi | Partially complete |
| 3/22/2019 | Get button working on Raspberry Pi with C++ | Not yet working in C++|
| 3/25/2019 | Add button function into code | |
| 3/25/2019 | Complete documentation for project | |

