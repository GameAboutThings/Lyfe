// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef LYFE_GAME_Character_SingleCelled_generated_h
#error "Character_SingleCelled.generated.h already included, missing '#pragma once' in Character_SingleCelled.h"
#endif
#define LYFE_GAME_Character_SingleCelled_generated_h

#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetPlayerState) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EPlayerState*)Z_Param__Result=this->GetPlayerState(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetPlayerState) \
	{ \
		P_GET_ENUM(EPlayerState,Z_Param_newState); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetPlayerState(EPlayerState(Z_Param_newState)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_amount); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->AddHealth(Z_Param_amount); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCurrentHealth) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetCurrentHealth(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWeight) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetWeight(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMaxHealth) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetMaxHealth(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMovementSpeed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetMovementSpeed(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRotationSpeed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetRotationSpeed(); \
		P_NATIVE_END; \
	}


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetPlayerState) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EPlayerState*)Z_Param__Result=this->GetPlayerState(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetPlayerState) \
	{ \
		P_GET_ENUM(EPlayerState,Z_Param_newState); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetPlayerState(EPlayerState(Z_Param_newState)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_amount); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->AddHealth(Z_Param_amount); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCurrentHealth) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetCurrentHealth(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWeight) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetWeight(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMaxHealth) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetMaxHealth(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMovementSpeed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetMovementSpeed(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRotationSpeed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetRotationSpeed(); \
		P_NATIVE_END; \
	}


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACharacter_SingleCelled(); \
	friend LYFE_GAME_API class UClass* Z_Construct_UClass_ACharacter_SingleCelled(); \
public: \
	DECLARE_CLASS(ACharacter_SingleCelled, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Lyfe_Game"), NO_API) \
	DECLARE_SERIALIZER(ACharacter_SingleCelled) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_INCLASS \
private: \
	static void StaticRegisterNativesACharacter_SingleCelled(); \
	friend LYFE_GAME_API class UClass* Z_Construct_UClass_ACharacter_SingleCelled(); \
public: \
	DECLARE_CLASS(ACharacter_SingleCelled, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Lyfe_Game"), NO_API) \
	DECLARE_SERIALIZER(ACharacter_SingleCelled) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACharacter_SingleCelled(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACharacter_SingleCelled) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACharacter_SingleCelled); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACharacter_SingleCelled); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACharacter_SingleCelled(ACharacter_SingleCelled&&); \
	NO_API ACharacter_SingleCelled(const ACharacter_SingleCelled&); \
public:


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACharacter_SingleCelled(ACharacter_SingleCelled&&); \
	NO_API ACharacter_SingleCelled(const ACharacter_SingleCelled&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACharacter_SingleCelled); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACharacter_SingleCelled); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ACharacter_SingleCelled)


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_PRIVATE_PROPERTY_OFFSET
#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_17_PROLOG
#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_PRIVATE_PROPERTY_OFFSET \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_RPC_WRAPPERS \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_INCLASS \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_PRIVATE_PROPERTY_OFFSET \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_INCLASS_NO_PURE_DECLS \
	Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Lyfe_Game_Source_Lyfe_Game_Public_Character_SingleCelled_h


#define FOREACH_ENUM_EPLAYERSTATE(op) \
	op(EPlayerState::EDead) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
