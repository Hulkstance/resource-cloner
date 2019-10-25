#pragma once

class ResourceHelper
{
private:
	std::wstring fileName;
	HMODULE module;

	static std::vector<Resource> resources;

	static bool EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);
	static bool EnumTypesFunc(HMODULE hModule, LPCWSTR lpType, LONG_PTR lParam);

public:
	ResourceHelper(std::wstring fileName);
	~ResourceHelper();
	std::vector<Resource> GetResources(std::vector<LPCWSTR>& types);
	void SetResources(std::wstring fileName, std::vector<Resource>& resources, bool overrideOldResources = false);
};
