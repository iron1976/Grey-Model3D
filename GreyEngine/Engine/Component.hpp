#pragma once


class Object;

class Component
{

public:
	virtual void Initialize(Object* obj) = 0;
	/// <summary>
	/// Every Frame Called
	/// </summary>
#if DEBUGCONSOLE
	virtual void OnUpdate() = 0;
#else
	virtual void OnUpdate() noexcept = 0;
#endif
	/// <summary>
	/// Every Frame Called At Last
	/// </summary>
#if DEBUGCONSOLE
	virtual void OnLastUpdate() = 0;
#else
	virtual void OnLastUpdate() noexcept = 0;
#endif
	virtual operator std::string() = 0;
	/// <summary>
	/// 0: For how many data there is, 1: Function pointer, +1: Data
	/// </summary>
	/// <returns></returns>
	virtual std::vector<std::pair<std::string, std::vector<void*>>> GUI_VARS() = 0;
	virtual void Destroy() = 0;
};
