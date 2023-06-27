#include <string>

class CityData {
public:
    std::string name;
    std::string country;
    double latitude;
    double longitude;
    int population;

    CityData(std::string _name, std::string _country, double _latitude, double _longitude, int _population)
        : name(_name), country(_country), latitude(_latitude), longitude(_longitude), population(_population) {}
};
