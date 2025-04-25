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
ACALCPROJECT_API UClass* Z_Construct_UClass_ASynapse_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnedNeurons_MetaData[] = {
		{ "ModuleRelativePath", "Network.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshComponent_MetaData[] = {
		{ "Category", "Network" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Network.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SynapseClass_MetaData[] = {
		{ "Category", "Synapse" },
		{ "ModuleRelativePath", "Network.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_NeuronClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnedNeurons_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnedNeurons;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshComponent;
	static const UECodeGen_Private::FClassPropertyParams NewProp_SynapseClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetwork>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_NeuronClass = { "NeuronClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetwork, NeuronClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ANeurons_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeuronClass_MetaData), NewProp_NeuronClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_SpawnedNeurons_Inner = { "SpawnedNeurons", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ANeurons_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_SpawnedNeurons = { "SpawnedNeurons", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetwork, SpawnedNeurons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnedNeurons_MetaData), NewProp_SpawnedNeurons_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_MeshComponent = { "MeshComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetwork, MeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshComponent_MetaData), NewProp_MeshComponent_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ANetwork_Statics::NewProp_SynapseClass = { "SynapseClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetwork, SynapseClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ASynapse_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SynapseClass_MetaData), NewProp_SynapseClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANetwork_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_NeuronClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_SpawnedNeurons_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_SpawnedNeurons,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_MeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetwork_Statics::NewProp_SynapseClass,
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
		{ Z_Construct_UClass_ANetwork, ANetwork::StaticClass, TEXT("ANetwork"), &Z_Registration_Info_UClass_ANetwork, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetwork), 1305661058U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_1780899382(TEXT("/Script/aCalcProject"),
	Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_a1203_Documents_unreal_aCalcProject_Source_aCalcProject_Network_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
