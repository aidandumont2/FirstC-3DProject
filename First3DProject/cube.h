#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include<sstream>
#include <iostream>

class cube
{
public:
    std::vector<glm::vec3> vCube;
    std::vector<glm::vec3> fCube;
    std::vector<glm::vec2> uvCube;
    std::ifstream stream;
    float scale = 0.2f;

    std::vector<glm::vec3> all;
    cube();
};
