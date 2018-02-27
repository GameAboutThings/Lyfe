// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/Camera/Camera_Editor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCamera_Editor() {}
// Cross Module References
	LYFE_GAME_API UClass* Z_Construct_UClass_ACamera_Editor_NoRegister();
	LYFE_GAME_API UClass* Z_Construct_UClass_ACamera_Editor();
	ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
	UPackage* Z_Construct_UPackage__Script_Lyfe_Game();
// End Cross Module References
	void ACamera_Editor::StaticRegisterNativesACamera_Editor()
	{
	}
	UClass* Z_Construct_UClass_ACamera_Editor_NoRegister()
	{
		return ACamera_Editor::StaticClass();
	}
	UClass* Z_Construct_UClass_ACamera_Editor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_APlayerCameraManager,
				(UObject* (*)())Z_Construct_UPackage__Script_Lyfe_Game,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "Camera/Camera_Editor.h" },
				{ "ModuleRelativePath", "Public/Camera/Camera_Editor.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ACamera_Editor>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ACamera_Editor::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900288u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACamera_Editor, 2257290643);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACamera_Editor(Z_Construct_UClass_ACamera_Editor, &ACamera_Editor::StaticClass, TEXT("/Script/Lyfe_Game"), TEXT("ACamera_Editor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACamera_Editor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
