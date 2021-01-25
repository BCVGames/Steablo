// Copyright BCV Games LLC 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

UCLASS()
class STEABLOCPP_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

#pragma region Variables
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Root")
    class USceneComponent* enemyRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
    class UFloatingPawnMovement* moveComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MOvement")
    USkeletalMeshComponent* skeleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentHealth;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float maxHealth;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int expWorth;

	float attackRange;
	float attackTimer;
	float attackTime;
	bool canAttack;

private:
	bool bMouseDown;
#pragma endregion

#pragma region Functions
public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void EnemyClicked();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// <summary>
	///  Cause the enemy to take damage
	/// </summary>
	/// <param name="amtToMod">Amount to modify (send negative to do damage)</param>
	/// <param name="modder">Who is modifying this enemies health.</param>
	void ModifyHealth(float amtToMod, AActor* modder);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void OnDamageTakenBP(float amt);

private:
	void OnDeath();
#pragma endregion 
};
