// Copyright Les Andro�ds Associ�s. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FRoundedFlatNodesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ApplyEditorStyle();
};
