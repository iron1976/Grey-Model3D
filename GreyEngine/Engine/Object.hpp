#pragma once
#include <iostream>
#include <vector>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <string>
std::vector<Object*> ObjectList;


class Object
{
public:
    std::string name;
	Object(bool BUILT_IN = 0)
    #if !DEBUGCONSOLE 
        noexcept
    #endif
    : ObjectID(BUILT_IN == 0 ?  ObjectList.size() : -1)
	{
        if(!BUILT_IN) ObjectList.push_back(this);
	}
    const int ObjectID;
#pragma region Components
private:
    std::vector<Component*> Components;

    void PrintList()
    {
        std::string list;
        
        for (int j = 0; j < Components.size(); j++)
        {
            if(j != 0)
                list += ", ";
            list += (std::string)*Components[j];
        }
        std::cout <<"\n"<< list;
    }

public:
    ~Object()
    #if !DEBUGCONSOLE 
        noexcept
    #endif
    {
        for (int j = 0; j < ObjectList.size(); j++)
            if (ObjectList[j] == this)
            {
                for (int j = 0; j < this->Components.size(); j++)
                {
                    this->Components[j]->Destroy();
                }

                    ObjectList.erase(ObjectList.begin() + j);
                return;
            }
    }

    template <typename T>
    T* AddComponent()
    #if !DEBUGCONSOLE 
        noexcept
    #endif
    {
        T* comp = new T();
        Components.push_back(comp);
        comp->Initialize(this);
        return comp;
    }

    template <typename T>
    T** GetComponent()
    #if !DEBUGCONSOLE 
        noexcept
    #endif
    {
        int ErrorMode = -1;
        std::vector<T*> result;
        if (Components.size() == 0)
        {
            return nullptr;
        }

        for (auto it = Components.begin(); it != Components.end(); it++)
        {
            auto Component = dynamic_cast<T*>(*it);
            if (Component != NULL)
            {
                result.push_back(Component);
            }
        }

        return result.size() == 0 ? nullptr : &result[0];
    }
    template <typename T>
    std::vector<T*> GetComponents()
    #if !DEBUGCONSOLE 
        noexcept
    #endif
    {
        std::vector<T*> result;
        int ErrorMode = -1;

        if (Components.size() == 0)
        {
            return result;
        }

        for (auto it = Components.begin(); it != Components.end(); it++)
        {
            auto Component = dynamic_cast<T*>(*it);
            if (Component != NULL)
            {
                result.push_back(Component);
            }
        }

        return result;
    }

    std::vector<Component*> GetComponents()
    #if !DEBUGCONSOLE 
            noexcept
    #endif
    {
        return Components;
    }

    void RemoveComponent(Component* CompID)
    #if !DEBUGCONSOLE 
            noexcept
    #endif
    {
        for (auto it = Components.begin(); it != Components.end(); it++)
            if (*it == CompID)
            {
                (*it)->Destroy();
                Components.erase(it, it + 1);
                break;
            }
        
    }
#pragma endregion
};