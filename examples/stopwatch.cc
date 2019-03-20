#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>
#include <string>

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

    private:
        bool running = false;
        high_resolution_clock::time_point start_time; 
        std::chrono::system_clock::duration sum;
        std::chrono::system_clock::duration previous_laptime;
        std::chrono::system_clock::duration lap_difference;
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
        //running = false;
        //sum = std::chrono::nanoseconds::zero();
        if(running){
            high_resolution_clock::time_point end_time = high_resolution_clock::now();
            //running = false;
            std::chrono::system_clock::duration event = end_time - start_time;
            sum = sum + event;
       }

        lap_difference = previous_laptime - sum;
        //std::cout << seconds() << std::endl;

        if (seconds_type(lap_difference).count() < 0){
            std::cout << "this lap is slower than the last" << std::endl;
            std::cout << seconds_type(lap_difference).count() << std::endl;
        }
        else{
            std::cout << "this lap is faster than the last" << std::endl;
            std::cout << seconds_type(lap_difference).count() << std::endl;
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

int main() {

    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("start"));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    m.emit(Event("lap"));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    m.emit(Event("lap"));
    std::this_thread::sleep_for(std::chrono::milliseconds(1100));


    m.emit(Event("lap"));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    m.emit(Event("lap"));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    m.emit(Event("lap"));

    m.emit(Event("stop"));
    

}
