#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Glad/glad.h"
#include "ShaderLoader.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct {
    glm::vec3 pos{0.0, 0.0, 1.0f}, rot;
} player;

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::Window window(sf::VideoMode(1280, 720), "OpenGL", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL functions, exiting\n";
        return -1;
    }

    std::vector<GLfloat> points {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f, 
        -0.5f,  0.5f, 0.0f,  
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    auto shader = createShaderProgram("Static", "Static");

    glBindVertexArray(vao);
    glUseProgram(shader);

    glm::mat4 viewMatrix            {1.0f};
    glm::mat4 modelMatrix           {1.0f};
    glm::mat4 projectionMatrix      {1.0f};
    glm::mat4 projectionViewMatrix  {1.0f};

    projectionMatrix     = glm::perspective(3.14f /2.0f, 1280.0f/ 720.0f, 0.01f, 100.0f);
    modelMatrix          = glm::rotate(modelMatrix, 3.14f / 4.0f, {1.0, 0.0, 0.0});
    viewMatrix           = glm::translate(viewMatrix, {0.0f, 0.0f, -1.0f});
    projectionViewMatrix = projectionMatrix * viewMatrix;

    auto pvLocation = glGetUniformLocation(shader, "projectionViewMatrix");
    auto modelLocation = glGetUniformLocation(shader, "modelMatrix");

    Keyboard keyboard;
    sf::Mouse::setPosition({window.getSize().x / 2, window.getSize().y / 2}, window);
    sf::Vector2i oldPosition = sf::Mouse::getPosition(window);
    while (window.isOpen()) {
        sf::Event e;
        
        while (window.pollEvent(e)) {
            keyboard.update(e);
            switch(e.type) {
                case sf::Event::KeyPressed:
                    switch (e.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break; 
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                default:
                    break;
            }
        }
        static auto lastMousePosition = sf::Mouse::getPosition(window);
        auto change = sf::Mouse::getPosition(window) - lastMousePosition;
        player.rot.x += change.y / 10.0;
        player.rot.y += change.x / 10.0;
        sf::Mouse::setPosition({window.getSize().x / 2, window.getSize().y / 2}, window);
        lastMousePosition = sf::Mouse::getPosition(window);
        player.rot.x = glm::clamp(player.rot.x, -170.0f, 170.0f);
        
        //Input
        const float SPEED = 0.05f;
        if (keyboard.isKeyDown(sf::Keyboard::W)) {
            player.pos.x += -glm::cos(glm::radians(player.rot.y + 90)) * SPEED;
            player.pos.z += -glm::sin(glm::radians(player.rot.y + 90)) * SPEED;
        }
        else if (keyboard.isKeyDown(sf::Keyboard::S)) {
            player.pos.x += glm::cos(glm::radians(player.rot.y + 90)) * SPEED;
            player.pos.z += glm::sin(glm::radians(player.rot.y + 90)) * SPEED;
        } 
        if (keyboard.isKeyDown(sf::Keyboard::A)) {
            player.pos.x += -glm::cos(glm::radians(player.rot.y)) * SPEED;
            player.pos.z += -glm::sin(glm::radians(player.rot.y)) * SPEED;
        }
        else if (keyboard.isKeyDown(sf::Keyboard::D)) {
            player.pos.x += glm::cos(glm::radians(player.rot.y)) * SPEED;
            player.pos.z += glm::sin(glm::radians(player.rot.y)) * SPEED;
        } 

        //Update
        glm::mat4 viewMatrix {1.0f};
        viewMatrix = glm::rotate(viewMatrix, glm::radians(player.rot.x), {1, 0, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(player.rot.y), {0, 1, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(player.rot.z), {0, 0, 1});
        viewMatrix = glm::translate(viewMatrix, -player.pos);
        projectionViewMatrix = projectionMatrix * viewMatrix;
        glUniformMatrix4fv(pvLocation, 1, GL_FALSE, glm::value_ptr(projectionViewMatrix));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        //Render
        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        window.display();
    }
}