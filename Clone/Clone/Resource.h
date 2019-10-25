#pragma once

struct Resource
{
	LPCWSTR lpType;
	LPWSTR lpName;
	LPVOID lpData;
	DWORD dwSize;

	Resource(LPCWSTR lpType, LPWSTR lpName, LPVOID lpData, DWORD dwSize);
	Resource(const Resource& src);
	~Resource();
	Resource& operator=(const Resource& rhs);
};