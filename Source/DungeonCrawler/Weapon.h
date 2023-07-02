// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AWeapon : public AActor
{
  GENERATED_BODY()


  UPROPERTY(EditAnywhere)
  class UStaticMeshComponent* m_weaponMesh;

  UPROPERTY(EditAnywhere)
   class UWorld* m_world;

public:

   UPROPERTY(EditAnywhere, BlueprintReadWrite)
   class UCapsuleComponent* m_damageCollision;


public:

  AWeapon();

protected:

  virtual void
  BeginPlay() override;

public:

  virtual void
  Tick(float DeltaTime) override;

public:

  UFUNCTION(BlueprintCallable) void 
  triggerDamage();

private:
  void 
  triggerCollision(bool active);

  void 
  checkDamageTrigger();


public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float m_damage;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float m_performanceTime;

private:
  float m_triggerTimeElapsed;

public:
  UPROPERTY(BlueprintReadOnly)
  bool m_isTriggered;

};
