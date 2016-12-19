#include <GL/glew.h>
#include <GL/gl.h>

#include "shader.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "koren.hpp"

#include <cmath>
#include <armadillo>

using namespace arma;
using namespace std;

GLFWwindow * window = nullptr;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int win_x = 640;
int win_y = 640;

int init_gl_window()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(win_x,win_y,"Graph Drawing",nullptr,nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    return 0;
}


int main(int argc,char ** argv)
{
    srand(time(nullptr));
    if(init_gl_window()<0) return -1;

    shader  show_;
    show_.load_file(GL_VERTEX_SHADER,"vert.glsl");
    show_.load_file(GL_FRAGMENT_SHADER,"frag.glsl");
    show_.create();

    fmat A; A.load(argv[1]);
    cout << A.n_rows << " " << A.n_cols << endl;

    fmat V = get_spectral(A,3);
    cout << V.n_rows << " " << V.n_cols << endl;
    V -= V.min();
    V /= V.max()/1.5;
    V -= 0.75;

    mesh graph(V,A);

    float t = 0.;
    glm::mat4 P = glm::ortho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &win_x, &win_y);
        glViewport(0, 0, win_x, win_y);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0,0.0,0.0,1.0);

        show_.begin();
        glm::mat4 PM = P * glm::rotate(t,glm::vec3(0.1,1.0,0.1));
        glUniformMatrix4fv(show_("PM"),1,GL_FALSE,glm::value_ptr(PM));
        graph.draw();
        show_.end();
        t += 1.0/60.0;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
