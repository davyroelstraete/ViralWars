#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpriteEngine.h"

//-----------------------------------------------------------------
// AbstractManager Class																
//-----------------------------------------------------------------
class AbstractManager 
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	AbstractManager();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~AbstractManager();

	//---------------------------
	// General Methods
	//---------------------------

	virtual bool SpawnAdd(const D3DXVECTOR2& pos, const int& type) = 0;

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	AbstractManager(const AbstractManager& t);
	AbstractManager& operator=(const AbstractManager& t);
};
