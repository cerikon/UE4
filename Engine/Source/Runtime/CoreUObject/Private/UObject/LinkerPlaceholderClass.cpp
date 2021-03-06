// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CoreUObjectPrivate.h"
#include "LinkerPlaceholderClass.h"

//------------------------------------------------------------------------------
ULinkerPlaceholderClass::ULinkerPlaceholderClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//------------------------------------------------------------------------------
IMPLEMENT_CORE_INTRINSIC_CLASS(ULinkerPlaceholderClass, UClass, 
	{
		Class->ClassAddReferencedObjects = &ULinkerPlaceholderClass::AddReferencedObjects;
		
	// @TODO: use the Class->Emit...() functions here to aid garbage 
	//        collection, so it has information on what class variables 
	//        hold onto UObject references
	}
);

//------------------------------------------------------------------------------
void ULinkerPlaceholderClass::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	ULinkerPlaceholderClass* This = CastChecked<ULinkerPlaceholderClass>(InThis);
	//... 
	Super::AddReferencedObjects(InThis, Collector);
}

//------------------------------------------------------------------------------
void ULinkerPlaceholderClass::PostInitProperties()
{
	Super::PostInitProperties();
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		// Default__LinkerPlaceholderClass uses its own AddReferencedObjects function.
		ClassAddReferencedObjects = &ULinkerPlaceholderClass::AddReferencedObjects;
	}
}

//------------------------------------------------------------------------------
void ULinkerPlaceholderClass::BeginDestroy()
{
#if USE_DEFERRED_DEPENDENCY_CHECK_VERIFICATION_TESTS
	check(IsMarkedResolved() || HasAnyFlags(RF_ClassDefaultObject));
	check(!HasKnownReferences());
#endif // USE_DEFERRED_DEPENDENCY_CHECK_VERIFICATION_TESTS

	// by this point, we really shouldn't have any properties left (they should 
	// have all got replaced), but just in case (so things don't blow up with a
	// missing class)...
	ResolveAllPlaceholderReferences(UObject::StaticClass());

	Super::BeginDestroy();
}

//------------------------------------------------------------------------------
void ULinkerPlaceholderClass::Bind()
{
	ClassConstructor = InternalConstructor<ULinkerPlaceholderClass>;
#if WITH_HOT_RELOAD_CTORS
	ClassVTableHelperCtorCaller = InternalVTableHelperCtorCaller<ULinkerPlaceholderClass>;
#endif // WITH_HOT_RELOAD_CTORS
	Super::Bind();

	ClassAddReferencedObjects = &ULinkerPlaceholderClass::AddReferencedObjects;
}


