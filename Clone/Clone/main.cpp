#include "stdafx.h"
#include "ResourceHelper.h"

int main()
{
	try
	{
		std::vector<LPCWSTR> resourceTypes;
		resourceTypes.push_back(RT_ICON);
		resourceTypes.push_back(RT_GROUP_ICON);
		resourceTypes.push_back(RT_VERSION);
		
		auto resourceHelper = std::make_unique<ResourceHelper>(L"clone_from.exe");
		auto iconAndVersionInfoFromFile = resourceHelper->GetResources(resourceTypes);

		// 3rd argument is false by default
		// It means that it won't delete the existing resources
		// Currently, it is set to true, so it will delete all existing resources
		resourceHelper->SetResources(L"clone_to.exe", iconAndVersionInfoFromFile, true);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}