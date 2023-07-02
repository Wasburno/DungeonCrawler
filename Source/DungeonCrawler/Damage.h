// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLER_API Damage
{
public:
	Damage(float damage);

	~Damage() = default;


	FORCEINLINE float 
	getDamage()
	{
		return m_damage;
	}

private:
	float m_damage;
};
