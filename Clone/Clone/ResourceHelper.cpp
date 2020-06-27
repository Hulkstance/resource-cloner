#include "stdafx.h"
#include "ResourceHelper.h"

std::vector<Resource> ResourceHelper::resources;

ResourceHelper::ResourceHelper(std::wstring fileName)
{
	this->fileName = fileName;

	this->module = LoadLibraryExW(this->fileName.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE);
	if (!this->module)
	{
		throw std::runtime_error("Could not open source file.");
	}
}

bool ResourceHelper::EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
	if (!IS_INTRESOURCE(lpName))
	{
		std::wcout << lpName << std::endl;
	}
	else if (IS_INTRESOURCE(lpName))
	{
		std::cout << reinterpret_cast<int>(lpName) << std::endl;
	}

	HRSRC hResource = hResource = FindResourceW(hModule, lpName, lpType);

	if (!hResource)
	{
		return false;
	}

	DWORD dwSize = SizeofResource(hModule, hResource);
	HGLOBAL hGlobal = LoadResource(hModule, hResource);

	if (!hGlobal)
	{
		return false;
	}

	LPVOID lpResource = LockResource(hGlobal);

	if (!lpResource)
	{
		return false;
	}

	resources.push_back(Resource(lpType, lpName, hGlobal, dwSize));

	FreeResource(lpResource);

	return true;
}

std::vector<Resource> ResourceHelper::GetResources(std::vector<LPCWSTR>& types)
{
	resources.clear();

	for (LPCWSTR type : types)
	{
		EnumResourceNamesW(module, type, reinterpret_cast<ENUMRESNAMEPROCW>(EnumNamesFunc), 0);
	}

	return resources;
}

void ResourceHelper::SetResources(std::wstring fileName, std::vector<Resource>& resources, bool overrideOldResources)
{
	HANDLE handle = BeginUpdateResourceW(fileName.c_str(), overrideOldResources);

	if (!handle)
	{
		throw std::runtime_error("Could not open destination file.");
	}

	for (Resource resource : resources)
	{
		UpdateResourceW(handle, resource.lpType, (LPCWSTR)resource.lpName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), resource.lpData, resource.dwSize);
	}

	EndUpdateResourceW(handle, false);
}

ResourceHelper::~ResourceHelper()
{
	if (this->module)
	{
		FreeLibrary(this->module);
	}
}
