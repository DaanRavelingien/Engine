#include "EnginePCH.h"
#include "HitboxManagerComp.h"

//component includes
#include "HitboxComp.h"

HitboxManagerComp::HitboxManagerComp()
	:Component{typeid(this).name()}
{
}

void HitboxManagerComp::Update()
{
	//comparing the hitboxes to each other to update wich ones overlap
	for (HitboxComp* pHitbox : m_Hitboxes)
	{
		pHitbox->ClearOverlappingHitboxes();
	
		for (HitboxComp* pOtherHitbox : m_Hitboxes)
		{
			//avoiding self updating the hitboxes
			if (pOtherHitbox == pHitbox)
				continue;

			pHitbox->IsOverlapping(pOtherHitbox);
		}
	}
}
