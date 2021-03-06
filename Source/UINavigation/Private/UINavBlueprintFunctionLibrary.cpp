﻿// Copyright (C) 2018 Gonçalo Marques - All Rights Reserved

#include "UINavBlueprintFunctionLibrary.h"
#include "Sound/SoundClass.h"
#include "GameFramework/GameUserSettings.h"
#include "UINavSettings.h"

void UUINavBlueprintFunctionLibrary::SetSoundClassVolume(USoundClass * TargetClass, float NewVolume)
{
	if (TargetClass == nullptr) return;
	TargetClass->Properties.Volume = NewVolume;
}

float UUINavBlueprintFunctionLibrary::GetSoundClassVolume(USoundClass * TargetClass)
{
	if (TargetClass == nullptr) return -1.f;
	return TargetClass->Properties.Volume;
}

void UUINavBlueprintFunctionLibrary::SetPostProcessSettings(FString Variable, FString Value)
{
	if (!GConfig)return;
	FString PostProcess = TEXT("PostProcessQuality@");
	PostProcess.Append(FString::FromInt(GEngine->GameUserSettings->GetPostProcessingQuality()));
	GConfig->SetString(
		*PostProcess,
		*Variable,
		*Value,
		GScalabilityIni
	);
}

FString UUINavBlueprintFunctionLibrary::GetPostProcessSettings(FString Variable)
{
	if (!GConfig) return FString();

	FString ValueReceived;
	FString PostProcess = TEXT("PostProcessQuality@");
	PostProcess.Append(FString::FromInt(GEngine->GameUserSettings->GetPostProcessingQuality()));
	GConfig->GetString(
		*PostProcess,
		*Variable,
		ValueReceived,
		GScalabilityIni
	);
	return ValueReceived;
}

void UUINavBlueprintFunctionLibrary::ResetInputSettings()
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	UUINavSettings *MySettings = GetMutableDefault<UUINavSettings>();
	Settings->ActionMappings = MySettings->ActionMappings;
	Settings->AxisMappings = MySettings->AxisMappings;
	Settings->SaveConfig();
	Settings->ForceRebuildKeymaps();
}

bool UUINavBlueprintFunctionLibrary::IsGamepadConnected()
{
	return FSlateApplication::Get().IsGamepadAttached();
}