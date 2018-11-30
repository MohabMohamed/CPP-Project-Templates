#include "ShaderLoader.h"

static GLuint compileShader(const GLchar* source, GLenum shaderType)
{
    auto shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);
    GLint isSuccess = 0;
    GLchar infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
    if(!isSuccess)
    {
        glGetShaderInfoLog(shaderID, 512, 1, infoLog);
        exit(1);
    }
    return shaderID;
}

static GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    auto id = glCreateProgram();
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    glLinkProgram(id);
    return id;
}

static char* getFileContents(const char* filePath)
{
    /*
    std::ifstream inFile(filePath);
    if(!inFile.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::stringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
    */
}

GLuint createShaderProgram(
    const char* vertexFile,
    const char* fragmentFile)
{
    auto vertexSource   = getFileContents("shaders/" + std::string(vertexFile)      + ".vert");
    auto fragmentSource = getFileContents("shaders/" + std::string(fragmentFile)    + ".frag");

    auto vertexShaderID     = compileShader(vertexSource.c_str(),   GL_VERTEX_SHADER);
    auto fragmentShaderID   = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return shaderID;
}