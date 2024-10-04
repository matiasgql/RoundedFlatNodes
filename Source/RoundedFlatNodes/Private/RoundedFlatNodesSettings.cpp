// Copyright Les Andro�ds Associ�s. All Rights Reserved.

#include "RoundedFlatNodesSettings.h"
#include "Materials/MaterialInstanceDynamic.h"

#define LOCTEXT_NAMESPACE "RoundedFlatNodes"

URoundedFlatNodesSettings::URoundedFlatNodesSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("RoundedFlatNodes");
}

#if WITH_EDITOR
FText URoundedFlatNodesSettings::GetSectionText() const
{
	return LOCTEXT("UserSettingsDisplayName", "Rounded Flat Nodes");
}

void URoundedFlatNodesSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		const FName NAME_HeaderBrightness = GET_MEMBER_NAME_CHECKED(URoundedFlatNodesSettings, HeaderBrightness);
		const FName PropertyName = PropertyChangedEvent.GetPropertyName();

		if (PropertyName == NAME_HeaderBrightness)
		{
			UObject* ResourceObject = SlateBrushes["HeaderBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);
		}
	}
}
#endif	// WITH_EDITOR

FSlateBrush* URoundedFlatNodesSettings::CreateHeaderBrush(float CornerRadius)
{
	FSlateBrush* SlateBrush = new FSlateBrush();
	
	const FString MaterialPath = bHeaderUseGradient ? FString("/RoundedFlatNodes/Materials/GradientBox.GradientBox") : FString("/RoundedFlatNodes/Materials/Box.Box");
	UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialPath);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	DynamicMaterial->SetVectorParameterValue("Color", FVector(HeaderBrightness, HeaderBrightness, HeaderBrightness));
	DynamicMaterial->AddToRoot();

	SlateBrush->SetResourceObject(DynamicMaterial);
	SlateBrushes.Add("HeaderBrush", SlateBrush);
	SlateBrush->DrawAs = ESlateBrushDrawType::RoundedBox;
	SlateBrush->OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	SlateBrush->OutlineSettings.CornerRadii = FVector4(CornerRadius, CornerRadius, 0, 0);

	return SlateBrush;
}

FSlateBrush* URoundedFlatNodesSettings::CreateBodyBrush(float CornerRadius)
{
	FSlateBrush* SlateBrush = new FSlateBrush();
	SlateBrush->DrawAs = ESlateBrushDrawType::RoundedBox;
	SlateBrush->OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	SlateBrush->OutlineSettings.CornerRadii = FVector4(CornerRadius, CornerRadius, CornerRadius, CornerRadius);
	SlateBrush->TintColor = FSlateColor(FLinearColor(0.0075f,0.0075f,0.0075f,0.75));

	return SlateBrush;
}

#undef LOCTEXT_NAMESPACE
