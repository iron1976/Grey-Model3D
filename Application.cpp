#define _CRT_SECURE_NO_WARNINGS
#include "GreyEngine/GreyEngine.hpp"
#include <direct.h>
#include <fstream>
#include "Shlobj.h"
#include <comdef.h>
#pragma region including imGUI
    #include "Dependencies/imgui/imgui.h"
    #include "Dependencies/imgui/imgui_impl_glfw.h"
    #define IMGUI_IMPL_OPENGL_LOADER_GLEW
    #include "Dependencies/imgui/imgui_impl_opengl3.h"
    #include "Dependencies/imgui/imgui_internal.h"
#pragma endregion
#pragma region Settings
    constexpr int INSPECTOR_WIDTH = 200;
    constexpr int INSPECTOR_HEIGHT = 500;
    #define INSPECTOR 1
    #define LOCK_INSPECTOR_POS 1
    auto THEME_COLOR = ImVec4(0.3f, 0.0f, 0.7f, 1.00f);
    bool SHOW_GUI = 1;
    const char* LOG_FILE_PATH = "\\GreyModel3D\\";
#pragma endregion

#include "Dependencies/imgui/imguiSkins/1.h"

double Scroll;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Scroll = ypos;
}

const std::string GetDocumentsFolderPath()
{
    wchar_t Folder[1024];
    HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
    if (SUCCEEDED(hr))
    {
        char str[1024];
        wcstombs(str, Folder, 1023);
        return str;
    }
    else return "";
}
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
bool LOG(std::string text)
{
    #if DEBUGCONSOLE
        print("LOG insert: " + text);
    #endif
    //print(GetDocumentsFolderPath() + (std::string)LOG_FILE_PATH + "LOGS.txt");
    std::ofstream WobjFile(GetDocumentsFolderPath() + (std::string)LOG_FILE_PATH + "LOGS.txt", std::ios_base::app);
    if (WobjFile.fail())
        return 0;
    WobjFile << "\n"+currentDateTime() + ": " + text;
    WobjFile.close();
    return 1;
}
INIT
{
    #pragma region  ImGui Initializing1
    ImGuiContext * ctx;
    ImGuiStyle* style;
    IMGUI_CHECKVERSION();
    ctx = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    style = &ImGui::GetStyle();
    ImGuiShatteredStyle(WIDTH, HEIGHT);
    #pragma endregion

    MainRenderer mainRenderer;
    Shader shader("src\\Shaders\\BasicVertex.shader",
        "src\\Shaders\\BasicFragment.shader");
    mainRenderer.SetRendererShader(shader);
    GLFWwindow* window = mainRenderer.window;
    #pragma region ImGui Initializing2
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    ImGui::SetCurrentContext(ctx);
    #pragma endregion
    stbi_set_flip_vertically_on_load(1);
    #if DEBUGCONSOLE
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    #else
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif
    //Built in objects
    Object GUICross(1);
    {
        GUICross.AddComponent<Transform>()->SetTransform(vec3(-999, -999, -999), &mainRenderer.view);
        /*x*/GUICross.AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.15f, 0.15f, 0.0f, -0.14f, 0.16f, 0.0f, 0.14f, -0.16f, 0.0f, 0.15f, -0.15f, 0.0f, -0.15f, -0.15f, 0.0f, -0.14f, -0.16f, 0.0f, 0.14f, 0.16f, 0.0f, 0.15f, 0.15f, 0.0f}, std::vector<unsigned int>{ 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 }, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        /*y*/GUICross.AddComponent<Mesh>()->SetMesh(std::vector<float>{0.0f, 0.15f, -0.15f, 0.0f, 0.16f, -0.14f, 0.0f, -0.16f, 0.14f, 0.0f, -0.15f, 0.15f, -0.0f, -0.15f, -0.15f, -0.0f, -0.16f, -0.14f, 0.0f, 0.16f, 0.14f, 0.0f, 0.15f, 0.15f }, std::vector<unsigned int>{ 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 }, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        /*z*/GUICross.AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.15f, 0.0f, 0.15f, -0.14f, 0.0f, 0.16f, 0.14f, 0.0f, -0.16f, 0.15f, 0.0f, -0.15f, -0.15f, 0.0f, -0.15f, -0.14f, 0.0f, -0.16f, 0.14f, 0.0f, 0.16f, 0.15f, 0.0f, 0.15f}, std::vector<unsigned int>{0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7}, vec4(0, 0, 1, 1));
    }
    Object GUIArrows(1);
    {
        GUIArrows.AddComponent<Transform>()->SetTransform(vec3(-999, -999, -999), &mainRenderer.view);

        //x
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{0.0f, -0.005f, 0.005f,0.15f,-0.005f, 0.005f,0.0f,  0.005f, 0.005f,0.15f, 0.005f, 0.005f,0.0f, -0.005f,-0.005f,0.15f,-0.005f,-0.005f,0.0f,  0.005f,-0.005f,0.15f, 0.005f,-0.005f,}, std::vector<unsigned int>{0,1,2,  1,2,3,  4,5,6, 5,6,7,0,4,5,  0,1,5,  2,3,6, 6,7,3}, vec4(1, 0, 0, 1));
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{0.15f, -0.005f, 0.005f,0.15f, 0.005f, 0.005f,0.15f, -0.005f, -0.005f,0.15f, 0.005f, -0.005f,0.20f, 0.0f, 0.0f}, std::vector<unsigned int>{0,1,4, 0,2,4, 1,3,4, 2,3,4}, (float*)&THEME_COLOR);

        //y
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.005f, 0.00f, 0.005f,-0.005f, 0.15f, 0.005f,0.005f, 0.00f, 0.005f,0.005f, 0.15f, 0.005f,-0.005f, 0.00f, -0.005f,-0.005f, 0.15f, -0.005f,0.005f, 0.00f, -0.005f,0.005f, 0.15f, -0.005f,}, std::vector<unsigned int>{0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7,0, 4, 5, 0, 1, 5, 2, 3, 6, 6, 7, 3}, vec4(0, 1, 0, 1));
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.005f, 0.15f,  0.005f,0.005f, 0.15f,  0.005f,-0.005f, 0.15f, -0.005f,0.005f, 0.15f, -0.005f,0.0f, 0.20f, 0.0f}, std::vector<unsigned int>{ 0, 1, 4, 0, 2, 4, 1, 3, 4, 2, 3, 4}, (float*)&THEME_COLOR);

        //z
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{0.005f, -0.005f, 0.00f,0.005f, -0.005f, 0.15f,0.005f,  0.005f, 0.00f,0.005f,  0.005f, 0.15f,-0.005f, -0.005f, 0.00f,-0.005f, -0.005f, 0.15f,-0.005f, 0.005f, 0.00f,-0.005f, 0.005f, 0.15f,}, std::vector<unsigned int>{0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7,0, 4, 5, 0, 1, 5, 2, 3, 6, 6, 7, 3}, vec4(0, 0, 1, 1));
        GUIArrows.AddComponent<Mesh>()->SetMesh(std::vector<float>{0.005f, -0.005f, 0.15f,0.005f, 0.005f, 0.15f,-0.005f, -0.005f, 0.15f,-0.005f, 0.005f, 0.15f,0.0f, 0.0f, 0.20f}, std::vector<unsigned int>{ 0, 1, 4, 0, 2, 4, 1, 3, 4, 2, 3, 4}, (float*)&THEME_COLOR);
    }

    Object Ass;
    Ass.name = "obj1";
    Ass.AddComponent<Transform>()->SetTransform(vec3(0), vec3(1));
    Ass.AddComponent<Mesh>()->SetMesh(std::vector<float>{
        -0.5f, -0.5f, -0.f,
            -0.5f, 0.5f, -0.0f,
            0.5f, 0.5f, -0.0f,
            0.5f, -0.5f, -0.0f
    }, std::vector<unsigned int>{0, 1, 2, 0, 3, 2}, vec4(1, 1, 1, 1));
    
    Object Cube;
    Cube.name = "mirror";
    Cube.AddComponent<Transform>()->SetTransform(vec3(0), vec3(1));
    Cube.AddComponent<Mesh>()->SetMesh(std::vector<float>{
     2.0f,-0.5f, -0.5f,
     2.0f, 0.5f, -0.5f,
     1.0f, 0.5f, 0.5f,
     1.0f,-0.5f, 0.5f
    }, std::vector<unsigned int>{0, 1, 2, 0, 3, 2}, vec4(1, 1, 1, 1));

    

    //Cube.AddComponent<Texture>()->SetTexture("C:/Users/PC/Desktop/c coding/GreyModel3D/src/Textures/cubemix.png");
    Cube.AddComponent<Mirror>()->SetMirror("0,", &mainRenderer.view);
    Cube.GetComponent<Mirror>()[0]->Size = vec2(2, 2);

    Object Background;
    Background.name = "background";
    Background.AddComponent<Transform>()->SetTransform(vec3(0), vec3(1));
    Background.AddComponent<Mesh>()->SetMesh(std::vector<float>{
        2.1f, -0.5f, -0.5f,
            2.1f, 0.5f, -0.5f,
            1.1f, 0.5f, 0.5f,
            1.1f, -0.5f, 0.5f
    }, std::vector<unsigned int>{0, 1, 2, 0, 3, 2}, vec4(1, 1, 1, 1));

    mainRenderer.view[3][3] = 2;
    #pragma region Mouse Vars
    int mouse_pressed = 0;
    vec2 firstpressed(0, 0);
    vec3 firstpressedxyz(0, 0, 0);
    bool MakeCursorHand = false;
    int prevscroll = 0;
    #pragma endregion
    #pragma region GUI Screen Coordinates
    bool GUI_Vertice_Enable = false;
    vec2 GUI_Vertice_Coords = vec2(0, 0);
    std::string GUI_Vertice_Text = "null";
    #pragma endregion
    #pragma region GUI Inspector Vars
    bool inspect_obj = false;
    bool inspect_component = false;
    bool saveObject = false;
    char* saveObjectPath = (char*)calloc(100, 1);
    int CurrentObjectIndex = 2;

    bool* CheckboxContainer;
    bool isCheckbox = false;
    bool currIsCheckbox = isCheckbox;
    bool unSelected = false;
    bool Selected = true;
    Component* inspectedComponent = nullptr;
    char* newObjectName = (char*) calloc(43,1);
    char* objFilePath = (char*)calloc(100, 1);
    bool AddObjectMenu = false;
    ImVec2 InspectorPos;

    bool showComponentList = false;
    int SelectedComponent = -1;
    int SelectedObject = -1;
    bool setInspectorPos = true;
    std::unordered_map<std::string, std::function<void(void*)>> ComponentDict;
    ComponentDict["Mesh"] = (std::function<void(void*)>)[&](void* obj) {
    ((Object*)(obj))->AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.5f, -0.5f, 0, 0.5f, -0.5f, 0, 0.0f, 0.5f, 0}, std::vector<unsigned int>{0, 1, 2}, vec4(1, 1, 1, 1));
    };
    ComponentDict["Transform"] = (std::function<void(void*)>)[&](void* obj) {
        ((Object*)(obj))->AddComponent<Transform>()->SetTransform(vec3(0,0,0), vec3(1,1,1));
    };
    ComponentDict["Texture"] = (std::function<void(void*)>)[&](void* obj) {

        if (((Object*)(obj))->GetComponent<Texture>() != nullptr)
            ((Object*)(obj))->RemoveComponent(((Object*)(obj))->GetComponent<Texture>()[0]);
        ((Object*)(obj))->AddComponent<Texture>()->SetTexture("s");
        ((Object*)(obj))->AddComponent<Mesh>()->SetMesh(std::vector<float>{
            -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f
        }, std::vector<unsigned int>{0, 1, 2, 0, 3, 2}, vec4(1, 0, 0, 1));
    };

    std::vector<const char*> ComponentList;
    for (auto i = ComponentDict.begin(); i != ComponentDict.end(); i++)ComponentList.push_back((i->first).c_str());
    #pragma endregion
    while (!mainRenderer.IsApplicationClosed())[&]()
    #if !DEBUGCONSOLE
        noexcept
    #endif
    {
        mainRenderer.BeginRender();
        glfwSetScrollCallback(window, cursor_position_callback);

        //Rendering
        for (auto obj : ObjectList)
            mainRenderer.render(*obj);
        
        //Built in objects
        mainRenderer.render(GUICross);
        mainRenderer.render(GUIArrows);

        #pragma region Keyboard Camera Inputs
        if (mainRenderer.IsKeyPressed(GLFW_KEY_Z))
            mainRenderer.CameraRotate(1.0f, glm::vec3(1, 0, 0));
        if (mainRenderer.IsKeyPressed(GLFW_KEY_X))
            mainRenderer.CameraRotate(1.0f, glm::vec3(-1, 0, 0));

        if (mainRenderer.IsKeyPressed(GLFW_KEY_SPACE))
        {
            if (mainRenderer.IsKeyPressed(GLFW_KEY_W))
                mainRenderer.view = glm::translate(mainRenderer.view, vec3(0, 0, -0.1f));
            if (mainRenderer.IsKeyPressed(GLFW_KEY_S))
                mainRenderer.view = glm::translate(mainRenderer.view, vec3(0, 0, +0.1f));
            if (mainRenderer.IsKeyPressed(GLFW_KEY_A))
                mainRenderer.view = glm::translate(mainRenderer.view, vec3(+0.1f, 0, 0));
            if (mainRenderer.IsKeyPressed(GLFW_KEY_D))
                mainRenderer.view = glm::translate(mainRenderer.view, vec3(-0.1f, 0, 0));
        }
        if (mainRenderer.IsKeyPressed(GLFW_KEY_R))//Reset The Camera
        {
            mainRenderer.view = glm::translate(mat4(1.0f), vec3(0,0,0));
            mainRenderer.view[3][3] = 2;
            mainRenderer.CameraResetRotation();
        }
        if (mainRenderer.IsKeyPressed(GLFW_KEY_F10))SHOW_GUI = 0;
        if (mainRenderer.IsKeyPressed(GLFW_KEY_F11))SHOW_GUI = 1;
        
        #pragma endregion
     
        #pragma region Rotating World
            if (mainRenderer.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
            {
                if (mouse_pressed == 0)
                {
                    mouse_pressed = 1;
                    firstpressed = vec2(mainRenderer.Cursor.x, mainRenderer.Cursor.y);
                    firstpressedxyz = mainRenderer.view_anglexyz;
                }
                else if (mouse_pressed == 1)
                {
                    //   print("\n" << glm::to_string(vec2(Cursor.x, Cursor.y) - firstpressed));
                }
                vec2 newpoint = vec2(mainRenderer.Cursor.x, mainRenderer.Cursor.y) - firstpressed;


                MakeCursorHand = true;
                if (mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
                    mainRenderer.CameraSetRotation(vec3(0, (firstpressedxyz.y + (newpoint.x * -1 * MouseSensitivity)), firstpressedxyz.z));
                else if (mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_ALT))
                    mainRenderer.CameraSetRotation(vec3(firstpressedxyz.x + (newpoint.y * -1 * MouseSensitivity), 0, firstpressedxyz.z));
                else
                    mainRenderer.CameraSetRotation(vec3(firstpressedxyz.x + (newpoint.y * -1 * MouseSensitivity), (firstpressedxyz.y + (newpoint.x * -1 * MouseSensitivity)), firstpressedxyz.z));
                
            }
            else
            {
                mouse_pressed = 0;
                MakeCursorHand = false;
            }
        #pragma endregion
        #pragma region ZoomIn&ZoomOut
            if (Scroll > prevscroll)
            {
                Scroll = prevscroll;
                mainRenderer.view[3][3] -= 0.25f;
            }
            else if (Scroll < prevscroll)
            {
                Scroll = prevscroll;
                mainRenderer.view[3][3] += 0.25f;
            }
        #pragma endregion
        #pragma region Changing Object Vertices
            if(Grey3D::SelectedObject != -1 && Grey3D::SelectedType.c_str()[0] == 'V' && Grey3D::SelectedType.c_str()[1] == 'e' && Grey3D::SelectedType.c_str()[2] == 'r')
            {

                
                ObjectList[Grey3D::SelectedObject]->GetComponent<Mesh>()[Grey3D::SelectedComponent]->vertices[Grey3D::SelectedData[0]];
                GUICross.GetComponent<Transform>()[0]->Position = ((glm::vec3(
                    ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[0]],
                    ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[1]],
                    ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[2]]
                ) + Grey3D::LastPos + vec3(0, 0, 0))  / mainRenderer.view[3][3]) ;
                
                if (mainRenderer.Cursor.x < WIDTH - INSPECTOR_WIDTH && mainRenderer.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                {

                    float resultX, resultY, resultZ;


                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_ALT))//X axis
                        ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[0]] = mainRenderer.Cursor.To3DWorldPosition().x - Grey3D::LastPos.x;
                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))//Y axis
                        ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[1]] = mainRenderer.Cursor.To3DWorldPosition().y - Grey3D::LastPos.y;
                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))//Z axis
                        ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[2]] = mainRenderer.Cursor.To3DWorldPosition().z - Grey3D::LastPos.z;


                    GUI_Vertice_Enable = true;

                    GUI_Vertice_Coords = vec2(mainRenderer.Cursor.x, mainRenderer.Cursor.y);
                    GUI_Vertice_Text =
                    (std::string)"("+
                    (std::string)std::to_string(((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[0]]) + (std::string)","+
                    (std::string)std::to_string(((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[1]]) + (std::string)","+
                    (std::string)std::to_string(((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->vertices[Grey3D::SelectedData[2]]) +
                    (std::string)")";

                }
                else if (GUI_Vertice_Enable)
                {
                    LOG("Ver" + std::to_string(Grey3D::SelectedData[0]) + " Changed(obj:" + ObjectList[Grey3D::SelectedObject]->name + " comp:"+ ((Mesh*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->operator std::string() +")" +") to " + GUI_Vertice_Text);
                    GUI_Vertice_Enable = false;
                }
            }
        #pragma endregion
        #pragma region Changing Object Position
            if (Grey3D::SelectedObject != -1 && Grey3D::SelectedType.c_str()[0] == 'P' && Grey3D::SelectedType.c_str()[1] == 'o' && Grey3D::SelectedType.c_str()[2] == 's')
            {

                GUIArrows.GetComponent<Transform>()[0]->Position =
                ObjectList[Grey3D::SelectedObject]->GetComponent<Transform>()[0]->Position/mainRenderer.view[3][3];


                if (mainRenderer.Cursor.x < WIDTH - INSPECTOR_WIDTH && mainRenderer.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                {

                    float resultX, resultY, resultZ;

                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_ALT))//X axis
                        ObjectList[Grey3D::SelectedObject]->GetComponent<Transform>()[0]->Position.x = mainRenderer.Cursor.To3DWorldPosition().x;
                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))//Y axis
                        ObjectList[Grey3D::SelectedObject]->GetComponent<Transform>()[0]->Position.y = mainRenderer.Cursor.To3DWorldPosition().y;
                    if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))//Z axis
                        ObjectList[Grey3D::SelectedObject]->GetComponent<Transform>()[0]->Position.z = mainRenderer.Cursor.To3DWorldPosition().z;

                    GUI_Vertice_Enable = true;
                    GUI_Vertice_Coords = vec2(mainRenderer.Cursor.x, mainRenderer.Cursor.y);
                    GUI_Vertice_Text =
                    (std::string)"(" +
                    (std::string)std::to_string(((Transform*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->Position.x) + (std::string)"," +
                    (std::string)std::to_string(((Transform*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->Position.y) + (std::string)"," +
                    (std::string)std::to_string(((Transform*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->Position.z) +
                    (std::string)")";

                }
                else if (GUI_Vertice_Enable)
                {
                    LOG((std::string)"Pos0" + " Changed(obj: " + ObjectList[Grey3D::SelectedObject]->name + " comp:" + ((Transform*)ObjectList[Grey3D::SelectedObject]->GetComponents()[Grey3D::SelectedComponent])->operator std::string() + ") to " + GUI_Vertice_Text);
                    GUI_Vertice_Enable = false;
                }
            }
        #pragma endregion
        #pragma region GUI
        if(SHOW_GUI)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            #pragma region On Screen Text
                if (GUI_Vertice_Enable)
                {
                    ImGuiTransparentWindow(WIDTH, HEIGHT);
                    if (ImGui::Begin("World Text", nullptr, ImGuiWindowFlags_NoCollapse))
                    {
                        ImGui::SetWindowPos(ImVec2(0, 0), true);
          
                        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), 15, ImVec2(GUI_Vertice_Coords.x + 25, GUI_Vertice_Coords.y - 25), ImColor((int)(255 / THEME_COLOR.x), (int)(255 / THEME_COLOR.y), (int)(255 / THEME_COLOR.z), 255), GUI_Vertice_Text.c_str(), 0, 0.0f, 0);
                        if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_ALT))//X axis
                            ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), 25, ImVec2(WIDTH - 90, HEIGHT - 75), ImColor(255, 0, 0, 255), "X AXIS", 0, 0.0f, 0);
                        if (!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))//Y axis
                            ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), 25, ImVec2(WIDTH - 90, HEIGHT - 50), ImColor(0, 255, 0, 255), "Y AXIS", 0, 0.0f, 0);
                        if(!mainRenderer.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))//Z axis
                            ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), 25, ImVec2(WIDTH - 90, HEIGHT - 25), ImColor(0, 0, 255, 255), "Z AXIS", 0, 0.0f, 0);


                        ImGui::End();
                    }
                }
            #pragma endregion
            ImGuiShatteredStyle(WIDTH, HEIGHT);
            #if DEBUGCONSOLE 
                if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse))
                {
                    ImGui::Text("Camera 4x4Matrices:");
                    ImGui::Text(mainRenderer.GetMatrix(mainRenderer.view).c_str());
                    ImGui::Text("Rotation : ");
                    ImGui::Text((glm::to_string(mainRenderer.view_anglexyz)).c_str());
                    ImGui::Text("Mouse Position(WORLD): ");
                    ImGui::Text((glm::to_string(mainRenderer.Cursor.ToWorldPoint()).c_str()));
                    ImGui::Text("Mouse Position(SCREEN): ");
                    ImGui::Text(((std::string)mainRenderer.Cursor).c_str());
                    ImGui::Text("Mouse Scroll: ");
                    ImGui::Text((std::to_string(Scroll)).c_str());
                    ImGui::SetWindowSize(ImVec2(321, 22), true);
                    ImGui::SetWindowPos(ImVec2(0, 0), true);
                    ImGui::End();
                }
            #endif  
            #if INSPECTOR
                if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoCollapse))
                {
                    #ifdef LOCK_INSPECTOR_POS
                    ImGui::SetWindowPos(ImVec2(WIDTH - INSPECTOR_WIDTH, 0), true);
                    #else
                    if (setInspectorPos) { ImGui::SetWindowPos(ImVec2(WIDTH - INSPECTOR_WIDTH, 0), true); setInspectorPos = 0; }
                    #endif
                    InspectorPos = ImGui::GetWindowPos();
                    ImGui::SetWindowSize(ImVec2(INSPECTOR_WIDTH, INSPECTOR_HEIGHT), 0);
                    ImGui::TextColored(ImVec4(0.25f + THEME_COLOR.x, 0.25f + THEME_COLOR.y, 0.25f + THEME_COLOR.z, 1), "Objects:");
                    ImGui::SetCursorPosX(1.f);
                    if (ImGui::BeginChild("Objects", ImVec2(185, 200), true, ImGuiWindowFlags_AlwaysAutoResize))
                    {
                        #pragma region Listing Objects
                    for (int TempObject = 0; TempObject < ObjectList.size(); TempObject++)
                    {
                        if (inspect_obj && SelectedObject != TempObject)
                            goto skip_button;
                                
                        if (ImGui::Button(ObjectList[TempObject]->name.c_str(), ImVec2(100, 25)))
                        {
                            SelectedObject = TempObject;
                            inspect_obj = !inspect_obj;
                            inspectedComponent = nullptr;
                            inspect_component = false;
                            break;
                        }
                        ImGui::SetCursorPosX(115);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY()-27);
                        ImGui::Text(("(ID:"+std::to_string(ObjectList[TempObject]->ObjectID)+")").c_str());
                        ImGui::SetCursorPosX(10.f);
                        skip_button: {}
                    }
                    #pragma endregion
                        ImGui::SetCursorPosX(6.f);
                        #pragma region Listing Components & Component View
                        if (inspect_obj && ImGui::BeginChild("Components", ImVec2(167, 125), true, 0))
                        {
                            if (inspect_obj && !inspect_component && ImGui::Button("Destroy Object", ImVec2(125, 22)))
                            {
                                auto ptr = &(*ObjectList[SelectedObject]);

                                ObjectList[SelectedObject]->~Object();

                                inspect_obj = false;
                            }
                            if (inspect_obj && !inspect_component && ImGui::Button("Save Object", ImVec2(125, 22)))
                            {
                                saveObject = !saveObject;
                            }
                            if (saveObject && inspect_obj && !inspect_component)
                            {
                                ImGui::Text("File path must");
                                ImGui::Text("end with \"/\" or \"\\\"");
                                ImGui::Text("Path:");
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
                                ImGui::Text("-------------------------");
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 12);
                                ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 3);
                                ImGui::InputText("saveObjectPath", saveObjectPath, 90, 0, 0, nullptr, 1);
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 14);
                                ImGui::Text("-------------------------");
                                if (ImGui::Button("Save", ImVec2(38, 22)))
                                {
                                    if (((std::string)saveObjectPath)[((std::string)saveObjectPath).size() - 1] != '/' &&
                                        ((std::string)saveObjectPath)[((std::string)saveObjectPath).size() - 1] != '\\')
                                    {
                                        ImGui::Text("Failed");
                                    }
                                    else
                                    {
                                        std::ofstream objFile(((std::string)saveObjectPath + ObjectList[SelectedObject]->name + ".obj").c_str());

                                        objFile << ObjectList[SelectedObject]->GetComponent<Mesh>()[0]->ToObj();
                                        objFile.close();


                                        ImGui::Text("Successful");
                                        saveObject = !saveObject;
                                        inspect_obj = false;
                                    }
                                }
                            }
                            if (!inspect_component)
                            {
                                for (int j = 0; j < ObjectList[SelectedObject]->GetComponents().size(); j++)
                                    if (ImGui::Button(ObjectList[SelectedObject]->GetComponents()[j]->operator std::string().c_str(), ImVec2(150, 25)))
                                    {
                                        inspectedComponent = ObjectList[SelectedObject]->GetComponents()[j];
                                        inspect_component = !inspect_component;
                                        SelectedComponent = j;
                                        break;
                                    }
                            }
                            else {
                                const float x = 5.5f;
                                ImGui::SetCursorPosX(5);
                                ImGui::SetCursorPosY(5);
                                if (ImGui::Button("X", ImVec2(22, 22)))
                                {
                                    inspect_component = false;
                                    Grey3D::SelectedType = "";
                                    Grey3D::SelectedObject = -1;
                                    GUICross.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                    GUIArrows.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                    inspectedComponent = nullptr;
                                }
                                ImGui::SetCursorPosX(x + 24);
                                ImGui::SetCursorPosY(5);
                                if (ImGui::Button("Remove Component", ImVec2(125, 22)))
                                {
                                    ObjectList[SelectedObject]->RemoveComponent(inspectedComponent);
                                    inspect_component = false;
                                    Grey3D::SelectedType = "";
                                    Grey3D::SelectedObject = -1;
                                    GUICross.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                    GUIArrows.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                    inspectedComponent = nullptr;
                                }
                                if (inspectedComponent != nullptr)
                                {
                                    ImGui::SetCursorPosX(x);
                                    ImGui::Text((((std::string)*inspectedComponent).substr(0, ((std::string)*inspectedComponent).find_last_of('(')) + " Variables:").c_str());

                                    ImGui::SetCursorPosX(x - 2.25f);

                                    ImGui::SetWindowSize(ImVec2(150, 155));
                                    float x = 10.f;
                                    float y = 64.0f;



                                    auto GUI_VARS = inspectedComponent->GUI_VARS();

                                    auto AddDatum = (std::function<void(void*)>*)GUI_VARS.begin()->second[2];

                                    int j = 0;
                                    for (auto i = GUI_VARS.begin(); i != GUI_VARS.end(); i++)
                                    {
                                        ImGui::SetCursorPosY(y);
                                        ImGui::SetCursorPosX(x);
                                        if ((int)i->second[0] > 1)
                                        {
                                            std::string id; for (int x = 0; x < j; x++)id += " ";

                                            if (i->second[1] != nullptr && ImGui::Button(id.c_str(), ImVec2(22, 22)))
                                            {
                                                isCheckbox = !isCheckbox;
                                                if (isCheckbox)
                                                {
                                                    (*(std::function<void(int, int, int, std::vector<void*>)>*)i->second[1])(SelectedObject, SelectedComponent, j, i->second);
                                                }
                                                else
                                                {
                                                    Grey3D::SelectedType = "";
                                                    Grey3D::SelectedObject = -1;
                                                    GUICross.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                                    GUIArrows.GetComponent<Transform>()[0]->Position = vec3(-999, -999, -999);
                                                }
                                            }

                                            if (i->first == Grey3D::SelectedType)
                                            {
                                                ImGui::SetCursorPosY(y + 4.f);
                                                ImGui::SetCursorPosX(x + 7.75f);
                                                ImGui::Text("X");
                                                ImGui::SetCursorPosY(y);
                                                ImGui::SetCursorPosX(x);
                                            }
                                        }
                                        else
                                        {
                                            ImGui::SetCursorPosY(y + 2);
                                            ImGui::SetCursorPosX(x + 3.5f);
                                            goto skip;
                                        }

                                        ImGui::SetCursorPosY(y + 2);
                                        ImGui::SetCursorPosX(x + 23.5f);
                                    skip:

                                        ImGui::Text((i->first + ":").c_str());

                                        if ((int)i->second[0] <= 1)
                                        {
                                            ImGui::SetCursorPos(ImVec2(x + 40, y - 3));
                                            if ((int)i->second[1] == 0)
                                            {
                                                if (ImGui::InputFloat((i->first).c_str(), (float*)i->second[4], 0, 0, "%.3f", 0))
                                                    LOG((i->first) + " Changed(obj:" + ObjectList[SelectedObject]->name + " comp:" + (std::string)*inspectedComponent + ") to " + std::to_string(*(float*)i->second[4]));
                                            }
                                            else if ((int)i->second[1] == 1)//For String type
                                                ImGui::InputText((i->first).c_str(), (char*)i->second[4], 200, 0, 0, nullptr, 1);
                                        }
                                        else
                                        {
                                            ImGui::SetCursorPos(ImVec2(x + 61, y - 3));
                                            ImGui::PushItemWidth(26.0f);
                                            for (int j = 0; j < (int)(i->second[0]); j++)
                                            {
                                                if (j == 0)
                                                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.f, 0.0f, 0.0f, 1.00f);
                                                else if (j == 1)
                                                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.f, 0.f, 1.00f);
                                                else
                                                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 1.f, 1.00f);



                                                if (ImGui::InputFloat((i->first + std::to_string(j)).c_str(),

                                                    ((int)i->second[3] == -1 ?
                                                        (float*)&((Mesh*)inspectedComponent)->vertices[(int)i->second[j + 4]] :
                                                        (float*)i->second[j + 4]
                                                        ), 0, 0, "%.3f", 0, 2.0f))
                                                    LOG(i->first
                                                        + "[" +
                                                        (j == 0 ? "X" : j == 1 ? "Y" : j == 2 ? "Z" : "0")
                                                        + "]" +
                                                        " Changed(obj:" + ObjectList[SelectedObject]->name + " comp:" + (std::string)*inspectedComponent + ") to " +
                                                        std::to_string(((int)i->second[3] == -1 ? *((float*)&((Mesh*)inspectedComponent)->vertices[(int)i->second[j + 4]]) : *((float*)i->second[j + 4]))));
                                                ImGui::SetCursorPos(ImVec2(x + 61 + ((j + 1) * 24.5f), y - 3));
                                            }
                                            ImGui::PopItemWidth();
                                            ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.93f, 1.00f);
                                        }
                                        ImGui::SetCursorPos(ImVec2(x + 60, y - 3));
                                        currIsCheckbox = isCheckbox;


                                        y += 25.0f;
                                        j++;
                                    }
                                    ImGui::SetCursorPos(ImVec2(x, y + 5));
                                    if (AddDatum != nullptr && ImGui::Button("+", ImVec2(22, 22)))
                                    {
                                        (*AddDatum)(inspectedComponent);
                                    }
                                }
                            }
                            if (!inspect_component && ImGui::Button("+", ImVec2(20, 25)))
                                showComponentList = !showComponentList;

                            if (showComponentList && ImGui::ListBox("AddComponent", &SelectedComponent, &ComponentList[0], ComponentList.size(), 1))
                            {
                                showComponentList = false;

                                ComponentDict[ComponentList[SelectedComponent]](ObjectList[SelectedObject]);
                            }

                            ImGui::EndChild();
                        }
                    #pragma endregion
                        ImGui::SetCursorPosX(10.f);
                        #pragma region Add Object Button
                        if (!inspect_obj && ImGui::Button("+", ImVec2(22, 22)))
                            AddObjectMenu = !AddObjectMenu;
                        if (AddObjectMenu)
                        {
                            ImGui::Text("Object Name:");
                            ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 82, ImGui::GetCursorPos().y - 25));
                            ImGui::InputText("Object Name", newObjectName, 37, 0, 0, nullptr, 1);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7.0f);
                            ImGui::Text("Obj File Path(optional):");
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
                            ImGui::Text("-------------------------");
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 12);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 3);
                            ImGui::InputText(".Obj File Path", objFilePath, 90, 0, 0, nullptr, 1);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 14);
                            ImGui::Text("-------------------------");
                            if (ImGui::Button("+ Add Object", ImVec2(120, 22)))
                            {
                                for (auto i : ObjectList)
                                    if (i->name == (std::string)newObjectName)
                                    {
                                        ImGui::Text("Object name is in use.");
                                        goto failed;
                                    }
                                Object* newObject = new Object();
                                newObject->name = newObjectName;

                                newObject->AddComponent<Transform>()->SetTransform(vec3(0), vec3(1));
                                if ((int)objFilePath[0] != 0)
                                {
                                    objl::Loader loader;
                                    loader.LoadFile(objFilePath);

                                    if ((int)newObjectName[0] == 0)
                                        newObject->name = loader.LoadedMeshes[0].MeshName;
                                    print("mesh size: " << loader.LoadedMeshes.size());
                                    for (int i = 0; i < loader.LoadedMeshes.size(); i++)
                                    {
                                        Mesh* CurrentMesh = newObject->AddComponent<Mesh>();
                                        CurrentMesh->SetMesh(std::vector<float>{}, std::vector<unsigned int>{}, vec4(0.8f, 0.8f, 0.8f, 1));
                                        CurrentMesh->indices = loader.LoadedMeshes[i].Indices;

                                        for (int j = 0; j < loader.LoadedMeshes[i].Vertices.size(); j++)
                                        {
                                            CurrentMesh->vertices.push_back(loader.LoadedMeshes[i].Vertices[j].Position.X);
                                            CurrentMesh->vertices.push_back(loader.LoadedMeshes[i].Vertices[j].Position.Y);
                                            CurrentMesh->vertices.push_back(loader.LoadedMeshes[i].Vertices[j].Position.Z);
                                        }
                                    }

                                    loader.~Loader();
                                }
                                else
                                    newObject->AddComponent<Mesh>()->SetMesh(std::vector<float>{-0.5f, -0.5f, 0, 0.5f, -0.5f, 0, 0.0f, 0.5f, 0}, std::vector<unsigned int>{0, 1, 2}, vec4(1, 1, 1, 1));
                                AddObjectMenu = false;
                            }
                        failed: {}
                        }
                    ImGui::EndChild();
                    #pragma endregion
                    }
                    ImGui::Text("Inspector Settings:");
                    if (ImGui::BeginChild("Settings", ImVec2(195, 175), true, 0))
                    {
                        ImGui::Text("GuiR:");
                        ImGui::SetCursorPos(ImVec2(45, 5));
                        ImGui::InputFloat("GuiR", &THEME_COLOR.x, 0, 0, "%.3f", 0);
                        ImGui::SetCursorPos(ImVec2(10, 30));
                        ImGui::Text("GuiG:");
                        ImGui::SetCursorPos(ImVec2(45, 25));
                        ImGui::InputFloat("GuiG", &THEME_COLOR.y, 0, 0, "%.3f", 1);
                        ImGui::SetCursorPos(ImVec2(10, 50));
                        ImGui::Text("GuiB:");
                        ImGui::SetCursorPos(ImVec2(45, 45));
                        ImGui::InputFloat("GuiB", &THEME_COLOR.z, 0, 0, "%.3f", 1);
                        ImGui::SetCursorPos(ImVec2(10, 70));
                        ImGui::Text("LightR:");
                        ImGui::SetCursorPos(ImVec2(58, 65));
                        ImGui::InputFloat("LightR", &LIGHT_COLOR.x, 0, 0, "%.3f", 1);
                        ImGui::SetCursorPos(ImVec2(10, 90));
                        ImGui::Text("LightG:");
                        ImGui::SetCursorPos(ImVec2(58, 85));
                        ImGui::InputFloat("LightG", &LIGHT_COLOR.y, 0, 0, "%.3f", 1);
                        ImGui::SetCursorPos(ImVec2(10, 110));
                        ImGui::Text("LightB:");
                        ImGui::SetCursorPos(ImVec2(58, 105));
                        ImGui::InputFloat("LightB", &LIGHT_COLOR.z, 0, 0, "%.3f", 1);

                        ImGui::SetCursorPos(ImVec2(10, 150));
                        ImGui::Text("Mouse Sensitivity:");
                        ImGui::SetCursorPos(ImVec2(135, 145));
                        ImGui::InputFloat("Sensitivity", &MouseSensitivity, 0, 0, "%.3f", 1);
                        ImGui::EndChild();
                    }
                    ImGui::Text("Camera Rotation:");
                    ImGui::Text(((std::to_string((int)mainRenderer.view_anglexyz.x) + " " + std::to_string((int)mainRenderer.view_anglexyz.y) + " " + std::to_string((int)mainRenderer.view_anglexyz.z)).c_str()));
                    ImGui::End();
                }
            #endif
            ImGui::EndFrame();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        #pragma endregion

        if(MakeCursorHand)SetCursor(LoadCursor(NULL, IDC_HAND));
        mainRenderer.EndRender();
    }();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}