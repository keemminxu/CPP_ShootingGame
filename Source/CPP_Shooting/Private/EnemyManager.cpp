// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "CPP_ShootingGameModeBase.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	

	//Ÿ�̸� ���߱�
	GetWorld()->GetTimerManager().SetTimer(createTimer, this, &AEnemyManager::CreateEnemy, createTime, true, createTime);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	// - �����ð��� �ѹ��� "�� ����" �α׸� ��� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	currentTime += DeltaTime;
	// 2. ���� ����ð��� �����ð��� �ʰ��ߴٸ�
	if (currentTime > createTime)
	{
		currentTime = 0;
		// 3. �α����
		//PRINTLOG(TEXT("Create Enemy"));
		// ���� ����� �ʹ�.
		// ��ġ�� EnemyManager �� ��ġ
		
	}
}

void AEnemyManager::CreateEnemy()
{
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	
	//if (gameMode->GetState() != EGameState::Gameover)
	//{
	//	// Ÿ�̸� ����
	//	GetWorld()->GetTimerManager().ClearTimer(createTimer);
	//}
	
	// gamemode �� ���°� playing �� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation(), Param);
}
