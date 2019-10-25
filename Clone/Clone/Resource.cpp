#include "stdafx.h"
#include "Resource.h"

LPWSTR copy_string(LPCWSTR value)
{
	if (IS_INTRESOURCE(value))
		return const_cast<LPWSTR>(value);

	int len = wcslen(value) + 1;
	LPWSTR copy = new WCHAR[len];
	memcpy(copy, value, sizeof(WCHAR) * len);
	return copy;
}

Resource::Resource(LPCWSTR lpType, LPWSTR lpName, LPVOID lpData, DWORD dwSize)
{
	this->lpType = copy_string(lpType);
	this->lpName = copy_string(lpName);
	this->lpData = lpData;
	this->dwSize = dwSize;
}

Resource::Resource(const Resource& src)
{
	this->lpType = copy_string(src.lpType);
	this->lpName = copy_string(src.lpName);
	this->lpData = src.lpData;
	this->dwSize = src.dwSize;
}

Resource::~Resource()
{
	if (!IS_INTRESOURCE(lpType))
		delete[] lpType;

	if (!IS_INTRESOURCE(lpName))
		delete[] lpName;
}

Resource& Resource::operator=(const Resource& rhs)
{
	if (&rhs != this)
	{
		Resource copy(rhs);

		using std::swap;
		swap(this->lpType, copy.lpType);
		swap(this->lpName, copy.lpName);
		swap(this->lpData, copy.lpData);
		swap(this->dwSize, copy.dwSize);
	}

	return *this;
}