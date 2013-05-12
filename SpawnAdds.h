#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "DeathBehaviour.h"
#include "AbstractManager.h"
#include "EnemyList.h"

//-----------------------------------------------------------------
// SpawnAdds Class																
//-----------------------------------------------------------------
class SpawnAdds : public DeathBehaviour
{
public:	
	//---------------------------
	// Enum(s)
	//---------------------------
	static enum AddType
	{
		SLIMESMALL
	};

	//---------------------------
	// Constructor(s)
	//---------------------------
	SpawnAdds(const D3DXVECTOR2* const pos, const AddType& type, const int& numAdds, const tstring& managername);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~SpawnAdds();

	//---------------------------
	// General Methods
	//---------------------------

	void Die();

	

private:
	// -------------------------
	// Datamembers
	// -------------------------
	AddType m_ChosenType;
	int m_NumberOfAdds;
	AbstractManager* m_pManager;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	SpawnAdds(const SpawnAdds& t);
	SpawnAdds& operator=(const SpawnAdds& t);
};
