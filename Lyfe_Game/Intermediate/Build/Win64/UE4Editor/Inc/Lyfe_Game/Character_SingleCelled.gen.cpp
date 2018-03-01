// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/Character_SingleCelled.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCharacter_SingleCelled() {}
// Cross Module References
	LYFE_GAME_API UEnum* Z_Construct_UEnum_Lyfe_Game_EPlayerState();
	UPackage* Z_Construct_UPackage__Script_Lyfe_Game();
	LYFE_GAME_API UClass* Z_Construct_UClass_ACharacter_SingleCelled_NoRegister();
	LYFE_GAME_API UClass* Z_Construct_UClass_ACharacter_SingleCelled();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_AddHealth();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetCurrentHealth();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetMaxHealth();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetMovementSpeed();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetPlayerState();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetRotationSpeed();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetWeight();
	LYFE_GAME_API UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_SetPlayerState();
// End Cross Module References
	static UEnum* EPlayerState_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_Lyfe_Game_EPlayerState, Z_Construct_UPackage__Script_Lyfe_Game(), TEXT("EPlayerState"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EPlayerState(EPlayerState_StaticEnum, TEXT("/Script/Lyfe_Game"), TEXT("EPlayerState"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_Lyfe_Game_EPlayerState_CRC() { return 2633996927U; }
	UEnum* Z_Construct_UEnum_Lyfe_Game_EPlayerState()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_Lyfe_Game();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EPlayerState"), 0, Get_Z_Construct_UEnum_Lyfe_Game_EPlayerState_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EPlayerState::EDead", (int64)EPlayerState::EDead },
				{ "EPlayerState::EAlive", (int64)EPlayerState::EAlive },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_Lyfe_Game,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"EPlayerState",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"EPlayerState",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void ACharacter_SingleCelled::StaticRegisterNativesACharacter_SingleCelled()
	{
		UClass* Class = ACharacter_SingleCelled::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddHealth", (Native)&ACharacter_SingleCelled::execAddHealth },
			{ "GetCurrentHealth", (Native)&ACharacter_SingleCelled::execGetCurrentHealth },
			{ "GetMaxHealth", (Native)&ACharacter_SingleCelled::execGetMaxHealth },
			{ "GetMovementSpeed", (Native)&ACharacter_SingleCelled::execGetMovementSpeed },
			{ "GetPlayerState", (Native)&ACharacter_SingleCelled::execGetPlayerState },
			{ "GetRotationSpeed", (Native)&ACharacter_SingleCelled::execGetRotationSpeed },
			{ "GetWeight", (Native)&ACharacter_SingleCelled::execGetWeight },
			{ "SetPlayerState", (Native)&ACharacter_SingleCelled::execSetPlayerState },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_AddHealth()
	{
		struct Character_SingleCelled_eventAddHealth_Parms
		{
			float amount;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_amount = { UE4CodeGen_Private::EPropertyClass::Float, "amount", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventAddHealth_Parms, amount), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_amount,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Health" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Used to manipulate the cell's health\n@param amount can be positive or negative" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "AddHealth", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Character_SingleCelled_eventAddHealth_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetCurrentHealth()
	{
		struct Character_SingleCelled_eventGetCurrentHealth_Parms
		{
			float ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetCurrentHealth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Health" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Returns the cell's current health" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetCurrentHealth", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Character_SingleCelled_eventGetCurrentHealth_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetMaxHealth()
	{
		struct Character_SingleCelled_eventGetMaxHealth_Parms
		{
			float ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetMaxHealth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Health" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Returns the cell's maximum health" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetMaxHealth", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04080401, sizeof(Character_SingleCelled_eventGetMaxHealth_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetMovementSpeed()
	{
		struct Character_SingleCelled_eventGetMovementSpeed_Parms
		{
			float ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetMovementSpeed_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Movement" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Returns the cells movement speed" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetMovementSpeed", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04080401, sizeof(Character_SingleCelled_eventGetMovementSpeed_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetPlayerState()
	{
		struct Character_SingleCelled_eventGetPlayerState_Parms
		{
			EPlayerState ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Enum, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetPlayerState_Parms, ReturnValue), Z_Construct_UEnum_Lyfe_Game_EPlayerState, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_State" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Allows to acces the state of the player" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetPlayerState", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Character_SingleCelled_eventGetPlayerState_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetRotationSpeed()
	{
		struct Character_SingleCelled_eventGetRotationSpeed_Parms
		{
			float ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetRotationSpeed_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Movement" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Returns the cells rotation speed" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetRotationSpeed", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04080401, sizeof(Character_SingleCelled_eventGetRotationSpeed_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_GetWeight()
	{
		struct Character_SingleCelled_eventGetWeight_Parms
		{
			float ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventGetWeight_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_Movement" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Returns the cells wight\nPublic because this is also used to determine dominant cell for absorbing" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "GetWeight", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Character_SingleCelled_eventGetWeight_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ACharacter_SingleCelled_SetPlayerState()
	{
		struct Character_SingleCelled_eventSetPlayerState_Parms
		{
			EPlayerState newState;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_newState = { UE4CodeGen_Private::EPropertyClass::Enum, "newState", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Character_SingleCelled_eventSetPlayerState_Parms, newState), Z_Construct_UEnum_Lyfe_Game_EPlayerState, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_newState_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_newState,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_newState_Underlying,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "CELL_State" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
				{ "ToolTip", "Allows to set the state for the player" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_ACharacter_SingleCelled, "SetPlayerState", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Character_SingleCelled_eventSetPlayerState_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ACharacter_SingleCelled_NoRegister()
	{
		return ACharacter_SingleCelled::StaticClass();
	}
	UClass* Z_Construct_UClass_ACharacter_SingleCelled()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_ACharacter,
				(UObject* (*)())Z_Construct_UPackage__Script_Lyfe_Game,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_AddHealth, "AddHealth" }, // 3455737740
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetCurrentHealth, "GetCurrentHealth" }, // 2503757367
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetMaxHealth, "GetMaxHealth" }, // 238462636
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetMovementSpeed, "GetMovementSpeed" }, // 740291887
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetPlayerState, "GetPlayerState" }, // 517893933
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetRotationSpeed, "GetRotationSpeed" }, // 3234756799
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_GetWeight, "GetWeight" }, // 1760046720
				{ &Z_Construct_UFunction_ACharacter_SingleCelled_SetPlayerState, "SetPlayerState" }, // 381249298
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Navigation" },
				{ "IncludePath", "Character_SingleCelled.h" },
				{ "ModuleRelativePath", "Public/Character_SingleCelled.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ACharacter_SingleCelled>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ACharacter_SingleCelled::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
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
	IMPLEMENT_CLASS(ACharacter_SingleCelled, 2788200234);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACharacter_SingleCelled(Z_Construct_UClass_ACharacter_SingleCelled, &ACharacter_SingleCelled::StaticClass, TEXT("/Script/Lyfe_Game"), TEXT("ACharacter_SingleCelled"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACharacter_SingleCelled);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
