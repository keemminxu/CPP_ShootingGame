// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullets.h"
#include <Components/SphereComponent.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyBullets::AEnemyBullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 만들어서 붙이기
	// 1. Box Collider
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollier"));
	RootComponent = sphereComp;
	// 2. 외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AEnemyBullets::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullets::OnTriggerEnter);
}

// Called every frame
void AEnemyBullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 1. 방향이 필요하다.
	FVector vel = FVector::DownVector * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	SetActorLocation(P, true);
}

void AEnemyBullets::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 녀석이 Player가 아니라면 처리하지 말자
	
	if (OtherActor->GetName().Contains(TEXT("Player")) == false)
	{
		return;
	}
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// 부딪힌 녀석이 Player 라면
	auto player = Cast<APlayerCPP>(OtherActor);

	if (player)
	{
		// 게임 오버 상태로 전환하고 싶다.
		gameMode->SetState(EGameState::Gameover);
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// 폭발 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy();
	Destroy();
}


