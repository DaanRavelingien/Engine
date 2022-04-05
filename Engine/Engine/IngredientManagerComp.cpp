#include "EnginePCH.h"
#include "IngredientManagerComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "HitboxComp.h"
#include "TransformComp.h"
#include "TextureRenderComp.h"
#include "TextureComp.h"

IngredientManagerComp::IngredientManagerComp()
	:Component{typeid(this).name()}
{
}

void IngredientManagerComp::CreateIngredient(const std::string& /*type*/, const glm::vec2& /*pos*/)
{
	/*
	GameObject* pIngredient{ new GameObject{"Ingredient" + std::to_string(m_Ingredients.size())} };

	//adding the neccesary components
	pIngredient->AddComponent(new TextureRenderComp{});
	TextureComp* pIngredientTexture{ new TextureComp{burgerTimeTextureIdx} };
	pIngredient->AddComponent(pIngredientTexture);

	//handeling the different sizes for the ingredients
	std::string lable{ ingredient["Type"].GetString() };
	if (lable.compare("TOPBUN") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,31,7 });

		pIngredientTexture->SetSourceRect({ 102,37,31,7 });
		pIngredientTexture->SetDestRect({ 0,0,31,7 });
	}
	else if (lable.compare("BOTTOMBUN") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,31,7 });

		pIngredientTexture->SetSourceRect({ 102,45,31,7 });
		pIngredientTexture->SetDestRect({ 0,0,31,7 });
	}
	else if (lable.compare("LETTUCE") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,31,7 });

		pIngredientTexture->SetSourceRect({ 102,77,31,7 });
		pIngredientTexture->SetDestRect({ 0,0,31,7 });
	}
	else if (lable.compare("CHEESE") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,28,6 });

		pIngredientTexture->SetSourceRect({ 104,53,28,6 });
		pIngredientTexture->SetDestRect({ 0,0,28,6 });
	}
	else if (lable.compare("PATTY") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,28,7 });

		pIngredientTexture->SetSourceRect({ 104,61,28,7 });
		pIngredientTexture->SetDestRect({ 0,0,28,7 });
	}
	else if (lable.compare("TOMATO") == 0)
	{
		pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient,30,7 });

		pIngredientTexture->SetSourceRect({ 103,69,30,7 });
		pIngredientTexture->SetDestRect({ 0,0,30,7 });
	}

	glm::vec2 pos{ ingredient["Position"][0].GetFloat() * pIngredients->GetTransform()->GetScale().x,
		(ingredient["Position"][1].GetFloat() + 16) * pIngredients->GetTransform()->GetScale().y };
	pIngredient->GetTransform()->SetPos({ pos.x,pos.y,0 });

	pIngredients->AddChild(pIngredient);

	*/
}


