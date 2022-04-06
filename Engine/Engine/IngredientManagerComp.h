#pragma once
#include "Component.h"
#include <map>

class GameObject;

class IngredientManagerComp : public Component
{
public:
	IngredientManagerComp();
	~IngredientManagerComp() = default;
	IngredientManagerComp(const IngredientManagerComp& other) = delete;
	IngredientManagerComp(IngredientManagerComp&& other) = delete;
	IngredientManagerComp& operator=(const IngredientManagerComp& other) = delete;
	IngredientManagerComp& operator=(IngredientManagerComp&& other) = delete;

	void CreateIngredient(const std::string& type, const glm::vec2& pos);

private:
	void CreateIngredientParts(GameObject* pIngredient, const std::string& type);

	std::map<std::string, glm::vec4> m_IngredientTypes{};
};

