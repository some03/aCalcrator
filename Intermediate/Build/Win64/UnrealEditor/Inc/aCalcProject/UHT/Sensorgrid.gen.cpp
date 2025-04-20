// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "aCalcProject/Sensorgrid.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSensorgrid() {}

// Begin Cross Module References
ACALCPROJECT_API UClass* Z_Construct_UClass_ASensorgrid();
ACALCPROJECT_API UClass* Z_Construct_UClass_ASensorgrid_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_aCalcProject();
// End Cross Module References

// Begin Class ASensorgrid
void ASensorgrid::StaticRegisterNativesASensorgrid()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASensorgrid);
UClass* Z_Construct_UClass_ASensorgrid_NoRegister()
{
	return ASensorgrid::StaticClass();
}
struct Z_Construct_UClass_ASensorgrid_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Sensorgrid.h" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rows_MetaData[] = {
		{ "Category", "Sensorgrid" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cols_MetaData[] = {
		{ "Category", "Sensorgrid" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CellSize_MetaData[] = {
		{ "Category", "Sensorgrid" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlaneMeshAsset_MetaData[] = {
		{ "Category", "Sensorgrid" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd""e\xef\xbf\xbdZ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\x83T\xef\xbf\xbd""C\xef\xbf\xbdY\xef\xbf\xbdiUnreal\xef\xbf\xbdP\xef\xbf\xbd\xca\x81j\n" },
#endif
		{ "ModuleRelativePath", "Sensorgrid.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd""e\xef\xbf\xbdZ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\x83T\xef\xbf\xbd""C\xef\xbf\xbdY\xef\xbf\xbdiUnreal\xef\xbf\xbdP\xef\xbf\xbd\xca\x81j" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshComponentClass_MetaData[] = {
		{ "Category", "Sensorgrid" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CellComponents_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CellMaterials_MetaData[] = {
		{ "ModuleRelativePath", "Sensorgrid.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Rows;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Cols;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CellSize;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlaneMeshAsset;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MeshComponentClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BaseMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CellComponents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CellComponents;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CellMaterials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CellMaterials;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASensorgrid>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_Rows = { "Rows", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, Rows), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rows_MetaData), NewProp_Rows_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_Cols = { "Cols", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, Cols), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cols_MetaData), NewProp_Cols_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellSize = { "CellSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, CellSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CellSize_MetaData), NewProp_CellSize_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_PlaneMeshAsset = { "PlaneMeshAsset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, PlaneMeshAsset), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlaneMeshAsset_MetaData), NewProp_PlaneMeshAsset_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_MeshComponentClass = { "MeshComponentClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, MeshComponentClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshComponentClass_MetaData), NewProp_MeshComponentClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_BaseMaterial = { "BaseMaterial", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, BaseMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseMaterial_MetaData), NewProp_BaseMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellComponents_Inner = { "CellComponents", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellComponents = { "CellComponents", nullptr, (EPropertyFlags)0x0010008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, CellComponents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CellComponents_MetaData), NewProp_CellComponents_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellMaterials_Inner = { "CellMaterials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellMaterials = { "CellMaterials", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASensorgrid, CellMaterials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CellMaterials_MetaData), NewProp_CellMaterials_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASensorgrid_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_Rows,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_Cols,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_PlaneMeshAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_MeshComponentClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_BaseMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellComponents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellMaterials_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASensorgrid_Statics::NewProp_CellMaterials,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASensorgrid_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASensorgrid_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_aCalcProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASensorgrid_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASensorgrid_Statics::ClassParams = {
	&ASensorgrid::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASensorgrid_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASensorgrid_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASensorgrid_Statics::Class_MetaDataParams), Z_Construct_UClass_ASensorgrid_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASensorgrid()
{
	if (!Z_Registration_Info_UClass_ASensorgrid.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASensorgrid.OuterSingleton, Z_Construct_UClass_ASensorgrid_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASensorgrid.OuterSingleton;
}
template<> ACALCPROJECT_API UClass* StaticClass<ASensorgrid>()
{
	return ASensorgrid::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASensorgrid);
ASensorgrid::~ASensorgrid() {}
// End Class ASensorgrid

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Sensorgrid_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASensorgrid, ASensorgrid::StaticClass, TEXT("ASensorgrid"), &Z_Registration_Info_UClass_ASensorgrid, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASensorgrid), 3883965726U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Sensorgrid_h_1064905512(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Sensorgrid_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Sensorgrid_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
