// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	// DoActorSpawn1();
	// DoActorSpawn2();
	// DoActorSpawn3();
	DoActorSpawn4();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogGeometryHub, Warning, TEXT("property pointer %i, is valid %i"), PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Warning, TEXT("none property pointer %i, is valid %i"), NonePropertyActor != nullptr, IsValid(NonePropertyActor));

}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < 10; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
			ABaseGeomentryActor* Geometry = World->SpawnActor<ABaseGeomentryActor>(GeometryClass, GeometryTransform);
			if (Geometry)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
	
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < 10; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
			ABaseGeomentryActor* Geometry = World->SpawnActorDeferred<ABaseGeomentryActor>(GeometryClass, GeometryTransform);
			if (Geometry)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
	
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (const FGeometryPayLoad PayLoad : GeometryPayLoads)
		{
			ABaseGeomentryActor* Geometry = World->SpawnActorDeferred<ABaseGeomentryActor>(PayLoad.GeometryClass, PayLoad.InitTransform);
			if (Geometry)
			{
				Geometry->SetGeometryData(PayLoad.Data);
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Geometry->OnTimeFinished.AddUObject(this, &AGeometryHubActor::OnTimerChanged);
				Geometry->FinishSpawning(PayLoad.InitTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn4()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 300.0f, 300.0f));
	NonePropertyActor = World->SpawnActor<ABaseGeomentryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 700.0f, 300.0f));
	PropertyActor = World->SpawnActor<ABaseGeomentryActor>(GeometryClass, GeometryTransform);
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerChanged(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finish: %s"), *Actor->GetName());

	ABaseGeomentryActor* Geometry = Cast<ABaseGeomentryActor>(Actor);
	if (!Geometry) return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude: %f"), Geometry->GetGeometryData().Amplitude);
	Geometry->Destroy();
	// Geometry->SetLifeSpan(2.0f);
}

