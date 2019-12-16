#include <glimac/Cube.hpp>

namespace glimac {

    Cube::Cube() : m_vao(0), m_ibo(0), m_vbo(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {
    }

    Cube::Cube(glm::vec3 position, glm::vec3 color) : m_vao(0), m_ibo(0), m_vbo(0), m_position(position), m_color(color) {
        initBuffer();
    }

    Cube::~Cube() {
        initBuffer();
    }

    void Cube::initBuffer() {

        Vertex3DColor vertices[] = {
            Vertex3DColor(glm::vec3(0.5, -0.5, 0.5), m_color), //0
            Vertex3DColor(glm::vec3(-0.5, -0.5, 0.5), m_color), //1
            Vertex3DColor(glm::vec3(-0.5, 0.5, 0.5), m_color), //2
            Vertex3DColor(glm::vec3(0.5, 0.5, 0.5), m_color), //3
            Vertex3DColor(glm::vec3(0.5, -0.5, -0.5), m_color), //4
            Vertex3DColor(glm::vec3(-0.5, -0.5, -0.5), m_color), //5
            Vertex3DColor(glm::vec3(-0.5, 0.5, -0.5), m_color), //6
            Vertex3DColor(glm::vec3(0.5, 0.5, -0.5), m_color) //7
        };

        uint32_t indexes[36] = {
                    0, 1, 3, 1, 3, 2, //top
                    4, 5, 7, 5, 7, 6, //bottom
                    0, 3, 4, 3, 4, 7, //left
                    1, 2, 5, 2, 5, 6, //right
                    3, 2, 7, 2, 7, 6, //front
                    0, 1, 4, 1, 4, 5 //back
        };
        //Vertex buffer
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);    
        glBufferData(GL_ARRAY_BUFFER,
                sizeof(Vertex3DColor), vertices,
                GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Index bufferm_max_cubes_in_column
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t), indexes, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //Vertex array
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_color));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Cube::create_uniform_matrices(Program &program)
    {
        uMVPLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
        uMVLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
        uNormalLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    }

    void Cube::draw() {
        glm::mat4 camera_VM = camera.getViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 900.0f/900.0f, 0.1f, 100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        
        glBindVertexArray(m_vao);

        glUniformMatrix4fv(uMVPLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
        glUniformMatrix4fv(uMVLocation, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
        glUniformMatrix4fv(uNormalLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //unbind vao
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}