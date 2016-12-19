#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <armadillo>

using namespace arma;
using namespace std;

struct screen
{
    GLuint i_vbo;
    GLuint x_vbo;
    GLuint t_vbo;
    screen()
    {
        vector<glm::vec3> screen_x =
        {
            glm::vec3(-1., 1., 0.),
            glm::vec3(-1.,-1., 0.),
            glm::vec3( 1.,-1., 0.),
            glm::vec3( 1., 1., 0.)
        };

        vector<glm::vec2> screen_t =
        {
            glm::vec2( 0., 1.),
            glm::vec2( 0., 0.),
            glm::vec2( 1., 0.),
            glm::vec2( 1., 1.)
        };

        vector<int> screen_i = { 0 , 1 , 2 , 0 , 2 , 3 };

        glGenBuffers(1,&x_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,x_vbo);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*screen_x.size(),&screen_x[0],GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

        glGenBuffers(1,&t_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,t_vbo);
        glEnableVertexAttribArray(1);
        glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*screen_t.size(),&screen_t[0],GL_STATIC_DRAW);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

        glGenBuffers(1,&i_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,i_vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*screen_i.size(),&screen_i[0],GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
    ~screen()
    {
        glDeleteBuffers(1,&i_vbo);
        glDeleteBuffers(1,&x_vbo);
        glDeleteBuffers(1,&t_vbo);
    }
    void draw()
    {
        glBindBuffer(GL_ARRAY_BUFFER,x_vbo);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,t_vbo);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,i_vbo);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
};

struct mesh
{
    GLuint i_vbo;
    GLuint x_vbo;
    GLuint size_;
    mesh(fmat & V,fmat & G)
    {
        vector<glm::vec3> graph_x;
        vector<int>       graph_l;
        for(int i=0;i<V.n_rows;i++)
        {
            graph_x.push_back(glm::vec3(V(i,0),V(i,1),V(i,2)));
            for(int j=i+1;j<V.n_rows;j++)
                if(G(i,j)>0.0)
                {
                    graph_l.push_back(i);
                    graph_l.push_back(j);
                }
        }

        glGenBuffers(1,&x_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,x_vbo);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*graph_x.size(),&graph_x[0],GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

        glGenBuffers(1,&i_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,i_vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*graph_l.size(),&graph_l[0],GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glDisableVertexAttribArray(0);
        size_ = graph_l.size();
    }
    void draw()
    {
        glBindBuffer(GL_ARRAY_BUFFER,x_vbo);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,i_vbo);
        glDrawElements(GL_LINES,size_,GL_UNSIGNED_INT,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glDisableVertexAttribArray(0);
    }
    ~mesh()
    {
        glDeleteBuffers(1,&i_vbo);
        glDeleteBuffers(1,&x_vbo);
    }
};

#endif // MESH_HPP_INCLUDED
