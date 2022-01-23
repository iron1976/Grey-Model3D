#pragma once

template<typename T>
std::string EncodeObj(T* object)
{
	std::string encodedObj = "";
	for (int j = 0; j < sizeof(T); j++)
		encodedObj += std::to_string((int)*(char*)&object[j]) + "|";

	return encodedObj;
}
template<typename T>
T DecodeObj(std::string encodedObj)
{
	std::string cropped = "";

	char* bytes = (char*)calloc(1, sizeof(T));
	for (int j = 0; j < sizeof(T); j++)
	{
		if (j == 0)cropped = encodedObj;

		bytes[j] = std::stoi(cropped.substr(0, cropped.find_first_of('|')));
		cropped = cropped.substr(cropped.find_first_of('|') + 1);

	}
	T result;
	memcpy((char*)&result, bytes, sizeof(T));
	return result;
}

class Texture : public Component
{
	void Destroy()
	{
		delete path;
		delete this;
	}
	Object* obj;
	std::function<void(void*)> OnAddTex = (std::function<void(void*)>)[&](void* comp) {
		SetTexture(path);
		std::cout << path;
	};

public:
	vec2 Size = vec2(1,1);

	/// <summary>
	/// Texture Buffer Object
	/// </summary>
	unsigned int TBO;
	char* path = (char*) (calloc(200,1));
	std::vector<std::pair<std::string, std::vector<void*>>>  GUI_VARS()
	{
		std::vector<std::pair<std::string, std::vector<void*>>> res;
		
		res.push_back(std::make_pair("Path", std::vector<void*>{ (void*)0x000001, (void*)1, &OnAddTex, (void*)0, path }));
		res.push_back(std::make_pair("SizX", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &Size.x }));
		res.push_back(std::make_pair("SizY", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &Size.y }));
		return res;
	}

	virtual void Initialize(Object* obj)
	{
		this->obj = obj;
	}
	void SetTexture(char* path)
	{
		int width;
		int height;

		unsigned char* bytes = stbi_load(path, &width, &height, nullptr, 4);


		if (bytes == nullptr)
			return;

		glGenTextures(1, &TBO);
		glActiveTexture(GL_TEXTURE0+TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (bytes)
			stbi_image_free(bytes);
	}
	void SetTexture(const char* path)
	{
		int width;
		int height;

		unsigned char* bytes = stbi_load(path, &width, &height, nullptr, 4);
		if (bytes == nullptr)
			return;

		glGenTextures(1, &TBO);
		glActiveTexture(GL_TEXTURE0 + TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (bytes)
			stbi_image_free(bytes);
	}

	void OnUpdate()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{

		glActiveTexture(GL_TEXTURE0 + TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);
		glUniform1i(glGetUniformLocation(*CurrentShader<>, "tex0"), TBO);
		glUniform1i(glGetUniformLocation(*CurrentShader<>, "UseTex"), 1);
		glUniform2f(glGetUniformLocation(*CurrentShader<>, "Invert"), Size.x, Size.y);
	}

	virtual void OnLastUpdate() 
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{}

	operator std::string()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return (std::string)"Texture(" + std::to_string(TBO) + ")";
	}
};