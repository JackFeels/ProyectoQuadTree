#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CityData.h"

std::vector<CityData> loadCities()
{
    std::vector<CityData> cities;
    std::ifstream file("/Users/jackfeels/Desktop/U/Semestre 4/Est de Datos/Labs/ProyectoQuadTree/worldcitiespop_fixed.csv");
    std::string line;
    // Salta linea de encabezado
    getline(file, line);

    // Leer líneas del archivo
    while (getline(file, line))
    {
        istringstream ss(line);
        string country, city, accentCity, region;
        double longitude, latitude;
        int population;

        // Parsear la línea (de acuerdo al formato "Country;City;AccentCity;Region;Population;Latitude;Longitude;geopoint").
        getline(ss, country, ';');
        getline(ss, city, ';');
        getline(ss, accentCity, ';');
        getline(ss, region, ';');

        // Parsear la población como un entero
        string temp;
        getline(ss, temp, ';');
        population = stoi(temp);

        // Parsear la latitud como un double
        getline(ss, temp, ';');
        latitude = stod(temp);

        // Parsear la longitud como un double
        getline(ss, temp, ';');
        longitude = stod(temp);

        // Ignorar el campo geopoint
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        CityData cityData(city, country, latitude, longitude, population);
        cities.push_back(cityData);
    }
    return cities;
}
