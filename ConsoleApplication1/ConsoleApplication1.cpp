

#include <GL/glew.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <time.h>
#include <stdarg.h>

#include <assert.h>

#include "LogErrors/LogErrors.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <UIComponents/WindEnergyWindow.h>
#include "TerrainGenerator/TerrainGenerator.h"
#include "Textures2/Texture.h"
#include "Shader/Shader.h"
#include <Models/WindGenerator.h>

#include <Models/GrassQuad.h>

#include "Window/MainWindow.h"
#include "Camera/Camera.h"
#include "ModelImporter.h"
#include "TreeModel.h"
#include <Lighting/Material.h>
#include <Lighting/DirectionalLight.h>
#include <Lighting/PointLight.h>


#pragma warning(disable:4996)
void RenderGrassBush(Mesh quad,glm::vec3 position,GLuint location,float slope)
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);

    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    model = glm::rotate(model, glm::radians(slope), glm::vec3(1, 0, 0));

    model = glm::rotate(model, (float)glm::radians(30.0f), glm::vec3(0, 1, 0));

    glUniformMatrix4fv(
       location,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );


    quad.RenderMesh();


    model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    model = glm::rotate(model, glm::radians(slope), glm::vec3(1, 0, 0));

    model = glm::rotate(model, (float)glm::radians(-30.0f), glm::vec3(0, 1, 0));


    glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    quad.RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    model = glm::rotate(model, glm::radians(slope), glm::vec3(1, 0, 0));
    model = glm::rotate(model, (float)glm::radians(-75.0f), glm::vec3(0, 1, 0));


    glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );
    quad.RenderMesh();

}


void RenderGrassField(Mesh quad,GLuint location,glm::vec3 position,float slope)
{
    RenderGrassBush(quad, glm::vec3(position.x, position.y, position.z), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 2, position.y, position.z + 0.5), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 4, position.y, position.z + 1.5), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 6, position.y, position.z + 1.2), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 8, position.y, position.z + 1.2), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 10, position.y, position.z), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x, position.y, position.z + 2.3), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 1.2, position.y, position.z + 3.5), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 4.5, position.y, position.z + 2.6), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 2.7, position.y, position.z + 2.3), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 1.9, position.y, position.z + 2), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 7.9, position.y, position.z + 3.5), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x, position.y, position.z + 4), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 2, position.y, position.z + 4), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 4.9, position.y, position.z + 6.1), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 6, position.y, position.z + 2.1), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 7.5, position.y, position.z + 3.1), location,slope);
    RenderGrassBush(quad, glm::vec3(position.x + 9.2, position.y, position.z + 5.4), location,slope);
}


float getSlope(glm::vec3 v1, glm::vec3 v2)
{
    return glm::angle(v1, v2);
}



