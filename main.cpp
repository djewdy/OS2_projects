#include <iostream>
#include <ostream>
#include <thread>
#include <map>
#include <string>
#include <chrono>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <random>
using namespace std::chrono_literals;

class WeatherSystem {
public:
    std::map<std::string, std::pair<int, std::string>> data;
    mutable std::mutex mtx;

    void updateWeather(const std::string& city, const std::string& condition) {
        std::lock_guard<std::mutex> lock(mtx);
        data[city].second = condition;
    }

    void incrementTemperature(const std::string& city) {
        std::lock_guard<std::mutex> lock(mtx);
        data[city].first++;
    }

   void printData() {
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& item : data) {
        // Check if the city is New York to print dashes before it
        if (item.first == "New York") {
            std::cout << "-----------------------------------\n";
        }

        std::cout << item.first << ": " << item.second.first << " degrees, " << item.second.second << std::endl;

        // Check if the city is Mumbai to print dashes after it
        if (item.first == "Mumbai") {
            std::cout << "-----------------------------------\n";
        }

        std::cout << std::endl;
    }
}

};

void SimulateWeather(WeatherSystem& system) {
    std::array<std::string, 3> conditions = {"windy", "sunny", "cloudy"};
    int conditionIndex = 0;

    std::random_device rd;  // Non-deterministic random device
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrib(0, conditions.size() - 1); // Define the range

      while (true) {
        for (auto& city : system.data) {
            int conditionIndex = distrib(gen);  // Generate a random index
            system.updateWeather(city.first, conditions[conditionIndex]);  // Update weather with a random condition
        }
        system.printData();
        std::this_thread::sleep_for(2s);
    }
}

void RefreshForecast(WeatherSystem& system) {
    while (true) {
        for (auto& city : system.data) {
            system.incrementTemperature(city.first);
        }
        system.printData();
        std::this_thread::sleep_for(2s);
    }
}

int main() {
    WeatherSystem system;
    system.data = {
        {"New York", {15, ""}},
        {"Mumbai", {21, ""}},
        {"Berlin", {18, ""}}
    };

    std::thread weatherThread(SimulateWeather, std::ref(system));
    std::thread forecastThread(RefreshForecast, std::ref(system));

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();

    weatherThread.join();
    forecastThread.join();

    return 0;
}
