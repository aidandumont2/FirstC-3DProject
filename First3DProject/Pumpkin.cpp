#include "Pumpkin.h"

Pumpkin::Pumpkin()
{
    try
    {
        std::ifstream stream;
        //stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        stream.open("Pumpkin.obj");//TeaPot.obj

        for(std::string line; std::getline(stream, line);)
        {
            std::stringstream stringStream (line);
            std::string values;
            stringStream >> values;
            if(values == "v")
            {
                glm::vec3 tempVec3;
                stringStream >> values;
                tempVec3[0] = std::stof(values)* scale;
                stringStream >> values;
                tempVec3[1] = std::stof(values) * scale;
                stringStream >> values;
                tempVec3[2] = std::stof(values) * scale;
                vPumpkin.push_back(tempVec3);
            }
            else if(values == "f")
            {
                unsigned int tempInt;
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fPumpkin.push_back(tempInt);
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fPumpkin.push_back(tempInt);
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fPumpkin.push_back(tempInt);
            }
        }
        stream.close();
        
        //std::cout << testStream.getline("f",) << std::endl;
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERR : File cant be read" << e.what() << std::endl;
    }

    for (int indice : fPumpkin)
    {
        PumpkinVertices.push_back(vPumpkin[indice]);
    }

    for (int i = 0; i < PumpkinVertices.size(); i+=3)
    {
        glm::vec3 p1 = PumpkinVertices[i];
        glm::vec3 p2 = PumpkinVertices[i+1];
        glm::vec3 p3 = PumpkinVertices[i+2];

        glm::vec3 u = p2-p1;
        glm::vec3 v = p3-p1;
        glm::vec3 normal =  glm::cross(u,v);
        PumpkinNormals.push_back(normal);
        PumpkinNormals.push_back(normal);
        PumpkinNormals.push_back(normal);
    }

    for (int i =0; i < PumpkinNormals.size(); i++)
    {
        all.push_back(PumpkinVertices[i]);
        all.push_back(PumpkinNormals[i]);
    }
}

