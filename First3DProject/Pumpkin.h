#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include<sstream>
#include <iostream>

class Pumpkin
{
public:
    std::vector<glm::vec3> vPumpkin;
    std::vector<unsigned int> fPumpkin;
    std::ifstream stream;
    float scale = 0.2f;
    std::vector<glm::vec2> UVPumpkin;

    std::vector<glm::vec3> PumpkinVertices;
    std::vector<glm::vec3> PumpkinNormals;

    std::vector<glm::vec3> all;
    
    Pumpkin();
};
