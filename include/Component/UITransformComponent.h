#pragma once

#include "TransformComponent.h"

class UITransformComponent : public CTransformComponent
{
public:
	void PreRender(float DelatTime) override;
	void Render() override;

	void UpdateMatrix();
};

