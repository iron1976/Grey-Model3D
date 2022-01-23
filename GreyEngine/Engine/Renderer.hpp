#pragma once
#include <iostream>
#include <vector>

class MainRenderer
{
private:
	GLuint shader;

public:
	GLFWwindow* window;
	mat4 ortho = glm::ortho<float>(-1, 1, -1, 1);

	std::function<void()> BeginRender;
	std::function<void()> EndRender;
	MainRenderer()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		#pragma region GLEW&GLFW Initializing
		if (!glfwInit())
			exit(-1);


		window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(-2);
		}
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK)
			exit(-3);

		glfwSwapInterval(1);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthRangef(-5.0f, 5.0f);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glEnableVertexAttribArray(0);
		#pragma endregion

		BeginRender = [&]()
		#if !DEBUGCONSOLE 
			noexcept
		#endif
		{
			glClearColor(0.06f, 0.15f, 0.25f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwGetCursorPos(window, &this->Cursor.x, &this->Cursor.y);
			glUniformMatrix4fv(glGetUniformLocation(shader, "ortho"), 1, false, &ortho[0][0]);
		};
		EndRender = [&]()
		#if !DEBUGCONSOLE 
			noexcept
		#endif
		{
			glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(this->view));
			glUniform4f(glGetUniformLocation(shader, "lightColor"), LIGHT_COLOR.x, LIGHT_COLOR.y, LIGHT_COLOR.z, LIGHT_COLOR.w);
			glfwSwapBuffers(window);
			glfwPollEvents();
		};

		this->Cursor = CursorPosition(&view, &view_anglexyz);
	}
	void SetRendererShader(GLuint shader)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		this->shader = shader;
	}
	const bool inline IsMouseButtonPressed(int MouseButton)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return glfwGetMouseButton(window, MouseButton);
	}
	bool IsKeyPressed(int Button)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return glfwGetKey(window, Button);
	}
#pragma region Camera
	mat4 view = mat4(1.0f);
	vec3 view_anglexyz = vec3(0.0f, 0.0f, 0.0f);
	std::string GetMatrix(mat4 matrix)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		std::string result;
		for (int j = 0; j < 4; j++)
		{
			result += ("|");
			for (int x = 0; x < 4; x++)
				result += std::to_string(matrix[j][x]) + (std::string)" ";
			result += ("|\n");
		}
		return result;
	};

	void CameraResetRotation() 
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		for (int j = 0; j <= 2; j++)
		{
			for (int x = 0; x <= 2; x++)
				view[j][x] = 0;
		}
		view[0][0] = 1; view[1][1] = 1; view[2][2] = 1;
		view_anglexyz = vec3(0, 0, 0);
	}
	void CameraReset()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		view = mat4(1.0f);
		view_anglexyz = vec3(0, 0, 0);
	}
	void CameraRotate(float angle, const vec3& anglexyz)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		float newvalx = (view_anglexyz.x + (anglexyz.x * angle));
		float newvaly = (view_anglexyz.y + (anglexyz.y * angle));
		float newvalz = (view_anglexyz.z + (anglexyz.z * angle));
		view_anglexyz.x = newvalx > 359 ? fmod(newvalx, 360.0f) : newvalx < 0 ? 360.0f + newvalx : newvalx;
		view_anglexyz.y = newvaly > 359 ? fmod(newvaly, 360.0f) : newvaly < 0 ? 360.0f + newvaly : newvaly;
		view_anglexyz.z = newvalz > 359 ? fmod(newvalz, 360.0f) : newvalz < 0 ? 360.0f + newvalz : newvalz;
		//x Limitations
		view_anglexyz.x = view_anglexyz.x < 270 && view_anglexyz.x > 180 ? 270 : view_anglexyz.x > 90 && view_anglexyz.x < 180 ? 90 : view_anglexyz.x;

		if (anglexyz == vec3(1, 0, 0))
			if (view_anglexyz.x == 270)
				angle = -90;
			else if (view_anglexyz.x == 90)
				angle = 90;
		view = glm::rotate(view, glm::radians(angle), anglexyz);
	}
	void CameraSetRotation(const vec3& anglexyz)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		CameraResetRotation();
		CameraRotate(anglexyz.x, vec3(1, 0, 0));
		CameraRotate(anglexyz.y, vec3(0, 1, 0));
		CameraRotate(anglexyz.z, vec3(0, 0, 1));
	}

