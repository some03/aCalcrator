// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/MyProjectGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyProjectGameModeBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
MYPROJECT_API UClass* Z_Construct_UClass_AMyProjectGameModeBase();
MYPROJECT_API UClass* Z_Construct_UClass_AMyProjectGameModeBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References

// Begin Class AMyProjectGameModeBase
void AMyProjectGameModeBase::StaticRegisterNativesAMyProjectGameModeBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyProjectGameModeBase);
UClass* Z_Construct_UClass_AMyProjectGameModeBase_NoRegister()
{
	return AMyProjectGameModeBase::StaticClass();
}
struct Z_Construct_UClass_AMyProjectGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MyProjectGameModeBase.h" },
		{ "ModuleRelativePath", "MyProjectGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyProjectGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMyProjectGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyProjectGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyProjectGameModeBase_Statics::ClassParams = {
	&AMyProjectGameModeBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyProjectGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyProjectGameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyProjectGameModeBase()
{
	if (!Z_Registration_Info_UClass_AMyProjectGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyProjectGameModeBase.OuterSingleton, Z_Construct_UClass_AMyProjectGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyProjectGameModeBase.OuterSingleton;
}
template<> MYPROJECT_API UClass* StaticClass<AMyProjectGameModeBase>()
{
	return AMyProjectGameModeBase::StaticClass();
}
AMyProjectGameModeBase::AMyProjectGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyProjectGameModeBase);
AMyProjectGameModeBase::~AMyProjectGameModeBase() {}
// End Class AMyProjectGameModeBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_MyProject_Source_MyProject_MyProjectGameModeBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyProjectGameModeBase, AMyProjectGameModeBase::StaticClass, TEXT("AMyProjectGameModeBase"), &Z_Registration_Info_UClass_AMyProjectGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyProjectGameModeBase), 1671415184U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_MyProject_Source_MyProject_MyProjectGameModeBase_h_945461007(TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_MyProject_Source_MyProject_MyProjectGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_MyProject_Source_MyProject_MyProjectGameModeBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
