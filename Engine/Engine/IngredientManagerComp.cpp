#include "EnginePCH.h"
#include "IngredientManagerComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "HitboxComp.h"
#include "TransformComp.h"
#include "TextureRenderComp.h"
#include "TextureComp.h"
#include "IngredientPieceComp.h"

IngredientManagerComp::IngredientManagerComp()
	:Component{typeid(this).name()}
{
	//creating the ingredient types
	m_IngredientTypes.emplace("TOPBUN", glm::vec4{ 102,37,31,7 });
	m_IngredientTypes.emplace("BOTTOMBUN", glm::vec4{ 102,45,31,7 });
	m_IngredientTypes.emplace("LETTUCE", glm::vec4{ 102,77,31,7 });
	m_IngredientTypes.emplace("CHEESE", glm::vec4{ 104,53,28,6 });
	m_IngredientTypes.emplace("PATTY", glm::vec4{ 104,61,28,7 });
	m_IngredientTypes.emplace("TOMATO", glm::vec4{ 103,69,30,7 });
}

void IngredientManagerComp::CreateIngredient(const std::string& type, const glm::vec2& pos)
{
	//an ingredient exists out of 4 child game objects wich have each a piece of the ingredient to display 
	//on what part peter pepper has walked

	GameObject* pIngredient{ new GameObject{"Ingredient" + std::to_string(m_pGameObj->GetChildren().size())} };

	//adding the pieces to the ingedient
	CreateIngredientParts(pIngredient, type);

	//adding hitbox to the ingredient
	glm::vec4 sourceRect{ m_IngredientTypes.at(type) };
	//pIngredient->AddComponent(new HitboxComp{ HitboxTag::Ingredient, sourceRect.z, sourceRect.w });

	glm::vec2 position{ pos.x * m_pGameObj->GetTransform()->GetScale().x,
		(pos.y + 16) * m_pGameObj->GetTransform()->GetScale().y };
	pIngredient->GetTransform()->SetPos({ position.x,position.y,0 });

	m_pGameObj->AddChild(pIngredient);
}

void IngredientManagerComp::CreateIngredientParts(GameObject* pIngredient, const std::string& type)
{
	//creating the 4 different parts of our ingredient
	int nrOfPieces{ 4 };

	for (int i{}; i < nrOfPieces; i++)
	{
		GameObject* pIngredientPiece{ new GameObject{"IngredientPiece_" + std::to_string(i) + "_" + pIngredient->GetName()} };
		pIngredientPiece->AddComponent(new TextureRenderComp{});
		pIngredientPiece->AddComponent(new IngredientPieceComp{});
		TextureComp* pTextureComp{ new TextureComp{"BurgerTimeTexture"} };
		pIngredientPiece->AddComponent(pTextureComp);

		//handeling the different sizes for the ingredients
		glm::vec4 ingrSourceRect{ m_IngredientTypes.at(type) };
		float pieceWidth{ ingrSourceRect.z / (float)nrOfPieces };
		
		pTextureComp->SetSourceRect({ ingrSourceRect.x + pieceWidth * i,ingrSourceRect.y,pieceWidth,ingrSourceRect.w });
		pTextureComp->SetDestRect({ 0,0,pieceWidth,ingrSourceRect.w});
		
		pIngredientPiece->AddComponent(new HitboxComp{ HitboxTag::ingredientPiece,pieceWidth,ingrSourceRect.w });

		pIngredientPiece->GetTransform()->SetPos({ pieceWidth * i * m_pGameObj->GetTransform()->GetScale().x,0,0 });

		//adding the piece to the ingredient
		pIngredient->AddChild(pIngredientPiece);
	}
}


