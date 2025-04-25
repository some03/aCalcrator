// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Network.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ACALCPROJECT_Network_generated_h
#error "Network.generated.h already included, missing '#pragma once' in Network.h"
#endif
#define ACALCPROJECT_Network_generated_h

#define FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetwork(); \
	friend struct Z_Construct_UClass_ANetwork_Statics; \
public: \
	DECLARE_CLASS(ANetwork, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/aCalcProject"), NO_API) \
	DECLARE_SERIALIZER(ANetwork)


#define FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ANetwork(ANetwork&&); \
	ANetwork(const ANetwork&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetwork); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetwork); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANetwork) \
	NO_API virtual ~ANetwork();


#define FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_12_PROLOG
#define FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ACALCPROJECT_API UClass* StaticClass<class ANetwork>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
