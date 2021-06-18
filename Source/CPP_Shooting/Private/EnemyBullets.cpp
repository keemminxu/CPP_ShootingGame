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

	// ������Ʈ ���� ���̱�
	// 1. Box Collider
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollier"));
	RootComponent = sphereComp;
	// 2. �ܰ�
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
	
	// 1. ������ �ʿ��ϴ�.
	FVector vel = FVector::DownVector * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ�ʹ�.
	SetActorLocation(P, true);
}

void AEnemyBullets::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ε��� �༮�� Player�� �ƴ϶�� ó������ ����
	
	if (OtherActor->GetName().Contains(TEXT("Player")) == false)
	{
		return;
	}
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// �ε��� �༮�� Player ���
	auto player = Cast<APlayerCPP>(OtherActor);

	if (player)
	{
		// ���� ���� ���·� ��ȯ�ϰ� �ʹ�.
		gameMode->SetState(EGameState::Gameover);
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// ���� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy();
	Destroy();
}


