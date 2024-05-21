#include <array>
#include <iostream>
#include <iterator>
#include <thread>
#include <map>
#include <string>
#include <chrono>
#include <mutex>
#include "ArrayClass.cpp"
using namespace std::chrono_literals;



void RefreshForecast(std::map<std::string , int> forecastMap){
    while(true){
        
        for(auto& item: forecastMap){
            item.second++;
            std::cout<<item.first<<"--"<<item.second<<std::endl;
        }
        std::this_thread::sleep_for(2000ms);
    }
}
void SimulateWeather(std::map<std::string, std::string>& weatherMap) {
    std::array<std::string, 3> conditions = {"windy", "sunny", "cloudy"};
    int conditionIndex = 0;

    while (true) {
        for (auto& item : weatherMap) {
            item.second = conditions[conditionIndex];
            conditionIndex = (conditionIndex + 1) % conditions.size(); // Move to the next condition
        }
        std::this_thread::sleep_for(2000ms);
    }
}

int main ()
{
    std::map<std::string , int> forecastMap={
        {"New York", 15}, {"mumbai",21}, {"Berlin",18}
    };

    std::map<std::string, std::string> weatherMap = {
        {"New York", ""}, {"Mumbai", ""}, {"Berlin", ""}
    };

    std::thread weatherThread(SimulateWeather, std::ref(weatherMap));
    std::thread forecastThread(RefreshForecast, std::ref(forecastMap), std::ref(weatherMap));
    std::cout << "Press enter to exit..." <<std::endl;
    std::cin.get();
    return 0;

}
// call the same global array in both functions and clear the terminal to print again the updated values 
//create a class for the global array to protect with mutex
//add it to github 