#pragma once


class Mirror : public Component
{
	void Destroy()
	{
		delete this;
	}
	Object* obj;


	char* ObjectIDs = (char*)(calloc(200, 1));

public:
	std::vector<std::pair<std::string, std::vector<void*>>>  GUI_VARS()
	{
		std::vector<std::pair<std::string, std::vector<void*>>> res;
		res.push_back(std::make_pair("IDs", std::vector<void*>{ (void*)0x000001, (void*)1, nullptr, (void*)0, this->ObjectIDs }));
		res.push_back(std::make_pair("SizX", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &this->Size.x }));
		res.push_back(std::make_pair("SizY", std::vector<void*>{ (void*)0x000001, nullptr, nullptr, (void*)0, &this->Size.y }));
		return res;
	}
	vec2 Size = vec2(1, 1);
	mat4* ScaleAuto;

	std::vector<int> ObjectIDList()
	{
		std::vector<int> result;
		std::string str = this->ObjectIDs;
		if (str[str.size() - 1] == ',')
			str[str.size() - 1] = ' ';
		std::string cropped = "";

		for (int j = 0; j < str.size(); j++)
		{
			if (j == 0)cropped = str;
			int resultVar;
			try
			{
				resultVar = std::stoi(cropped.substr(0, cropped.find_first_of(',')));
				if (resultVar >= ObjectList.size())//When ID out of bounds
					resultVar = obj->ObjectID;
			}
			catch (...)
			{
				return result;
			}
			if(resultVar != obj->ObjectID)
				result.push_back(resultVar);

			cropped = cropped.substr(cropped.find_first_of(',') + 1);


		}
		return result;
	}

	/// <summary>
	/// Texture Buffer Object
	/// </summary>
	unsigned int TBO;

	virtual void Initialize(Object* obj)
	{
		this->obj = obj;
	}
	void SetMirror(std::string ObjectIDs, mat4* ScaleAuto) 
	{
		this->ScaleAuto = ScaleAuto;
		memcpy(this->ObjectIDs, ObjectIDs.c_str(), ObjectIDs.size());
		
		glGenTextures(1, &TBO);
		glActiveTexture(GL_TEXTURE0 + TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OnUpdate() 
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		glViewport(0, 0, WIDTH, HEIGHT);
		/* Target texture */
		glBindTexture(GL_TEXTURE_2D, TBO);
		/* Copy screen to a 1024x1024 texture */
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, WIDTH, HEIGHT, 0);
		/* Restore viewport (in our case to 800x600)*/
		glViewport(0, 0, WIDTH, HEIGHT);
		glActiveTexture(GL_TEXTURE0 + TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);

		glUniform1i(glGetUniformLocation(*CurrentShader<>, "tex0"), TBO);
		glUniform1i(glGetUniformLocation(*CurrentShader<>, "UseTex"), 1);
		glUniform2f(glGetUniformLocation(*CurrentShader<>, "Invert"), (*this->ScaleAuto)[3][3] * Size.x, (*this->ScaleAuto)[3][3] * Size.y);
	}
	void OnLastUpdate()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{}

	operator std::string()
	{
		return (std::string)"Mirror(" + std::to_string(TBO) + ")";
	}
};