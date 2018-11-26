#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Glad/glad.h"
#include "ShaderLoader.h"

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::Window window(sf::VideoMode(1280, 720), "OpenGL", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL functions, exiting\n";
        return -1;
    }

    std::vector<GLfloat> points {
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
    };

    std::vector<GLuint> indices {
        0, 1, 2, 2, 3, 0
    };

    glViewport(0, 0, 1280, 720);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    auto shader = createShaderProgram("Static", "Static");

    glBindVertexArray(vao);
    glUseProgram(shader);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        window.display();
    }
}