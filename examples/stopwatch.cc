#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>
#include <string>
#include <wiringPi.h>

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process {
    public:
        Stopwatch(){}
        void init();
        void start();
        void stop();
        void update();
        void lap();
        double seconds();
        int getcolor();

    private:
        bool running = false;
        high_resolution_clock::time_point start_time; 
        std::chrono::system_clock::duration sum;
        std::chrono::system_clock::duration previous_laptime;
        std::chrono::system_clock::duration lap_difference;
        int color;
};

void Stopwatch::init()
{
    sum = std::chrono::nanoseconds::zero();

    watch("start", [this](Event &e) {
        start();
    });
    watch("stop", [this](Event &e) {
       if(running){
        high_resolution_clock::time_point end_time = high_resolution_clock::now();
        running = false;
        std::chrono::system_clock::duration event = end_time - start_time;
        sum = sum + event;
       }
     });
    watch("lap", [this](Event &e) {
        lap();
    });
    
    watch("faster", [this](Event &e) {
        color = 4;
    });
    
    watch("slower", [this](Event &e) {
        color =5;
    });
}

void Stopwatch::start() {
        if(!running){
            start_time = high_resolution_clock::now();
            running = true;
            printf("started event\n");
            previous_laptime = std::chrono::nanoseconds::zero();
        }
}
void Stopwatch::update() {}
void Stopwatch::stop() {}
void Stopwatch::lap() {
        if(running){
            high_resolution_clock::time_point end_time = high_resolution_clock::now();
            std::chrono::system_clock::duration event = end_time - start_time;
            sum = sum + event;
       }
        lap_difference = previous_laptime - sum;

        if (seconds_type(lap_difference).count() < 0){
            std::cout << "this lap is slower than the last" << std::endl;
            std::cout << seconds_type(lap_difference).count() << std::endl;
            emit(Event("slower"));
        }
        else{
            std::cout << "this lap is faster than the last" << std::endl;
            std::cout << seconds_type(lap_difference).count() << std::endl;
            emit(Event("faster"));
        }
        
        previous_laptime = sum;
        sum = std::chrono::nanoseconds::zero();
        start_time = high_resolution_clock::now();
}


double Stopwatch::seconds(){
    if(running){
        auto sec = seconds_type(high_resolution_clock::now() - start_time + sum);
        return sec.count();
    }
    if(!running){
        auto sec = seconds_type(sum);
        return sec.count();}
}

int Stopwatch::getcolor(){
    return color;
    }

int main() {

     Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();
    
	wiringPiSetup();
	
	/*
    Pins map as follows:
	pinMode 1 (18)
	pinMode 4 (23)
	pinMode 5 (24)
	pinMode 0 (17)
	*/
	
	pinMode(1, INPUT);  // button
	pinMode(4, OUTPUT); // green
	pinMode(0, OUTPUT); // blue
	pinMode(5, OUTPUT); // red
	
    static int times_pressed = 0;

	for(;;)
	{
        // if button is not pressed 
		if(digitalRead(1) == LOW) { 
            digitalWrite(0, LOW);
	} 
        // if button is pressed for the first time
		if(digitalRead(1) == HIGH && times_pressed == 0){
            times_pressed += 1;
			m.emit(Event("start"));
            digitalWrite(0, HIGH); delay(500);
            digitalWrite(0, LOW); delay(500);
            printf("ready go! button is pressed!\n");
		}

        // if button is pressed any other time
		if(digitalRead(1) == HIGH && times_pressed != 0){
            times_pressed += 1;
			m.emit(Event("lap"));
            digitalWrite(watch.getcolor(), HIGH); delay(500);
            digitalWrite(watch.getcolor(), LOW); delay(500);
		}

        // if button is held down
        // emit "stop" event and exit this loop
	}
	return 0;
}
