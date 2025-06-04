// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "ImpactPoint.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UImpactPoint : public UBillboardComponent
{
	GENERATED_BODY()

public:
	TArray<TObjectPtr<UStaticMeshComponent>> BodyMeshesImpacted;
};