#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

//Extraer los vertices e indices de un archivo .obj

class ObjLoader {
public:
    // Si empieza con v es un vértice, entomces traemos el x,y,z
    std::vector<glm::vec3> vertices;
    // Si empieza con f es una cara, entonces traemos los índices
    std::vector<GLuint> indices;
    
    //Asignamos un minimo y maximo de la altura
    float minY = 99999.0f;
    float maxY = -99999.0f;

    //Agregamos tambien para X y Z ya que necesitamos centrar
    float minX = 99999.0f;
    float maxX = -99999.0f;
    float minZ = 99999.0f;
    float maxZ = -99999.0f;

    //Ahra tenemos que cargar el archivo obj
    bool cargarModelo(const char* rutaArchivo) {
        std::ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
            return false;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream iss(linea);
            std::string tipo;
            iss >> tipo;

            if (tipo == "v") {
                //Vertice
                glm::vec3 vertice;
                iss >> vertice.x >> vertice.y >> vertice.z;
                vertices.push_back(vertice);

                // Actualizamos minY y maxY
                if (vertice.y < minY) minY = vertice.y;
                if (vertice.y > maxY) maxY = vertice.y;
                //Igualmente agregamos sus "if"
                if (vertice.x < minX) minX = vertice.x;
                if (vertice.x > maxX) maxX = vertice.x;
                if (vertice.z < minZ) minZ = vertice.z;
                if (vertice.z > maxZ) maxZ = vertice.z;

            } else if (tipo == "f") {
                std::string vertice1, vertice2, vertice3;
                iss >> vertice1 >> vertice2 >> vertice3;
                // Los índices en el archivo OBJ comienzan desde 1, así que restamos
                indices.push_back(obtenerIndice(vertice1));
                indices.push_back(obtenerIndice(vertice2));
                indices.push_back(obtenerIndice(vertice3));
            }
        }

        // Imprimimos información solicitada (especificaciones del pdf: nombre, vértices, max y min)
        std::cout << "Nombre: " << rutaArchivo << "\n";
        std::cout << "Número de vértices: " << vertices.size() << "\n";
        std::cout << "Mínimo: " << minY << ", Máximo: " << maxY << "\n";

        return true;
    }

    private:
    // Extraer el primer vértice y convertirlo a entero
    GLuint obtenerIndice(const std::string& token) {
        size_t pos = token.find('/');
        if (pos != std::string::npos) {
            return std::stoi(token.substr(0, pos)) - 1; // Restamos porque los índices en OBJ comienzan desde 1
        }
        return std::stoi(token) - 1; // Volvemos a restar
    }
};