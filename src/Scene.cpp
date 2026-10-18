#include "Scene.h"
#include "models/ObjModel.h"

void Scene::mouseCallback(GLFWwindow *window, int button,int action,int mods)
{
    Scene* instance = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    mods = 0;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double currX,currY = mods;
        glfwGetCursorPos(window,&currX,&currY);
        instance->m_last = glm::vec2((float)currX,(float)currY);
        instance->m_cameraMovement = true;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        instance->m_cameraMovement = false;
    }
}

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    glfwSetWindowUserPointer(m_window->getWindow(), this);
    glfwSetMouseButtonCallback(m_window->getWindow(),Scene::mouseCallback);
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("../shader/vertex_shader.glsl", "../shader/frag_shader.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);

    //Se inicializan todos los modelos a usar
    // En lugar de "cubo" se instancia el objeto model (cambie lo que estaba por defecto)
    Model* bunny = new ObjModel(m_shaderPrograms[0],"../assets/bunny.obj");
    m_models.push_back(bunny);

    Model* car = new ObjModel(m_shaderPrograms[0],"../assets/car.obj");
    m_models.push_back(car);

    //Matriz de vista View Matrix
    //Posicion de la camara, centro de atencion, vector perpendicular de la Cámara
    m_camera = new OrbitCamera(glm::vec3(7.0f,4.0f,7.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
    m_view =  m_camera->getMatrix();
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    size_t modeloActual = 0;
    bool teclaPresionada = false; //Evitamos que cambie muy rapido si se deja presionado

    //Ciclo de Renderizado
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario


    m_cameraMovement = false;
    while(!glfwWindowShouldClose(m_window->getWindow())){
        // Compute time  
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            delete m_camera;
            m_camera = new OrbitCamera(glm::vec3(7.0f,4.0f,7.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
        }
        //Agregamos poder cambiar de modelo con las flechas del teclado
        if(glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if(!teclaPresionada) {
                modeloActual++;
                // Volver al primer modelo
                if(modeloActual >= m_models.size()) modeloActual = 0;
                teclaPresionada = true; 
            }
        }
        else if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (!teclaPresionada) {
                if(modeloActual == 0) {
                    modeloActual = m_models.size() - 1; // Ir al último
                } else {
                    modeloActual--;
                }
                teclaPresionada = true;
            }
        } 
        else {
            //Podemos presionar otra vez
            teclaPresionada = false;
        }

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Solo renderizamos el modelo actual
        m_models[modeloActual]->renderModel(m_view, m_projection);
        m_models[modeloActual]->updateModel(0.7f);
        
        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        m_models[modeloActual]->updateModel(0.7f);

        if (m_cameraMovement)
        {
            double currX,currY = 0;
            glfwGetCursorPos(m_window->getWindow(),&currX,&currY);
            m_current = glm::vec2((float)currX,(float)currY);
            m_camera->rotate(m_last,m_current);
            m_camera->setPos(m_last,m_current);

        }
        m_view = m_camera->getMatrix();
    }

}