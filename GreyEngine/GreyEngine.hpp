#pragma once
#pragma comment(lib, "GreyEngine/Dependencies/OpenGL/GLEW/glew32s.lib")
#pragma comment(lib, "GreyEngine/Dependencies/OpenGL/GLFW/glfw3.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#define INIT int main(void)
#define STB_IMAGE_IMPLEMENTATION
#include "GreyEngine/Dependencies/stb_image/stb_image.h"
#pragma region including C++ stuff
    #include <iostream>
    #include <windows.h>
    #include <strsafe.h>
    #include <Commdlg.h>
    #include <fstream>
    #include <string>
    #include <sstream>
    #include <vector>
    #include <math.h>
    #include <algorithm>
    #include <bitset>
    #include <map>
    #include <functional>
    #include <any>
    #include <tchar.h>
    #include <filesystem>
    #include <sstream>
    #include <fstream>
#pragma endregion
#pragma region including glm functions
    #include "GreyEngine/Dependencies/glm/glm.hpp"
    #include "GreyEngine/Dependencies/glm/gtc/matrix_transform.hpp"
    #include "GreyEngine/Dependencies/glm/gtc/type_ptr.hpp"
    #include "GreyEngine/Dependencies/glm/mat4x4.hpp"
    #include "GreyEngine/Dependencies/glm/gtx/string_cast.hpp"// this is for glm::to_string()
    using namespace glm;
#pragma endregion
#pragma region including OpenGL
    #define GLEW_STATIC
    #include "GLEW/glew.h"
    #include "GLFW/glfw3.h"
#pragma endregion
//I don't own this; I have taken this from https://github.com/Bly7/OBJ-Loader
#include "GreyEngine/Dependencies/OBJ_Loader/OBJ_Loader.hpp"
#pragma region Settings
    #define APP_NAME "GreyModel3D"
    constexpr int WIDTH = 1280;
    constexpr int HEIGHT = 640;
    /*DEBUG MODE*/#define DEBUGCONSOLE 1
    float MouseSensitivity = 1.0f;//it is multiplied with the sensitivity(lower slower)
    auto LIGHT_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
#pragma endregion
#pragma region including GreyEngine Resources
    namespace Grey3D
    {
        std::string SelectedType;
        /// <summary>
        /// 0: x, 1: y, 2: z
        /// </summary>
        int* SelectedData = (int*)malloc(10);
        int SelectedObject = -1;
        int SelectedComponent = -1;
        vec3 LastPos;
    }
    #include "Engine/DebugLog.hpp"
    #include "Engine/Shader.hpp"
    #include "Engine/Component.hpp"
    #include "Engine/Object.hpp"
    #include "Engine/Components/Transform.hpp"
    #include "Engine/Components/Mesh.hpp"
    #include "Engine/Components/Texture.hpp"
    #include "Engine/Components/Mirror.hpp"
    #include "Engine/Renderer.hpp"
#pragma endregion