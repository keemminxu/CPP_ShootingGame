// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.h"
#include "EnemyFire.h"
#include "EnemyMove.h"
#include "EnemyBullets.h"
#include <Components/ArrowComponent.h>


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 만들어서 붙이기
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. 외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 3. 총구
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(boxComp);

	enemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));
	enemyFire = CreateDefaultSubobject<UEnemyFire>(TEXT("EnemyFire"));

	

	// 총알을 로드해서 붙여주자
	ConstructorHelpers::FClassFinder<AEnemyBullets> TempBullet(TEXT("Blueprint'/Game/Blueprints/BP_EnemyBullets.BP_EnemyBullets_C'"));

	if (TempBullet.Succeeded())
	{
		enemyFire->bulletFactory = TempBullet.Class;
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
	

	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// 다른 물체와 겹쳤을 때 호출되는 이벤트 함수
// 갸도 죽고 나도 죽게 하자
//void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	
//}


