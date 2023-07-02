#include "DungeonCrawlerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"

//////////////////////////////////////////////////////////////////////////
// ADungeonCrawlerCharacter

ADungeonCrawlerCharacter::ADungeonCrawlerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}


void ADungeonCrawlerCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_world = GetWorld();
	m_hp = m_hpBase;
	m_healthPercentage = m_hp / m_hpBase;
}


void 
ADungeonCrawlerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	checkAction();
}

void 
ADungeonCrawlerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADungeonCrawlerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADungeonCrawlerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Attack",IE_Pressed,  this, &ADungeonCrawlerCharacter::attack);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADungeonCrawlerCharacter::roll);

}



void ADungeonCrawlerCharacter::checkAction()
{
	if (m_rolling) {
		iterateCycle(m_rolling, m_rollEffectiveTime, m_rollEffectiveTimeElapsed);
		FVector direction = (m_moveDirectionX * m_xMoveValue + m_moveDirectionY * m_yMoveValue);
		AddMovementInput(direction.GetSafeNormal(), 2);
	}

	if (m_isAttacking) {
		iterateCycle(m_isAttacking, m_attackEffectiveTime, m_attackTimeElapsed);
	}

	if (m_isInvulnerable) {
		iterateCycle(m_isInvulnerable, m_invulnerabilityTime, m_invulnerabilityElapsed);
	}
}


void 
ADungeonCrawlerCharacter::MoveForward(float Value)
{
	if(!m_rolling && !m_isAttacking && !m_isDead){
		if ((Controller != nullptr) && (Value != 0.0f)) {
			FRotator yawRotation = getYawRotation();
			m_moveDirectionX = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(m_moveDirectionX, Value);
		}

		m_xMoveValue = Value;
	}
}


void 
ADungeonCrawlerCharacter::MoveRight(float Value)
{
	if (!m_rolling && !m_isAttacking && !m_isDead) {
		if ( (Controller != nullptr) && (Value != 0.0f) ) {
			FRotator yawRotation = getYawRotation();
			m_moveDirectionY = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(m_moveDirectionY, Value);
		}

		m_yMoveValue = Value;
	}
}


void 
ADungeonCrawlerCharacter::attack()
{
	if (!m_rolling && !m_isAttacking && !m_isDead) {
		m_moveDirectionX = FVector::ZeroVector;
		m_moveDirectionY = FVector::ZeroVector;
		m_isAttacking = true;

		if (nullptr != m_weapon) {
			m_weapon->triggerDamage();
		}
	}
}


void 
ADungeonCrawlerCharacter::roll()
{
	float velocityMagnitude = GetVelocity().Size();
	if (velocityMagnitude > 0.0f && !m_isDead) {
		m_rolling = true;
	}
}


void ADungeonCrawlerCharacter::iterateCycle(bool& condition, float& time, float& elapsed)
{
	if (elapsed >= time) {
		condition = !condition;
		elapsed = 0.0f;
	}
	else {
		elapsed += m_world->GetDeltaSeconds();
	}
}


FRotator ADungeonCrawlerCharacter::getYawRotation()
{
	const FRotator Rotation = Controller->GetControlRotation();
	return FRotator (0, Rotation.Yaw, 0);
}


void ADungeonCrawlerCharacter::takeDamage(float damage)
{
	if (!m_isInvulnerable) {
		m_isInvulnerable = true;
		m_hp -= damage;
		m_hp = FMath::Clamp(m_hp, 0.0f, m_hpBase);

		m_healthPercentage = m_hp / m_hpBase;

		if (m_hp == 0) {
			m_isDead = true;
		}
	}
}
