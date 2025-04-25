// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "aCalcProject/Synapse.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSynapse() {}

// Begin Cross Module References
ACALCPROJECT_API UClass* Z_Construct_UClass_ASynapse();
ACALCPROJECT_API UClass* Z_Construct_UClass_ASynapse_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
UPackage* Z_Construct_UPackage__Script_aCalcProject();
// End Cross Module References

// Begin Class ASynapse
void ASynapse::StaticRegisterNativesASynapse()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASynapse);
UClass* Z_Construct_UClass_ASynapse_NoRegister()
{
	return ASynapse::StaticClass();
}
struct Z_Construct_UClass_ASynapse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Synapse.h" },
		{ "ModuleRelativePath", "Synapse.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spline_MetaData[] = {
		{ "Category", "Synapse" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Synapse.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LineMesh_MetaData[] = {
		{ "Category", "Synapse" },
		{ "ModuleRelativePath", "Synapse.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LineMaterial_MetaData[] = {
		{ "Category", "Synapse" },
		{ "ModuleRelativePath", "Synapse.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LineMaterialInstance_MetaData[] = {
		{ "Category", "Synapse" },
		{ "ModuleRelativePath", "Synapse.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Spline;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LineMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LineMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LineMaterialInstance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASynapse>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASynapse_Statics::NewProp_Spline = { "Spline", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASynapse, Spline), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spline_MetaData), NewProp_Spline_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASynapse_Statics::NewProp_LineMesh = { "LineMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASynapse, LineMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LineMesh_MetaData), NewProp_LineMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASynapse_Statics::NewProp_LineMaterial = { "LineMaterial", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASynapse, LineMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LineMaterial_MetaData), NewProp_LineMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASynapse_Statics::NewProp_LineMaterialInstance = { "LineMaterialInstance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASynapse, LineMaterialInstance), Z_Construct_UClass_UMaterialInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LineMaterialInstance_MetaData), NewProp_LineMaterialInstance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASynapse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASynapse_Statics::NewProp_Spline,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASynapse_Statics::NewProp_LineMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASynapse_Statics::NewProp_LineMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASynapse_Statics::NewProp_LineMaterialInstance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASynapse_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASynapse_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_aCalcProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASynapse_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASynapse_Statics::ClassParams = {
	&ASynapse::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASynapse_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASynapse_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASynapse_Statics::Class_MetaDataParams), Z_Construct_UClass_ASynapse_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASynapse()
{
	if (!Z_Registration_Info_UClass_ASynapse.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASynapse.OuterSingleton, Z_Construct_UClass_ASynapse_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASynapse.OuterSingleton;
}
template<> ACALCPROJECT_API UClass* StaticClass<ASynapse>()
{
	return ASynapse::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASynapse);
ASynapse::~ASynapse() {}
// End Class ASynapse

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Synapse_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASynapse, ASynapse::StaticClass, TEXT("ASynapse"), &Z_Registration_Info_UClass_ASynapse, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASynapse), 1799632902U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Synapse_h_3645712192(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Synapse_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Synapse_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
