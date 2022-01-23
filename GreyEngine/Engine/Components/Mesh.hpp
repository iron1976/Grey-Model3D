#pragma once
#include <iostream>
#include <vector>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

int MeshCount = -1;


auto OnToggleVer = (std::function<void(int, int, int,std::vector<void*>)>)[&](const int& ObjectId, const int& CompId, const int& Index, const std::vector<void*>& selectedVar) {
	Grey3D::SelectedObject = ObjectId;
	Grey3D::SelectedComponent = CompId;
	if ((int)selectedVar[0] == 3)
	{
		Grey3D::LastPos = ObjectList[ObjectId]->GetComponent<Transform>()[0]->Position;
		Grey3D::SelectedType = "Ver"+std::to_string((Index - 4) * 3);

		Grey3D::SelectedData[0] = (Index - 4) * 3;
		Grey3D::SelectedData[1] = (Index - 4) * 3+1;
		Grey3D::SelectedData[2] = (Index - 4) * 3+2;
	}
};
class Mesh : public Component
{
	void Destroy()
	{

		vertices.clear();//tried my best to avoid the memory leak but Component cannot be properly destroyed
		std::vector<float>().swap(vertices);
		indices.clear();
		std::vector<unsigned int>().swap(indices);

	    VBO = 0; 
	    VAO = 0;
	    IBO = 0;
	    MeshId = 0;
		delete Color;
	}
	Object* obj;


	std::function<void(void*)> OnAddVer = (std::function<void(void*)>)[&](void* comp) {
		unsigned int totalVertex = ((Mesh*)comp)->vertices.size()/3;
		unsigned int totalVertices = ((Mesh*)comp)->vertices.size();

		/*point1*/((Mesh*)comp)->vertices.push_back(-0.5f); ((Mesh*)comp)->vertices.push_back(-0.5f); ((Mesh*)comp)->vertices.push_back(0.0f);
		/*point2*/((Mesh*)comp)->vertices.push_back( 0.5f); ((Mesh*)comp)->vertices.push_back(-0.5f); ((Mesh*)comp)->vertices.push_back(0.0f);
		/*point3*/((Mesh*)comp)->vertices.push_back( 0.0f); ((Mesh*)comp)->vertices.push_back( 0.5f); ((Mesh*)comp)->vertices.push_back(0.0f);

		((Mesh*)comp)->indices.push_back(totalVertex + 0);
		((Mesh*)comp)->indices.push_back(totalVertex + 1);
		((Mesh*)comp)->indices.push_back(totalVertex + 2);

		std::cout << "\n";
		std::cout << totalVertex <<"    " << totalVertices;
		std::cout << "\n";
		for (int j = 0; j < (*((Mesh*)comp)).vertices.size(); j++)
			std::cout << (*((Mesh*)comp)).vertices[j] << " ";
		std::cout << "\n";
		for (int j = 0; j < (*((Mesh*)comp)).indices.size(); j++)
			std::cout << (*((Mesh*)comp)).indices[j] << " ";

	};

public:
	std::vector<std::pair<std::string, std::vector<void*>>> GUI_VARS()
	{
		std::vector<std::pair<std::string, std::vector<void*>>> res;



		res.push_back(std::make_pair("Colr", std::vector<void*>{ (void*)0x000001 , 0, &OnAddVer, (void*)0, &Color[0] }));

		res.push_back(std::make_pair("Colg", std::vector<void*>{ (void*)0x000001 , 0, nullptr, (void*)0, &Color[1] }));
																							
		res.push_back(std::make_pair("Colb", std::vector<void*>{ (void*)0x000001 , 0, nullptr, (void*)0, &Color[2] }));
																							
		res.push_back(std::make_pair("Cola", std::vector<void*>{ (void*)0x000001 , 0, nullptr, (void*)0, &Color[3] }));


		for (int j = 0; j < vertices.size(); j+=3)
		{
			res.push_back(std::make_pair("Ver" + std::to_string(j), std::vector<void*>{
				(void*)3, 
				&OnToggleVer, nullptr,
				(void*)-1,
				(void*)j,
				(void*)(j + 1),
				(void*)(j + 2)
				}));
			

		}
		return res;
	}
	bool isRender;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	int MeshId;
	
	float *Color;

	/// <summary>
	/// Vertex Buffer Object(Vertices Buffer)
	/// </summary>
	unsigned int VBO;
	/// <summary>
	/// Index Buffer Object(Verticy index buffer)
	/// </summary>
	unsigned int IBO;
	/// <summary>
	/// Vertex Array Object(Attrib Container)
	/// </summary>
	unsigned int VAO;


	virtual void Initialize(Object*obj)
	{
		this->obj = obj;
	}

	void SetMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, glm::vec4 color)
	{
		MeshCount++;
		MeshId = MeshCount;
		this->vertices = vertices;
		this->indices = indices;
		
		Color = (float*)malloc(sizeof(int) * 4);
		Color[0] = color.r;
		Color[1] = color.g;
		Color[2] = color.b;
		Color[3] = color.a;

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glNamedBufferData(VBO, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glNamedBufferData(IBO, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

		isRender = true;
	}
	void SetMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, float* color)
	{
		MeshCount++;
		MeshId = MeshCount;
		this->vertices = vertices;
		this->indices = indices;

		Color = color;

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glNamedBufferData(VBO, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glNamedBufferData(IBO, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

		isRender = true;
	}
	void OnUpdate()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{}

	void OnLastUpdate()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		//when increasing size of the glBufferSubData it breaks! so switch to glNamedBufferData
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glNamedBufferData(VBO, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glNamedBufferData(IBO, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

		glUniform4f(glGetUniformLocation(*CurrentShader<>, "custom_color"), Color[0], Color[1], Color[2], Color[3]);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

	}
	std::string ToMeshObj()
	{
		std::string result = "";

		for (int j = 0; j < vertices.size(); j+=3)
			result += "v "+std::to_string(vertices[j])+" "+std::to_string(vertices[j + 1])+" "+std::to_string(vertices[j+2])+"\n";
		result += "vt 0.000000 0.000000\n";
		result += "vn 0.000000 0.000000 0.000000\n";
		result += "g " + obj->name +"\n";
		result += "s off\n";

		for (int j = 0; j < indices.size(); j += 3)
			result += "f "+std::to_string(indices[j]+1) +"/1/1 "+ std::to_string(indices[j+1]+1) +"/1/1 " + std::to_string(indices[j+2]+1) +"/1/1\n";
		return result;
	}
	std::string ToObj()
	{
		std::string result = "";
		
		for (int j = 0; j < obj->GetComponents().size(); j++)
		{
			if (obj->GetComponents()[j]->operator std::string()[0] == 'M' &&
				obj->GetComponents()[j]->operator std::string()[1] == 'e' &&
				obj->GetComponents()[j]->operator std::string()[2] == 's' &&
				obj->GetComponents()[j]->operator std::string()[3] == 'h')
			{
				result += "\n\n#" + ((Mesh*)obj->GetComponents()[j])->operator std::string() +"\n\n";
				result += ((Mesh*)obj->GetComponents()[j])->ToMeshObj();
			}
		}
		return result;
	}
	operator std::string()
	{
		return (std::string)"Mesh("+ std::to_string(VAO)+")";
	}
};