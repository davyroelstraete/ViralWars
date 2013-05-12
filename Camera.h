/*
Class wich controls the cameraview and movement.
*/

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SpriteEngine.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	bool Init(const D3DXVECTOR3& pos=D3DXVECTOR3(0.0f,0.0f,-16.0f));

	void Update(float dtime);

	void SetPosition(float x,float y,float z);
	void TranslateCamera(float x,float y,float z);	
	void RotateCamera(float pitch,float yaw,float roll);
	
	void ResetCamera();

	const D3DXMATRIX& GetViewMatrix() const;
	const D3DXMATRIX& GetProjectionMatrix() const;
	const D3DXVECTOR3& GetPosition() const;
	const D3DXVECTOR3& GetRotation() const;
	const D3DXVECTOR3& GetLookAt() const;
	const D3DXVECTOR3& GetRightVector() const;

	void GetWorldPickingRay(D3DXVECTOR3& originW, D3DXVECTOR3& dirW);

private:
	void CreateViewMatrix();

	D3DXVECTOR3 m_MyPosition,m_MyRotation,m_MyLookAtPoint,m_MyUpVector,m_MyRightVector;

	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;

	D3DXPLANE m_FrustumPlanes[6];

	Camera(const Camera& t);
	Camera& operator=(const Camera& t);
};
#endif