int main() {

   /* glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    glEnable(GL_MULTISAMPLE);
    glFrontFace(GL_CCW);

    
    MainWindow window("OpenGL");

    Shader spm1, wind;
    spm1.CreateShaderFromFiles(
        "Shader/shaders/windGenerator.vert",
        "Shader/shaders/windGenerator.frag"
    );

    wind.CreateShaderFromFiles(
        "Shader/shaders/grass.vert",
        "Shader/shaders/grass.frag"
    );


    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CW);

    WindEnergyWindow wew;
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    std::string basePath = "Textures/textures/";

    ModelImporter mi(basePath);

    TreeModel* mo = mi.LoadModel("Models/models/bushes/bush-01.fbx");
    
    glm::mat4 projection(1.0f);

    projection = glm::perspective(
        glm::radians(45.0f),
        (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(),
        0.1f,
        100.0f);

    float degs = 0;

    GLfloat last_time = 0;
    GLfloat delta_time = 0;
    GLfloat now = 0;
    glfwSwapInterval(1);

    TerrainGenerator* gen = new TerrainGenerator(16,2.5f);
    Texture metalTex("Textures/textures/metal3.jpg");
    metalTex.LoadTexture();


    const unsigned int numberOfGenerators = 4;
    WindGenerator winGenerator(
        spm1, {},
        glm::vec3(0.0f, 0.0f, 0.0f),
        7.0f, 0.15f,
        0.2f, 0.5f, 3.0f,
        wew.GetWindSpeedData()
    );

    Mesh* terrain = gen->GetTerrainMesh();
    Texture grass("Textures/textures/grass.png");
    Texture grass3("Textures/textures/grass3.png");

    grass3.LoadTexture();
    grass.LoadTexture();

    Material shinyMaterial = Material(4.0f, 256.0f);
    Material dullMaterial = Material(0.3f, 4.0f);

    DirectionalLight mainLight = DirectionalLight(
        0.86f, 0.86f, 0.86f,
        1.0f, 1.0f,
        glm::vec3(2.0f, -1.0f, -2.0f)
    );

    PointLight pointLight = PointLight(
        0.86f, 0.86f, 0.86f,
        0.8f, 0.9f,
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.3f, 0.2f, 0.1f
    );

    GrassQuad q(glm::vec3(0.0f,0.0f,0.0f),5,5);

    Mesh grassMesh(q.GetVertices(), q.GetVerticesNum(), q.GetIndices(), q.GetIndicesNum());


    int i = 10;
    auto& uniLoc = spm1.GetUniformLocations();
    auto& windLoc = wind.GetUniformLocations();

    winGenerator.SetUniformLocations(uniLoc);
    
    float time = 0;
    float step = 0.05;
    mo->SetShader(wind);

    while (!window.getShouldClose())
    {
        now = glfwGetTime();
        delta_time = now - last_time;
        last_time = now;

        glfwPollEvents();
        camera.move(delta_time);
        camera.turn(window.getXChange(),window.getYChange());

        degs++;
        if (degs >= 360)
            degs = 0;

        glm::mat4 model(1.0f);


        glm::mat4 view = camera.calculateViewMatrix();

        wind.UseShader();

        glUniform1f(glGetUniformLocation(wind.getID(), "intensity"), wew.getWindSpeed()/10);
        glUniform1f(glGetUniformLocation(wind.getID(), "random"), rand()/RAND_MAX);
        glUniform1f(glGetUniformLocation(wind.getID(), "time"), now);

        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 camPos = camera.GetCameraPosition();

        glUniform3f(windLoc.EyePositionLocation, camPos.x, camPos.y, camPos.z);
        
        mainLight.UseLight(
            windLoc.UDirLightLocs.ULightLocations.AmbientIntesityLocation,
            windLoc.UDirLightLocs.ULightLocations.ColorLocation,
            windLoc.UDirLightLocs.ULightLocations.DiffuseIntesityLocation,
            windLoc.UDirLightLocs.DirectionLocation
        );

        pointLight.UseLight(
            windLoc.UPointLightLocs.ULightLocations.AmbientIntesityLocation,
            windLoc.UPointLightLocs.ULightLocations.ColorLocation,
            windLoc.UPointLightLocs.ULightLocations.DiffuseIntesityLocation,
            windLoc.UPointLightLocs.PositionLocation,
            windLoc.UPointLightLocs.ConstantLocation,
            windLoc.UPointLightLocs.LinearLocation,
            windLoc.UPointLightLocs.ExponentLocation
        );
        
        grass3.UseTexture();

        dullMaterial.UseMaterial(
            windLoc.UMaterialLocations.SpecularIntesityLocation,
            windLoc.UMaterialLocations.ShininessLocation
        );

        glUniformMatrix4fv(
            windLoc.ProjectionMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            windLoc.ViewMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );
        

        RenderGrassField(grassMesh, windLoc.ModelMatrixLocation,glm::vec3(2.0, 2.5, 2.0),0);
        RenderGrassField(grassMesh, windLoc.ModelMatrixLocation, glm::vec3(25, 2, 30),0);
        RenderGrassField(grassMesh, windLoc.ModelMatrixLocation, glm::vec3(25, 6, 12),0);


        RenderGrassBush(grassMesh, glm::vec3(2.0, 2.6, 12.0), windLoc.ModelMatrixLocation, -29);
        RenderGrassBush(grassMesh, glm::vec3(4.0, 3.1, 13.0), windLoc.ModelMatrixLocation, -28);










        model = glm::mat4(1.0f);
        glUniformMatrix4fv(
            uniLoc.ModelMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        mo->Render(glm::vec3(5.0f, 5, 6.0));
        mo->Render(glm::vec3(16.0f, 9, 16.0));

   
        spm1.UseShader();

        glUniformMatrix4fv(
            uniLoc.ProjectionMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            uniLoc.ViewMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );



        grass.UseTexture();

        mainLight.UseLight(
            uniLoc.UDirLightLocs.ULightLocations.AmbientIntesityLocation,
            uniLoc.UDirLightLocs.ULightLocations.ColorLocation,
            uniLoc.UDirLightLocs.ULightLocations.DiffuseIntesityLocation,
            uniLoc.UDirLightLocs.DirectionLocation
        );

        pointLight.UseLight(
            uniLoc.UPointLightLocs.ULightLocations.AmbientIntesityLocation,
            uniLoc.UPointLightLocs.ULightLocations.ColorLocation,
            uniLoc.UPointLightLocs.ULightLocations.DiffuseIntesityLocation,
            uniLoc.UPointLightLocs.PositionLocation,
            uniLoc.UPointLightLocs.ConstantLocation,
            uniLoc.UPointLightLocs.LinearLocation,
            uniLoc.UPointLightLocs.ExponentLocation
        );

        model = glm::mat4(1.0f);
        glUniformMatrix4fv(
            uniLoc.ModelMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        terrain->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(5.0f, 25.0f, 12.0f));
        glUniformMatrix4fv(
            uniLoc.ModelMatrixLocation,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );
        metalTex.UseTexture();
        winGenerator.setDelta(delta_time * 100);
        winGenerator.SetBladePercentageInc(wew.GetBladePercentageIncrease());
        winGenerator.Render(glm::vec3(3.0f,12.0f,4.0f));
        winGenerator.Render(glm::vec3(20.0f,13.0f, 6.0f));
        winGenerator.Render(glm::vec3(28.0f, 13.0f, 28.0f));
        winGenerator.Render(glm::vec3(16.0f, 16.0f, 16.0f));



        //winGenerator.SetViewMatrix(view);
        // faktor skaliranja vremena u odnosu na stvarni svet


   
        // blend away grass with no alpha
        /*glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        
        // speed updated
        wew.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete gen;
    delete terrain;
    // close GL context and any other GLFW resources
    // should be picked up in the MainWindow::~MainWindow();
    //glfwTerminate();

    return 0;
}

