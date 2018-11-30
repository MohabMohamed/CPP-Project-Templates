#include "Glad/glad.h"
#include "ShaderLoader.h"

#include <SDL2/SDL.h>

static void kill(const char* message) {
    printf(message);
    SDL_Quit();
    exit(1);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        kill("Cannot init sdl");
    }

    SDL_Window* window;
    SDL_GLContext glContext;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    window = SDL_CreateWindow("OpennGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        kill("Cannot create sdl window");
    }

    glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGL()) {
        kill("Cannot load opengl");
    }

    int8_t running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                            running = 0;
                            break;
                        
                        default:
                        break;
                    }
                    break;

                default:
                    break;
            }
        }
        glClearColor ( 1.0, 0.0, 0.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();


/*
    GLfloat points[] = {
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
    };

    GLuint indices[] =  {
        0, 1, 2, 2, 3, 0
    };

    glViewport(0, 0, 1280, 720);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

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
*/
}