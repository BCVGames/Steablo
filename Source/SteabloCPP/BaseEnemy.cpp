// Copyright BCV Games LLC 2020


#include "BaseEnemy.h"
#include "SteabloCharacter.h"
#include <GameFramework/FloatingPawnMovement.h>

#include "Items/ItemManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup our components
	enemyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(enemyRootComponent);

	skeleMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	skeleMeshComponent->SetupAttachment(enemyRootComponent);
    moveComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

	currentHealth = maxHealth = 100.0f;
	expWorth = FMath::RandRange(100, 300);
	bMouseDown = false;
	canAttack = true;
	attackRange = 200.f;
	attackTime = 1.f;
	attackTimer = 0.f;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	//skeleMeshComponent->OnClicked.AddDynamic(this, &ABaseEnemy::OnPressed);
	//skeleMeshComponent->OnReleased.AddDynamic(this, &ABaseEnemy::OnReleased);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	attackTimer += DeltaTime;

	if (false == canAttack && attackTimer >= attackTime)
	{
		attackTimer = 0.f;
		canAttack = true;
	}

	if (canAttack)
	{
		// Distance check for the player, can we melee it?
		ASteabloCharacter* playerActor = Cast<ASteabloCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		float const distance = FVector::Dist(this->GetActorLocation(), playerActor->GetActorLocation());

		if (distance <= attackRange)
		{
			canAttack = false;
			playerActor->ModifyHealth(-2.f);
		}
	}


}

void ABaseEnemy::EnemyClicked()
{
    ASteabloCharacter* playerActor = Cast<ASteabloCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (playerActor != nullptr)
    {
        //playerActor->SetTargetItem(this);
    }
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::ModifyHealth(float amtToMod, AActor* modder)
{
	currentHealth += amtToMod;
	if (amtToMod < 0.0f)
	{
		// Let BP know we took some amount of damage (negated because it came in negative since we can use this function to heal as well)
		OnDamageTakenBP(-amtToMod);
	}

	currentHealth = FMath::Clamp(currentHealth, 0.0f, maxHealth);

	if (currentHealth == 0.0f)
	{
		ASteabloCharacter* killer = Cast<ASteabloCharacter>(modder);
		if (killer)
		{
			killer->ModifyExp(expWorth);
		}
		OnDeath();
	}
}

float ABaseEnemy::GetHealthPercent()
{
	return currentHealth / maxHealth;
}

void ABaseEnemy::OnDeath()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemManager::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		AItemManager* itemMgr = Cast<AItemManager>(actor);

		if (itemMgr)
		{
			itemMgr->SpawnItem(GetActorLocation());
		}
		break;
	}

	Destroy();
}

