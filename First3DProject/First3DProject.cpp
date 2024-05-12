#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Window.h"
#include "TeaPotOBJ.h"
#include "Pumpkin.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include<sstream>
#include <vector>



Window* window = new Window();

glm::vec3 worldFront = glm::vec3(0.0f,0.0f,1.0f);
glm::vec3 worldUp = glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 worldRight = glm::vec3(1.0f,0.0f,0.0f);

glm::vec3 cameraPos = glm::vec3(0.0f,0.0f, -3.0f);
glm::vec3 cameraFront = worldFront;
glm::vec3 cameraUp = worldUp;
glm::vec3 cameraRight = worldRight;


//cube* Cube = new class cube();

float deltaTime;


double camerax;
double cameray;

float pitch;
float yarn;

void ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
    //float cameraspeedByDeltaTime = cameraSpeed * cameraspeedByDeltaTime;
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp)) * deltaTime;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp)) * deltaTime;
    }
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraFront * deltaTime;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraFront * deltaTime;
    }
}

void GetCameraOffSet()
{
    double offsetx = camerax;
    double offsety = cameray;
    glfwGetCursorPos(window->window, &camerax,&cameray);
    yarn -= camerax - offsetx;
    pitch -= cameray - offsety;
    //std::cout << "pitch : " <<pitch << " yaw : " << yarn << std::endl;
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


int main(int argc, char* argv[])
{

    TeaPotOBJ* teaPotOBJ = new TeaPotOBJ();

    Pumpkin* pumpkin = new Pumpkin();
    
    float lastTime = glfwGetTime();
    
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    window->CreateWindow();

    glfwMakeContextCurrent(window->window);

    glfwSetFramebufferSizeCallback(window->window, Window::framebufferSizeCallback);
    glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    //glfwSetCursorPosCallback(window->window, mouseMoveCallback);
    //glfwSetScrollCallback(window->window, mouseScrollCallback);
    
    
    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    Shader* shader = new Shader("vertex.shader","fragment.shader");
    

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
   };

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.4f,  0.4f,  1.0f),
        glm::vec3( 2.0f, -2.0f, -1.0f),
        glm::vec3(-2.0f,  2.0f, -2.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f)
    };
    
    unsigned int diffuseMap = loadTexture("container2.png");

    unsigned int VBO,VAO,VTBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VTBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, teaPotOBJ->all.size() * sizeof(glm::vec3), teaPotOBJ->all.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,sizeof(glm::vec3)*2,(void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//////////////////////////////////
    
    unsigned int PBO,PAO,VPBO;
    glGenVertexArrays(1, &PAO);
    glGenBuffers(1, &VPBO);
    glGenBuffers(1, &PBO);

    glBindVertexArray(PAO);

    glBindBuffer(GL_ARRAY_BUFFER, PBO);
    glBufferData(GL_ARRAY_BUFFER, pumpkin->all.size() * sizeof(glm::vec3), pumpkin->all.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,sizeof(glm::vec3)*2,(void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //////////////////////////////////

    unsigned int VBOlight, VAOlight;
    glGenVertexArrays(1, &VAOlight);
    glGenBuffers(1, &VBOlight);

    glBindVertexArray(VAOlight);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shaderlight("vertexlight.shader", "fragmentlight.shader");

    //glm::vec3 lightPosition(1,1,-1);
    
    while (!glfwWindowShouldClose(window->window))
    {
        
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window->window, true);
        }

        ProcessInput(window->window);

        GetCameraOffSet();

        glm::mat4 transform = glm::mat4(1);
        transform = glm::rotate(transform,glm::radians(yarn),worldUp);

        cameraFront = transform * glm::vec4(worldFront,1.0f);
        
        cameraRight = glm::normalize(glm::cross(cameraFront,worldUp));

        transform = glm::mat4(1);

        transform = glm::rotate(transform,glm::radians(pitch),cameraRight); //

        cameraFront = transform * glm::vec4(cameraFront,1.0f);
        
        glClearColor(0.2f,0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);   
        
        shader->Use();

        shader->SetVector3("lightColor", 1.0f,1.0f,1.0f);
        shader->SetVector3("objectColor", 1.0f,1.0f,1.0f);
        shader->SetFloat("ambientStrenght",1.0f);
        //shader->SetVector3("lightPos", lightPosition);
        shader->SetVector3("viewPos", cameraPos);
        //shader->SetVector3("material.ambient", 1.0f, 0.5f, 0.31f);
        shader->SetInt("material.diffuse", 0);
        shader->SetVector3("material.specular", 0.5f, 0.5f, 0.5f);
        shader->SetFloat("material.shininess", 32.0f);
        shader->SetFloat("light.constant",  1.0f);
        shader->SetFloat("light.linear",    0.09f);
        shader->SetFloat("light.quadratic", 0.032f);

        shader->SetVector3("pointLights[0].position", pointLightPositions[0]);
        shader->SetVector3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader->SetVector3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shader->SetVector3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader->SetFloat("pointLights[0].constant", 1.0f);
        shader->SetFloat("pointLights[0].linear", 0.09f);
        shader->SetFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        shader->SetVector3("pointLights[1].position", pointLightPositions[1]);
        shader->SetVector3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        shader->SetVector3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shader->SetVector3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        shader->SetFloat("pointLights[1].constant", 1.0f);
        shader->SetFloat("pointLights[1].linear", 0.09f);
        shader->SetFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        shader->SetVector3("pointLights[2].position", pointLightPositions[2]);
        shader->SetVector3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        shader->SetVector3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shader->SetVector3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        shader->SetFloat("pointLights[2].constant", 1.0f);
        shader->SetFloat("pointLights[2].linear", 0.09f);
        shader->SetFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        shader->SetVector3("pointLights[3].position", pointLightPositions[3]);
        shader->SetVector3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader->SetVector3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader->SetVector3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shader->SetFloat("pointLights[3].constant", 1.0f);
        shader->SetFloat("pointLights[3].linear", 0.09f);
        shader->SetFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)window->Width_screen / (float)window->Height_screen, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader->SetMatrix4("projection",projection);
        
        shader->SetMatrix4("view",view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
        model = glm::rotate(model,glm::radians(0.f),glm::vec3(0.0f,1.0f,0.0f));
        shader->SetMatrix4("model",model);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,teaPotOBJ->all.size()/2);
        glBindVertexArray(0);

        glBindVertexArray(PAO);
        glDrawArrays(GL_TRIANGLES, 0,pumpkin->all.size()/2);
        glBindVertexArray(0);
        //glDrawElements(GL_TRIANGLES, teaPotOBJ->fTeaPot.size(), GL_UNSIGNED_INT, NULL);
        //glDrawElements(GL_TRIANGLES, Cube->fCube.size(), GL_UNSIGNED_INT, NULL);
        
        

        shaderlight.Use();
        
        shaderlight.SetMatrix4("projection", projection);
        shaderlight.SetMatrix4("view", view);
        
        shaderlight.SetMatrix4("model",model);
        
        glBindVertexArray(VAOlight);

        for (unsigned int i = 0; i < pointLightPositions->length() ; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); 
            shaderlight.SetMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1, &PAO);
    glDeleteBuffers(1,&PBO);
    glDeleteProgram(shader->ID);
    glDeleteVertexArrays(1, &VAOlight);
    glDeleteBuffers(1,&VBOlight);
    glDeleteProgram(shaderlight.ID);

    
    
    glfwTerminate();
    return 0;
}

