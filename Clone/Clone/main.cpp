#include "stdafx.h"
#include "ResourceHelper.h"

int main()
{
	// NOTE: BeginUpdateResourceW requires full path
	wchar_t sourcePath[] = L"E:\\GitHub\\resource-cloner\\Clone\\Debug\\clone_from.exe";
	wchar_t destinationPath[] = L"E:\\GitHub\\resource-cloner\\Clone\\Debug\\clone_to.exe";

	try
	{
		// The resource types to copy
		std::vector<LPCWSTR> resourceTypes;
		resourceTypes.push_back(RT_ICON);
		resourceTypes.push_back(RT_GROUP_ICON);
		resourceTypes.push_back(RT_VERSION);
		
		// Get source file resources
		auto helper = std::make_unique<ResourceHelper>(sourcePath);
		auto resources = helper->GetResources(resourceTypes);

		// Replaces destination file resources with specified ones
		helper->SetResources(destinationPath, resources, true);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}