#pragma endregion
#pragma region Cursor
struct CursorPosition
{
public:
	CursorPosition(mat4* view, vec3* view_anglexyz) : view(view), view_anglexyz(view_anglexyz) {}
	CursorPosition(double x, double y, double z) : y(y), x(x), z(z) {};
	CursorPosition() : y(0), x(0) {};
	double y;
	double x;
	double z;
	mat4* view;
	vec3* view_anglexyz;
	vec3 ToWorldPoint() const
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		double zoomMagnification = view[0][3][3];
		return vec3((x - WIDTH / 2) / (WIDTH / 2) * zoomMagnification, (HEIGHT / 2 - y) / (HEIGHT / 2) * zoomMagnification, 0);
	};
	vec3 ToWorldPointZ() const
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		double zoomMagnification = view[0][3][3];
		double x = 0;
		double y = 0;
		double z = 0;
		if (view_anglexyz[0].x == 270)
		{
			x = (this->x - WIDTH / 2) / (WIDTH / 2);
			y = 0;
			z = (HEIGHT / 2 - this->y) / (HEIGHT / 2);
		}
		return vec3((x - WIDTH / 2) / (WIDTH / 2) * zoomMagnification, (HEIGHT / 2 - y) / (HEIGHT / 2) * zoomMagnification, z * zoomMagnification);
	};

	vec3 ToScreenPoint() const
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return vec3((x - WIDTH / 2) / (WIDTH / 2), (HEIGHT / 2 - y) / (HEIGHT / 2), 0);
	};

	vec3 To3DWorldPosition()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		//Probably most difficult part was here
		vec2 MousePos(this->ToWorldPoint().x, this->ToWorldPoint().y);
		vec3 result = vec3(0, 0, 0);
		result.x = cos(view_anglexyz[0].y * (3.14159f / 180.0f)) * MousePos.x
			+
			-sin(view_anglexyz[0].y * (3.14159f / 180.0f)) * -sin(view_anglexyz[0].x * (3.14159f / 180.0f)) * MousePos.y;

		result.y = cos(view_anglexyz[0].x * (3.14159f / 180.0f)) * MousePos.y
			;
		result.z = -sin(view_anglexyz[0].y * (3.14159f / 180.0f)) * MousePos.x
			+
			cos(view_anglexyz[0].y * (3.14159f / 180.0f)) * (sin(view_anglexyz[0].x * (3.14159f / 180.0f)) * MousePos.y);

		return result;

	}

	operator std::string() const 
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return std::to_string(x)
			+ (std::string)" " + std::to_string(y) + " " + std::to_string(z);
	}

};
CursorPosition Cursor;
#pragma endregion
#pragma region Rendering
private:
	void renderRAW(Object& object)
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		std::vector<Component*> Components = object.GetComponents();
		glUniform1i(glGetUniformLocation(*CurrentShader<>, "UseTex"), 0);

		for (auto i = Components.begin(); i != Components.end(); i++)
			(**i).OnUpdate();
		for (auto i = Components.begin(); i != Components.end(); i++)
			(**i).OnLastUpdate();
	}

public:
	void render(Object& object) 
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		if (object.GetComponent<Mirror>() != nullptr)
		{
			glClearColor(0.06f, 0.15f, 0.25f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (auto i : object.GetComponent<Mirror>()[0]->ObjectIDList())
				this->renderRAW(*ObjectList[i]);
			this->renderRAW(object);
			for (auto d : ObjectList)
				this->renderRAW(*d);

		}
		else
			this->renderRAW(object);

	}
#pragma endregion

	bool IsApplicationClosed()
	#if !DEBUGCONSOLE 
		noexcept
	#endif
	{
		return glfwWindowShouldClose(window);
	}
};