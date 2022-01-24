#pragma once

int TransformCount = 0;

auto OnTogglePos = (std::function<void(int, int, int, std::vector<void*>)>)[&](const int& ObjectId, const int& CompId, const int& Index, const std::vector<void*>& selectedVar) {
	Grey3D::SelectedObject = ObjectId;
	Grey3D::SelectedComponent = CompId;
	if ((int)selectedVar[0] == 3)
	{
		Grey3D::SelectedType = "Pos0";

		Grey3D::SelectedData[0] = Index - 3;
		Grey3D::SelectedData[1] = Index - 2;
		Grey3D::SelectedData[2] = Index - 1;
	}
};

class Transform : public Component
{
	void Destroy()
	{
		delete this;
	}
	Object* obj;
public:
	std::vector<std::pair<std::string, std::vector<void*>>>  GUI_VARS()
	{

		std::vector<std::pair<std::string, std::vector<void*>>> res;

		res.push_back(std::make_pair("SizX", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &Scale.x }));
		res.push_back(std::make_pair("SizY", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &Scale.y }));
		res.push_back(std::make_pair("SizZ", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &Scale.z }));
		res.push_back(std::make_pair("Pos0", std::vector<void*>{ (void*)0x000003, &OnTogglePos, nullptr, (void*)0,
			&Position.x,
			&Position.y,
			&Position.z
		}));
		return res;
	}

	vec3 Position;
	vec3 Scale;

	mat4* AutoScale = nullptr;
	float layer = NULL;

	void Initialize(Object* obj) { TransformCount++; }
	void SetTransform(const vec3& Position, const vec3& Scale)
	{
		this->Position = Position;
		this->Scale = Scale;
	}
	void SetTransform(const vec3& Position, mat4* ScaleAuto)
	{
		this->Position = Position;
		AutoScale = ScaleAuto;
	}
	void SetTransform(const vec3& Position, const vec3& Scale, const float layer)
	{
		this->SetTransform(Position, Scale);
		this->layer = layer;
	}

	void OnUpdate() 
	#if !DEBUGCONSOLE 
			noexcept
	#endif
	{

		glUniform3f(glGetUniformLocation(*CurrentShader<>, "objectPosition"), Position.x, Position.y, -Position.z);
		if(AutoScale == nullptr)
			glUniform3f(glGetUniformLocation(*CurrentShader<>, "objectScale"), Scale.x, Scale.y, Scale.z);
		else
			glUniform3f(glGetUniformLocation(*CurrentShader<>, "objectScale"), ((*AutoScale)[3][3]), ((*AutoScale)[3][3]), ((*AutoScale)[3][3]));

	}

	void OnLastUpdate()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{}

	operator std::string()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return "Transform("+std::to_string(TransformCount)+")";
	}
};

