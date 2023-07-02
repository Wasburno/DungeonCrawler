#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonCrawlerCharacter.generated.h"

UCLASS(config=Game)

class ADungeonCrawlerCharacter : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AWeapon* m_weapon;

public:
	ADungeonCrawlerCharacter();

  virtual void
  Tick(float DeltaTime) override;

	/****************************************************************************
	* @brief Obtains the spring arm component that belongs to the player
	*
	* @return USpringArmComponent* obtainedSpringArm
	*/
	FORCEINLINE class USpringArmComponent*
	GetCameraBoom() const { return CameraBoom; }


	/****************************************************************************
	* @brief Obtains the camera component that belongs to the player
	*
	* @return  UCameraComponent* obtainedCameraComponent
	*/
	FORCEINLINE class UCameraComponent*
	GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable) void 
	takeDamage(float damage);

protected:

  virtual void
  BeginPlay() override;

	/****************************************************************************
	* @brief Sets up the player components and bind the inputs to certain functions
	*/
	virtual void 
	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/****************************************************************************
	* @brief Manages the multiple actions that are happening
	*/
	void 
	checkAction();


	/****************************************************************************
	* @brief Moves and rotates the player in the forward axis of it's controller
	*
	* @param float inputValue
	*/
	void 
	MoveForward(float Value);


	/****************************************************************************
	* @brief Moves and rotates the player in it's right axis of  it's controller
	*
	* @param float inputValue
	*/
	void 
	MoveRight(float Value);


	/****************************************************************************
	* @brief Performs an attack, also triggers the weapon the player is using
	*/
	void 
	attack();


	/****************************************************************************
	* @brief Performs a roll movement
	*/
	void 
	roll();

	/****************************************************************************
	* @brief manages a condition that depends of time
	*
	* @param bool& condition, float& time, float& elapsed
	*/
	void 
	iterateCycle(bool& condition, float& time, float& elapsed);

	/****************************************************************************
	* @brief Obtains the Yaw rotation that the character has
	*
	* @return FRotator yawRotation
	*/
	FRotator 
	getYawRotation();


protected:
	UPROPERTY(EditAnywhere) 
	float m_rollEffectiveTime;

	UPROPERTY(EditAnywhere) 
	float m_attackEffectiveTime;

	UPROPERTY(EditAnywhere) 
	float m_invulnerabilityTime;

	UPROPERTY(EditAnywhere) 
	float m_deadDestroyTime;

	UPROPERTY(EditAnywhere) 
	float m_hpBase;

	UPROPERTY(BlueprintReadOnly)
	float m_healthPercentage;

	UPROPERTY(BlueprintReadOnly)
	bool m_rolling;

	UPROPERTY(BlueprintReadOnly)
	bool m_isAttacking;

	UPROPERTY(BlueprintReadOnly)
	bool m_isInvulnerable;

	UPROPERTY(BlueprintReadOnly)
	bool m_isDead;

	UPROPERTY() 
	UWorld* m_world;

private:
	FVector m_moveDirectionX;
	FVector m_moveDirectionY;
	float m_xMoveValue;
	float m_yMoveValue;
	float m_hp;
	float m_rollEffectiveTimeElapsed;
	float m_attackTimeElapsed;
	float m_invulnerabilityElapsed;
	float m_deadDestroyElapsed;
};

