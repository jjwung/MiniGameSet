// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticToolFunction.h"


void UTacticToolFunction::CalculateMouseAngleToCenter(FVector2D MousePos, FVector2D ScreenSize,float& Angle)
{
	const float CenterX = ScreenSize.X / 2.0f;
	const float CenterY = ScreenSize.Y / 2.0f;
	const float dx = MousePos.X - CenterX;
	const float dy = MousePos.Y - CenterY;

	// 1. 处理中心点重合的情况
	if (FMath::IsNearlyZero(dx) && FMath::IsNearlyZero(dy))
	{
		Angle = 0.0f;
	}

	// 2. 转换到数学坐标系（y轴向上）
	const float mathY = -dy; // 反转y轴方向

	// 3. 计算相对于正右方的逆时针角度
	const float rawAngle = FMath::RadiansToDegrees(FMath::Atan2(mathY, dx));

	// 4. 转换为从正上方开始的顺时针角度
	Angle = FMath::Fmod(450.0f - rawAngle, 360.0f);
}
