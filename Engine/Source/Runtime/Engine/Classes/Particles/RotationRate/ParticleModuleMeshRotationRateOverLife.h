// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#pragma once
#include "Particles/RotationRate/ParticleModuleRotationRateBase.h"
#include "ParticleModuleMeshRotationRateOverLife.generated.h"

UCLASS(editinlinenew, hidecategories=Object, meta=(DisplayName = "Mesh Rotation Rate over Life"))
class UParticleModuleMeshRotationRateOverLife : public UParticleModuleRotationRateBase
{
	GENERATED_UCLASS_BODY()

	/**
	 *	The rotation rate desired.
	 *	The value is retrieved using the RelativeTime of the particle.
	 */
	UPROPERTY(EditAnywhere, Category=Rotation)
	struct FRawDistributionVector RotRate;

	/**
	 *	If true, scale the current rotation rate by the value retrieved.
	 *	Otherwise, set the rotation rate to the value retrieved.
	 */
	UPROPERTY(EditAnywhere, Category=Rotation)
	uint32 bScaleRotRate:1;

	//Begin UObject Interface
	virtual void	PostInitProperties() override;
	//End UObject Interface

	// Begin UParticleModule Interface
	virtual void Spawn(FParticleEmitterInstance* Owner, int32 Offset, float SpawnTime, FBaseParticle* ParticleBase) override;
	virtual void Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime) override;
	virtual void SetToSensibleDefaults(UParticleEmitter* Owner) override;
	virtual bool TouchesMeshRotation() const override { return true; }
	// End UParticleModule Interface
};



