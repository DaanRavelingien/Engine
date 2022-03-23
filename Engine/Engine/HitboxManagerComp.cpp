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
		if (!pHitbox)
			continue;

		pHitbox->ClearOverlappingHitboxes();
	
		for (HitboxComp* pOtherHitbox : m_Hitboxes)
		{
			if (!pOtherHitbox)
				continue;

			//avoiding self updating the hitboxes
			if (pOtherHitbox == pHitbox)
				continue;

			pHitbox->IsOverlapping(pOtherHitbox);
		}
	}
}
