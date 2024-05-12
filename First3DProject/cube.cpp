#include "cube.h"

cube::cube()
{
    std::ifstream stream;
   
    stream.open("TeaPot.obj"); 

    for (std::string line; std::getline(stream, line);)
    {
        std::stringstream stringStream(line);
        std::string values;
        stringStream >> values;
        if (values == "v")
        {
            glm::vec3 tempvec3;
            stringStream >> values;
            tempvec3[0] = std::stof(values); //* scale
            stringStream >> values;
            tempvec3[1] = std::stof(values);
            stringStream >> values;
            tempvec3[2] = std::stof(values);
            vCube.push_back(tempvec3);
        }
        else if (values == "f")
        {
            glm::vec3 tempf;
            stringStream >> values;
            tempf[0] = std::stof(values);
            stringStream >> values;
            tempf[1] = std::stof(values);
            stringStream >> values;
            tempf[2] = std::stof(values);
            fCube.push_back(tempf);
        }
        else if (values == "vt")
        {
            glm::vec2 tempvec2;
            stringStream >> values;
            tempvec2.x = std::stof(values);
            stringStream >> values;
            tempvec2.y = std::stof(values);
            uvCube.push_back(tempvec2);
        }
    }
    stream.close();

    //std::cout << testStream.getline("f",) << std::endl;
}
