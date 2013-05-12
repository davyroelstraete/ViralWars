//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpawnAdds.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// SpawnAdds methods																				
//-----------------------------------------------------------------

SpawnAdds::SpawnAdds(const D3DXVECTOR2* const pos, const AddType& type, const int& numAdds, const tstring& managername):DeathBehaviour(pos)																						
{
	m_Pos = pos;
	m_ChosenType = type;
	m_NumberOfAdds = numAdds;

	if(managername == _T("enemy"))
	{
		m_pManager = static_cast<EnemyList*>(EnemyList::GetSingleton());
	}
}

SpawnAdds::~SpawnAdds()																						
{
	// nothing to destroy
}

void SpawnAdds::Die()
{
	for (int count = 0; count != m_NumberOfAdds; ++count) m_pManager->SpawnAdd(*m_Pos, m_ChosenType);
}