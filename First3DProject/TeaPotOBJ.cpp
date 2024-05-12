#include "TeaPotOBJ.h"

TeaPotOBJ::TeaPotOBJ()
{
    try
    {
        std::ifstream stream;
        //stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        stream.open("TeaPot.obj");//TeaPot.obj

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
                vTeaPot.push_back(tempVec3);
            }
            else if(values == "f")
            {
                unsigned int tempInt;
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fTeaPot.push_back(tempInt);
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fTeaPot.push_back(tempInt);
                stringStream >> values;
                tempInt = std::stoi(values)-1;
                fTeaPot.push_back(tempInt);
            }
        }
        stream.close();
        
        //std::cout << testStream.getline("f",) << std::endl;
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERR : File cant be read" << e.what() << std::endl;
    }

    for (int indice : fTeaPot)
    {
        teaPotVertices.push_back(vTeaPot[indice]);
    }

    for (int i = 0; i < teaPotVertices.size(); i+=3)
    {
        glm::vec3 p1 = teaPotVertices[i];
        glm::vec3 p2 = teaPotVertices[i+1];
        glm::vec3 p3 = teaPotVertices[i+2];

        glm::vec3 u = p2-p1;
        glm::vec3 v = p3-p1;
        glm::vec3 normal =  glm::cross(u,v);
        teaPotNormals.push_back(normal);
        teaPotNormals.push_back(normal);
        teaPotNormals.push_back(normal);
    }

    for (int i =0; i < teaPotNormals.size(); i++)
    {
        all.push_back(teaPotVertices[i]);
        all.push_back(teaPotNormals[i]);
    }
}

