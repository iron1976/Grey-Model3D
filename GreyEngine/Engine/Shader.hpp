#pragma once
#include <string>


static unsigned int CompileShader(unsigned int type, const std::string source)
#if !DEBUGCONSOLE noexcept
#endif
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    std::cout << &id;

    glShaderSource(id, 1, &src, nullptr);


    glCompileShader(id);

    int result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == 0)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        LOGBREAK((std::string)"Failed to compile " + (std::string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " " + (std::string)message);

        glDeleteShader(id);
        return 0;
    }
    return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
#if !DEBUGCONSOLE noexcept
#endif
{

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
static unsigned int GetShaderFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
#if !DEBUGCONSOLE noexcept
#endif
{
    std::stringstream vertexShader_RAW;
    std::stringstream fragmentShader_RAW;
    std::string line;
    std::ifstream readVertexS(vertexShaderPath);
    while (std::getline(readVertexS, line))
    {
        vertexShader_RAW << line << "\n";
    }
    readVertexS.close();
    std::ifstream readFragmentS(fragmentShaderPath);
    while (std::getline(readFragmentS, line))
    {
        fragmentShader_RAW << line << "\n";
    }
    readFragmentS.close();
    if (vertexShader_RAW.str().size() == 0)
    {
        __debugbreak();
    }
    else if (fragmentShader_RAW.str().size() == 0)
    {
        __debugbreak();
    }
    return CreateShader(vertexShader_RAW.str(), fragmentShader_RAW.str());
}

class Shader;
template<typename T = Shader>
T* CurrentShader = nullptr;

#pragma region Shaders
#ifdef _DEBUG 
#else
const char* vertexShader =
"#version 330 core""\n"
"\n"
"layout(location = 0) in vec3 position;""\n"
"uniform vec3 objectScale;""\n"
"uniform vec3 objectPosition;""\n"
"\n"
"uniform vec2 Invert;""\n"
"uniform mat4 view;""\n"
"uniform mat4 ortho;""\n"
"\n"
"out vec4 color_data;""\n"
"uniform int UseTex;""\n"
"\n"
"\n"
"uniform vec4 custom_color;""\n"
"out vec2 TexCoords;""\n"
"\n"
"vec2 TexCoordsVer[6] = vec2[6]""\n"
"(""\n"
"    vec2(-0.5f, -0.5f), vec2(-0.5f, 0.5f), vec2(0.5f, 0.5f),""\n"
"    vec2(0.5f, -0.5f), vec2(0.5f, 0.5f), vec2(-0.5f, -0.5f)""\n"
"    );""\n"
"\n"
"\n"
"void main()""\n"
"{""\n"
"    gl_Position = view * ortho * vec4((position + objectPosition) * objectScale, 1.0f);""\n"
"    color_data = custom_color;""\n"
"""\n"
"   if (UseTex == 1)""\n"
"        TexCoords = (TexCoordsVer[gl_VertexID] / (Invert)) + vec2(0.5f, 0.5f);""\n"
"    else""\n"
"        TexCoords = vec2(-166, -1);""\n"
"};";

const char* fragmentShader =
"#version 330 core""\n"

"layout(location = 0) out vec4 color;""\n"
"in vec4 color_data;""\n"
""
"in vec2 TexCoords;""\n"
"uniform sampler2D tex0;""\n"
"uniform vec4 lightColor;""\n"
"""\n"
"void main()""\n"
"{""\n"
"    if (TexCoords.x != -166)""\n"
"       color = texture(tex0, TexCoords)*color_data*lightColor;""\n"
"    else""\n"
"        color = color_data * lightColor;""\n"
"}";

#endif

#pragma endregion
class Shader
{
    unsigned int shader;
public:
	Shader(const std::string vertex, const std::string frag)
	{
#ifdef _DEBUG
        shader = GetShaderFromFile(vertex, frag);
#else
        shader = CreateShader(vertexShader, fragmentShader);
#endif
        CurrentShader<Shader> = this;
        UseShader();
	}
    void UseShader()
#if !DEBUGCONSOLE noexcept
#endif
    {
        glUseProgram(shader);
    }
	operator unsigned int()
#if !DEBUGCONSOLE noexcept
#endif
	{
		return shader;
	}
};