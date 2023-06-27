#include "QuadTree.h"
#include "Node.h"
#include "Point.h"
#include "loadcities.cpp"
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace chrono;
int main()
{
// Crear un Quadtree vacío.
  QuadTree quadtree;
// Creacion de base de datos
  vector<CityData> cities = loadCities();
//--------------EXPERIMENTACION INSERT --------------------------------------------------------------
  // Los tamaños de los lotes que quieres probar
  int citiesToRead;
  cout << "¿Cuantas ciudades quieres leer? " << endl;
  std::cin >> citiesToRead;

    // Loop a través de cada tamaño de lote
        // Tomar el tiempo inicial
        auto start = high_resolution_clock::now();

        // Insertar ciudades en el QuadTree
        for (int i = 0; i < citiesToRead; ++i) {
            quadtree.insert(Point(cities[i].latitude, cities[i].longitude), cities[i].name, cities[i].country, cities[i].population);
        }

        // Tomar el tiempo final
        auto stop = high_resolution_clock::now();

        // Calcular y mostrar la duración
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Tiempo para insertar " << citiesToRead << " ciudades: " << duration.count() << " microsegundos" << endl;
//-----------------------------------------------------------------------------------------------
  // totalNodes y totalPoints
  int totalNodes = quadtree.totalNodes();
  int totalPoints = quadtree.totalPoints();

  std::cout << "Total de nodos en el Quadtree: " << totalNodes << std::endl;
  std::cout << "Total de puntos en el Quadtree: " << totalPoints << std::endl;
// LIST()
  quadtree.list();

  // IMPRIMIR QUADTREE
  //quadtree.printQuadTree();

  return 0;
}
