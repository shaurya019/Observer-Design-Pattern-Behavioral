#include <iostream>
#include <vector>
#include <string>

// class Observer: Declares an interface for objects that should be notified of changes in a subject.

// virtual void update(const std::string& message) = 0;: A pure virtual function that must be implemented by concrete observer classes. This function is called to update the observer with a new message.

class Observer {
    public:
    virtual void update(const std::string& message) = 0;
};

// Declares an interface for managing and notifying observers.

class Subject {
    private:
     std::vector<Observer*> observers;

     public:
     void attach(Observer* x){
         observers.push_back(x);
     }

     void detach(Observer* x){
        observers.erase(std::remove(observers.begin(), observers.end(), x), observers.end());
     }

     void notify(const std::string& x){
        for(auto observer:observers){
            observer->update(x);
        }
     }
};


class WeatherStation : public Subject{
    private:
    std::string weather;

    public:
    void setWeather(const std::string& newWeather){
        weather = newWeather;
        notify(weather);
    }
};


// Concrete Observer
class PhoneDisplay : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Phone Display: Weather updated to " << message << std::endl;
    }
};

class WeatherApp : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Weather App: Weather updated to " << message << std::endl;
    }
};


int main(){
    WeatherStation station;
    PhoneDisplay phoneDisplay;
    WeatherApp weatherApp;

    // Attach observers
    station.attach(&phoneDisplay);
    station.attach(&weatherApp);

    // Change weather state
    station.setWeather("Sunny");
    station.setWeather("Rainy");

    return 0;
}



// The & in station.attach(&weatherApp); is used to pass the address of the weatherApp object to the attach method. Here’s why it’s necessary:

// 1. Passing by Pointer
// Observer* observer in the attach method indicates that the method expects a pointer to an Observer object.
// By using &weatherApp, you are passing the address of the weatherApp instance, which allows the method to store a pointer to it in the observers vector.
// 2. Object vs. Pointer
// If you simply wrote station.attach(weatherApp);, it would attempt to pass the weatherApp object by value, which would lead to a compilation error since attach expects a pointer (Observer*), not an object of type Observer.
// Example Breakdown
// cpp
// Copy code
// station.attach(&weatherApp);
// &weatherApp: This takes the address of the weatherApp object, effectively creating a pointer to it.
// attach(&weatherApp): This passes that pointer to the attach method, which then adds it to the list of observers.
// Summary
// Using & allows you to pass a pointer to the existing weatherApp instance rather than creating a new copy, which is essential for the observer pattern to work correctly. This enables dynamic updates to the same instance when the subject (e.g., WeatherStation) notifies its observers.