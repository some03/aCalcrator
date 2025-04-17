// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "aCalcProject/Neurons.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNeurons() {}

// Begin Cross Module References
ACALCPROJECT_API UClass* Z_Construct_UClass_ANeurons();
ACALCPROJECT_API UClass* Z_Construct_UClass_ANeurons_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_aCalcProject();
// End Cross Module References

// Begin Class ANeurons
void ANeurons::StaticRegisterNativesANeurons()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANeurons);
UClass* Z_Construct_UClass_ANeurons_NoRegister()
{
	return ANeurons::StaticClass();
}
struct Z_Construct_UClass_ANeurons_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Neurons.h" },
		{ "ModuleRelativePath", "Neurons.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "Category", "Neurons" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Neurons.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANeurons>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANeurons_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANeurons, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANeurons_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANeurons_Statics::NewProp_Mesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANeurons_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ANeurons_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_aCalcProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANeurons_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANeurons_Statics::ClassParams = {
	&ANeurons::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ANeurons_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ANeurons_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANeurons_Statics::Class_MetaDataParams), Z_Construct_UClass_ANeurons_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANeurons()
{
	if (!Z_Registration_Info_UClass_ANeurons.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANeurons.OuterSingleton, Z_Construct_UClass_ANeurons_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANeurons.OuterSingleton;
}
template<> ACALCPROJECT_API UClass* StaticClass<ANeurons>()
{
	return ANeurons::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANeurons);
ANeurons::~ANeurons() {}
// End Class ANeurons

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Neurons_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANeurons, ANeurons::StaticClass, TEXT("ANeurons"), &Z_Registration_Info_UClass_ANeurons, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANeurons), 889463672U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Neurons_h_3104440278(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Neurons_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Neurons_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
