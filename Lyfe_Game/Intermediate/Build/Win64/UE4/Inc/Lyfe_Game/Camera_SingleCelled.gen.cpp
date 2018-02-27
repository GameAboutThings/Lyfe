// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/Camera_SingleCelled.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCamera_SingleCelled() {}
// Cross Module References
	LYFE_GAME_API UClass* Z_Construct_UClass_ACamera_SingleCelled_NoRegister();
	LYFE_GAME_API UClass* Z_Construct_UClass_ACamera_SingleCelled();
	ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
	UPackage* Z_Construct_UPackage__Script_Lyfe_Game();
// End Cross Module References
	void ACamera_SingleCelled::StaticRegisterNativesACamera_SingleCelled()
	{
	}
	UClass* Z_Construct_UClass_ACamera_SingleCelled_NoRegister()
	{
		return ACamera_SingleCelled::StaticClass();
	}
	UClass* Z_Construct_UClass_ACamera_SingleCelled()
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
				{ "IncludePath", "Camera_SingleCelled.h" },
				{ "ModuleRelativePath", "Public/Camera_SingleCelled.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ACamera_SingleCelled>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ACamera_SingleCelled::StaticClass,
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
	IMPLEMENT_CLASS(ACamera_SingleCelled, 2378165890);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACamera_SingleCelled(Z_Construct_UClass_ACamera_SingleCelled, &ACamera_SingleCelled::StaticClass, TEXT("/Script/Lyfe_Game"), TEXT("ACamera_SingleCelled"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACamera_SingleCelled);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
