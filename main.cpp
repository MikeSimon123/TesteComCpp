#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vss = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 color;
    out vec4 cor;
    void main(){
        gl_Position = vec4(aPos, 1.0);
        cor = vec4(color, 1.0f);
    }
)glsl";

const char* fss = R"glsl(
    #version 330 core
    in vec4 cor;
    out vec4 FragColor;
    void main(){
        FragColor = cor;
    }
)glsl";

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Triângulo", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glClearColor(0.55f, 0.78f, 0.43f, 1.0f);

    float vertices[18] = {
        -0.5f, -0.5f, 0.f, 1.0f, 0.f, 0.f,
        0.5f, -0.5f, 0.f, 0.f, 1.0f, 0.f,
        0.f, 0.5f, 0.f, 0.f, 0.f, 1.0f
    };
    
    unsigned int VBO, VAO, vs, fs, sp;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    sp = glCreateProgram();
    glShaderSource(vs, 1, &vss, NULL);
    glShaderSource(fs, 1, &fss, NULL);
    glCompileShader(vs); glCompileShader(fs);
    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        

        glUseProgram(sp);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}