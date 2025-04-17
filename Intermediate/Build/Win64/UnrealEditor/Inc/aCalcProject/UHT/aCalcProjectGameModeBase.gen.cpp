// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "aCalcProject/aCalcProjectGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeaCalcProjectGameModeBase() {}

// Begin Cross Module References
ACALCPROJECT_API UClass* Z_Construct_UClass_AaCalcProjectGameModeBase();
ACALCPROJECT_API UClass* Z_Construct_UClass_AaCalcProjectGameModeBase_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_aCalcProject();
// End Cross Module References

// Begin Class AaCalcProjectGameModeBase
void AaCalcProjectGameModeBase::StaticRegisterNativesAaCalcProjectGameModeBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AaCalcProjectGameModeBase);
UClass* Z_Construct_UClass_AaCalcProjectGameModeBase_NoRegister()
{
	return AaCalcProjectGameModeBase::StaticClass();
}
struct Z_Construct_UClass_AaCalcProjectGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "aCalcProjectGameModeBase.h" },
		{ "ModuleRelativePath", "aCalcProjectGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AaCalcProjectGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_aCalcProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::ClassParams = {
	&AaCalcProjectGameModeBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AaCalcProjectGameModeBase()
{
	if (!Z_Registration_Info_UClass_AaCalcProjectGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AaCalcProjectGameModeBase.OuterSingleton, Z_Construct_UClass_AaCalcProjectGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AaCalcProjectGameModeBase.OuterSingleton;
}
template<> ACALCPROJECT_API UClass* StaticClass<AaCalcProjectGameModeBase>()
{
	return AaCalcProjectGameModeBase::StaticClass();
}
AaCalcProjectGameModeBase::AaCalcProjectGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AaCalcProjectGameModeBase);
AaCalcProjectGameModeBase::~AaCalcProjectGameModeBase() {}
// End Class AaCalcProjectGameModeBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_aCalcProjectGameModeBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AaCalcProjectGameModeBase, AaCalcProjectGameModeBase::StaticClass, TEXT("AaCalcProjectGameModeBase"), &Z_Registration_Info_UClass_AaCalcProjectGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AaCalcProjectGameModeBase), 2016815749U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_aCalcProjectGameModeBase_h_2494349921(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_aCalcProjectGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_aCalcProjectGameModeBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
