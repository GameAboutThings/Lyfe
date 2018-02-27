// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Lyfe_GameGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLyfe_GameGameModeBase() {}
// Cross Module References
	LYFE_GAME_API UClass* Z_Construct_UClass_ALyfe_GameGameModeBase_NoRegister();
	LYFE_GAME_API UClass* Z_Construct_UClass_ALyfe_GameGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Lyfe_Game();
// End Cross Module References
	void ALyfe_GameGameModeBase::StaticRegisterNativesALyfe_GameGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ALyfe_GameGameModeBase_NoRegister()
	{
		return ALyfe_GameGameModeBase::StaticClass();
	}
	UClass* Z_Construct_UClass_ALyfe_GameGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameModeBase,
				(UObject* (*)())Z_Construct_UPackage__Script_Lyfe_Game,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "Lyfe_GameGameModeBase.h" },
				{ "ModuleRelativePath", "Lyfe_GameGameModeBase.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ALyfe_GameGameModeBase>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ALyfe_GameGameModeBase::StaticClass,
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
	IMPLEMENT_CLASS(ALyfe_GameGameModeBase, 2772501699);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALyfe_GameGameModeBase(Z_Construct_UClass_ALyfe_GameGameModeBase, &ALyfe_GameGameModeBase::StaticClass, TEXT("/Script/Lyfe_Game"), TEXT("ALyfe_GameGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALyfe_GameGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
