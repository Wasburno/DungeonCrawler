// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	m_damageCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageCollision"));
	m_weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	RootComponent = m_weaponMesh;
	m_damageCollision->SetupAttachment(m_weaponMesh);
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	m_world = GetWorld();
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	checkDamageTrigger();
}

void AWeapon::triggerDamage()
{
	m_isTriggered = true;
	triggerCollision(true);
}


void AWeapon::triggerCollision(bool active)
{
	//if (nullptr != m_damageCollision) {
	//	active ?
	//	m_damageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly) :
	//	m_damageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}
}

void AWeapon::checkDamageTrigger()
{
	if (m_isTriggered) {
		if (m_triggerTimeElapsed >= m_performanceTime) {
			m_isTriggered = false;
			triggerCollision(false);
			m_triggerTimeElapsed = 0.0f;
		}
		else {
			m_triggerTimeElapsed += m_world->DeltaTimeSeconds;
		}
	}
}

