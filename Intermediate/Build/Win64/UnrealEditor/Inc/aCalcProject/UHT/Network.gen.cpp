// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "aCalcProject/Network.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetwork() {}

// Begin Cross Module References
ACALCPROJECT_API UClass* Z_Construct_UClass_ANetwork();
ACALCPROJECT_API UClass* Z_Construct_UClass_ANetwork_NoRegister();
ACALCPROJECT_API UClass* Z_Construct_UClass_ANeurons_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_aCalcProject();
// End Cross Module References

// Begin Class ANetwork
void ANetwork::StaticRegisterNativesANetwork()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANetwork);
UClass* Z_Construct_UClass_ANetwork_NoRegister()
{
	return ANetwork::StaticClass();
}
struct Z_Construct_UClass_ANetwork_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Network.h" },
		{ "ModuleRelativePath", "Network.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeuronClass_MetaData[] = {
		{ "Category", "Neuron" },
		{ "ModuleRelativePath", "Network.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_NeuronClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetwork>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_NeuronClass = { "NeuronClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetwork, NeuronClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ANeurons_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeuronClass_MetaData), NewProp_NeuronClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANetwork_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_NeuronClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetwork_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ANetwork_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_aCalcProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetwork_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANetwork_Statics::ClassParams = {
	&ANetwork::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ANetwork_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ANetwork_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetwork_Statics::Class_MetaDataParams), Z_Construct_UClass_ANetwork_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANetwork()
{
	if (!Z_Registration_Info_UClass_ANetwork.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANetwork.OuterSingleton, Z_Construct_UClass_ANetwork_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANetwork.OuterSingleton;
}
template<> ACALCPROJECT_API UClass* StaticClass<ANetwork>()
{
	return ANetwork::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANetwork);
ANetwork::~ANetwork() {}
// End Class ANetwork

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANetwork, ANetwork::StaticClass, TEXT("ANetwork"), &Z_Registration_Info_UClass_ANetwork, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetwork), 919754013U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_2552215937(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
