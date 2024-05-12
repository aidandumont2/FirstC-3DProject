#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include<sstream>
#include <iostream>

class TeaPotOBJ
{
public:
    std::vector<glm::vec3> vTeaPot;
    std::vector<unsigned int> fTeaPot;
    std::ifstream stream;
    float scale = 0.2f;
    std::vector<glm::vec2> UVTeaPot;

    std::vector<glm::vec3> teaPotVertices;
    std::vector<glm::vec3> teaPotNormals;

    std::vector<glm::vec3> all;
    
    TeaPotOBJ();
    
    
};
