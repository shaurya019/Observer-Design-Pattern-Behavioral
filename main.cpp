#include <iostream>
#include <vector>

// Observer Interface
class Observer {
public:
    virtual void update(float temperature) = 0;
};

// Subject Class
class Subject {
private:
    std::vector<Observer*> observers;
    
protected:
    void notify(float temperature) {
        for (auto observer : observers) {
            observer->update(temperature);
        }
    }

public:
    Subject(const std::vector<Observer*>& obs) : observers(obs) {}
};

// Concrete Subject
class WeatherStation : public Subject {
private:
    float temperature;

public:
    WeatherStation(const std::vector<Observer*>& observers) : Subject(observers), temperature(0.0f) {}

    void setData(float newTemp) {
        temperature = newTemp;
        notify(temperature);
    }

    void add(float value) {
        temperature += value;
        notify(temperature);
    }

    void subtract(float value) {
        temperature -= value;
        notify(temperature);
    }

    float getTemperature() const {
        return temperature;
    }
};

// Concrete Observer
class PhoneDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Phone Display: Temperature updated to " << temperature << "°C" << std::endl;
    }
};

class WeatherApp : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Weather App: Temperature updated to " << temperature << "°C" << std::endl;
    }
};

int main() {
    PhoneDisplay phoneDisplay;
    WeatherApp weatherApp;

    // List of observers
    std::vector<Observer*> observers = { &phoneDisplay, &weatherApp };

    // Create WeatherStation with observers injected via constructor
    WeatherStation station(observers);

    // Change temperature state using different methods
    station.setData(25.0f);
    station.add(5.0f);
    station.subtract(3.0f);

    return 0;
}
