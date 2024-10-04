// Copyright Les Andro�ds Associ�s. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "RoundedFlatNodesSettings.generated.h"

/**
 * Configure the Rounded Flat Nodes plug-in.
 */
UCLASS(config = EditorPerProjectUserSettings)
class URoundedFlatNodesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	URoundedFlatNodesSettings();

#if WITH_EDITOR
	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;

	/**
	 * Called when a property on this object has been modified externally
	 *
	 * @param PropertyThatChanged the property that was modified
	 */
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	FSlateBrush* CreateHeaderBrush(float CornerRadius);
	FSlateBrush* CreateBodyBrush(float CornerRadius);

	/** Whether to use gradient on node header or not. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Use Gradient", meta = (ConfigRestartRequired = true))
	bool bHeaderUseGradient = true;

	/** Brightness of node header. Default: 0.25 */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Brightness", meta = (EditCondition = "!bHeaderUseGradient", ClampMin = "0", ClampMax = "1"))
	float HeaderBrightness = 0.25f;

	TMap<FString, FSlateBrush*> SlateBrushes;
};
