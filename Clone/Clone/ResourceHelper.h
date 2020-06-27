#pragma once

#include "Resource.h"

class ResourceHelper
{
private:
	/// <summary>
	/// Source file path.
	/// </summary>
	std::wstring fileName;
	
	/// <summary>
	/// Source file mapped module.
	/// </summary>
	HMODULE module;

	static std::vector<Resource> resources;

	static bool EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="fileName">The source file path.</param>
	/// <returns>The instantiated object.</returns>
	ResourceHelper(std::wstring fileName);
	~ResourceHelper();

	/// <summary>
	/// Gets specified resources from a source file.
	/// </summary>
	/// <param name="types">The specified resource types.</param>
	/// <returns>The resources.</returns>
	std::vector<Resource> GetResources(std::vector<LPCWSTR>& types);

	/// <summary>
	/// Replaces destination file resources with specified ones.
	/// </summary>
	/// <param name="fileName">The destination file path.</param>
	/// <param name="resources">The specified resource types.</param>
	/// <param name="overrideOldResources">Set to true to delete existing resources. It is false by default.</param>
	void SetResources(std::wstring fileName, std::vector<Resource>& resources, bool overrideOldResources = false);
};
