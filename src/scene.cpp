//Basé sur learnopengl


#include <stb_image.h>
#include <scene.h>



const glm::vec3 positions[] = {
        glm::vec3(2.0f, 1.0f, -2.0f),//bezier1
        glm::vec3(0.0f,  0.0f, -2.0f),//bezier2
        glm::vec3(-1.0f,  0.0f, 0.0f),//...
        glm::vec3(1.0f,  0.0f, 0.0f),
        glm::vec3(1.0f,  -1.0f, -1.0f),
        glm::vec3(-1.0f,  -1.0f, -1.0f),
        glm::vec3(.0f,  .0f, 4.0f),//floor1
        glm::vec3(.0f,  .0f, 6.0f),//floor2
        glm::vec3(-6.0f,  .0f, 0.0f),//floor3
        glm::vec3(.0f,  5.0f, 0.0f),//cylindre
};

const glm::vec3 cameraInitPos = glm::vec3(3.0f, 2.0f, -7.0f);

const float initYAW         = 120.0f;
const float initPITCH       =  -10.0f;



void Scene::renderScene(const Shader *shader, int beginObjectNumber, int endObjectNumber){
    glm::mat4 model;
    for(int i = beginObjectNumber; i < endObjectNumber; i++){
        if(i == 0)
            shader->setVec3("objectColor", 1.0f, 0.0f, 1.0f);
        else if(i >= 1)
            shader->setVec3("objectColor", 0.0f, 1.0f, 0.0f);
        
            
        model = glm::mat4(1.0f);
        model *= glm::translate(glm::mat4(1.0f), positions[i]);
        if(i == 8)
            model = glm::rotate(model, glm::pi<float>()/2.f, glm::vec3(0,1,0));
        shader->setMat4("model", model);
        if(i < 6)
            surface->afficher(); 
        else if(i >= 6 && i < 9){
            glBindVertexArray(floorVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
        else
            cylindre->afficher();
    }

}




Scene::Scene(std::string pathCubemap, std::string pathTexture, Camera *camera) {
    lightPos = glm::vec3(0.0f, 3.0f, -6.0f);
    cubemap = new Cubemap(pathCubemap);
    makeObject();
    makeFloor();
    makeShader(pathTexture);
    this->camera = camera;
    camera->Position = cameraInitPos;
    camera->Yaw = initYAW;
    camera->Pitch = initPITCH;
    cylindre = new Cylindre(10, 10);
    bone1 = new Bone(glm::vec3(0.,-3.,0.), glm::vec3(0.,0.,0.), 0);
    bone1->attacherCylindre(cylindre);
    bone2 = new Bone(glm::vec3(0.,3.,0.), glm::vec3(0.,0.,0.), 1);
    bone2->attacherCylindre(cylindre);   
    bone1->normaliserPoids(); 
    bone2->mettreParent(bone1);
    bone1->mettreEnfant(bone2);



}

void Scene::makeFloor(){
    float floorVertices[] = {   
        -1.0f,  1.0f, 0.0f, 
        -1.0f, -1.0f, 0.0f, 
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,  
         1.0f, -1.0f, 0.0f,  
         1.0f,  1.0f, 0.0f   
    };

    for(int i = 0; i < 6*3; i++)
        floorVertices[i] *= 6;

    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    glBindVertexArray(floorVAO);

    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void Scene::makeObject(){
    std::vector<glm::vec3> pointsControles = {
        glm::vec3(-0.25f, 0.0f, 0.0f),
        glm::vec3(-0.25f, 0.5f, 0.0f),
        glm::vec3(0.25f, -0.5f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f)
    };
    CourbeBezier curve(pointsControles, 0.001f);
    curve.charger(VBO, VAO);
    

    std::vector<std::vector<glm::vec3>> ctrlpoints = {
      {
        glm::vec3(-0.25f, 0.0f, 0.0f),
        glm::vec3(-0.25f, 0.5f, 0.0f),
        glm::vec3(0.25f, -0.5f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f)},
      {
        glm::vec3(-0.25f, 0.25f, 0.2f),
        glm::vec3(-0.25f, 0.75f, 0.2f),
        glm::vec3(0.25f, -0.25f, 0.2f),
        glm::vec3(0.5f, 0.25f, 0.2f)},
      {
        glm::vec3(-0.25f, 0.25f, 0.4f),
        glm::vec3(-0.25f, 0.75f, 0.4f),
        glm::vec3(0.25f, -0.25f, 0.4f),
        glm::vec3(0.5f, 0.25f, 0.4f)},
      {
        glm::vec3(-0.25f, 0.0f, 0.6f),
        glm::vec3(-0.25f, 0.5f, 0.6f),
        glm::vec3(0.25f, -0.5f, 0.6f),
        glm::vec3(0.5f, 0.0f, 0.6f)}
    };

    surface = new SurfaceBezier(ctrlpoints, 0.01f, 0.01f);
    surface->charger(VBO_surface, VAO_surface, EBO);
}

void Scene::makeShader(std::string pathTexture){
    shader_ig3 = new Shader("shader/ig3.vs", "shader/ig3.fs");
    shader_cubemap = new Shader("shader/cubemap.vs", "shader/cubemap.fs");
    simpleDepthShader = new Shader("shader/shadow_mapping.vs", "shader/shadow_mapping.fs");
    boneShader = new Shader("shader/bone.vs", "shader/bone.fs");
    shaderScene = new Shader("shader/scene.vs", "shader/scene.fs");
    

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int tex_width, tex_height, nrChannels;
    unsigned char *tex_data = stbi_load(pathTexture.c_str(), &tex_width, &tex_height, &nrChannels, 0);
    if (tex_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(tex_data);


    configureDepthMap();


    shader_ig3->use();
    shader_ig3->setInt("shadowMap", 1);
}

void Scene::configureDepthMap(){
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}




void Scene::renderCubemap(){
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glDepthFunc(GL_LEQUAL);
    shader_cubemap->use();
    shader_cubemap->setMat4("projection", projection);
    
    view = glm::mat4(glm::mat3(camera->GetViewMatrix()));  
    shader_cubemap->setMat4("view", view);
    cubemap->draw();
    glDepthFunc(GL_LESS);
}


void Scene::renderDepthMap(){
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 20.f;
    lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, positions[6], glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    simpleDepthShader->use();
    simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderScene(simpleDepthShader, 0, 9);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Scene::renderObjectScene(int rotationInDegree){
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 20.f;
    lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, positions[6], glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    shader_ig3->use();
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader_ig3->setMat4("projection", projection);
    shader_ig3->setMat4("view", view);

    shader_ig3->setVec3("viewPos", camera->Position);
    shader_ig3->setVec3("lightPos", lightPos);
    shader_ig3->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    shader_ig3->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader_ig3->setVec3("objectColor", 0.0f, 1.0f, 0.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    renderScene(shader_ig3, 0, 6);


    shaderScene->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    shaderScene->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    shaderScene->setMat4("projection", projection);
    shaderScene->setMat4("view", view);
    renderScene(shaderScene, 6, 9);
 

    boneShader->use();

    boneShader->setMat4("projection", projection);
    boneShader->setMat4("view", view);    
    boneShader->setVec3("viewPos", camera->Position);
    boneShader->setVec3("objectColor", 0.0f, 1.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(glm::mat4(1.0f), positions[9]);
    boneShader->setMat4("model", model);
    matRotation = bone2->matRotation(rotationInDegree, glm::vec3(0,0,1));
    boneShader->setMat4("matRotation", matRotation);
    cylindre->afficher();
    boneShader->setMat4("matRotation", glm::mat4(1.0));
    //bone1->afficher();
    boneShader->setMat4("matRotation", glm::mat4(1.0));
    //bone2->afficher();
}





void Scene::free(){
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);    
    glDeleteVertexArrays(2, VAO_surface);
    glDeleteBuffers(2, VBO_surface); 
    glDeleteBuffers(2, EBO);
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteBuffers(1, &floorVBO);
    cubemap->free();
    cylindre->free();
    bone1->free();
    bone2->free();    
    delete cubemap;
    delete surface;
    delete shader_ig3;
    delete shader_cubemap;
    delete simpleDepthShader;
    delete cylindre;
    delete bone1;
    delete bone2;
    delete boneShader;
    delete shaderScene;
}

