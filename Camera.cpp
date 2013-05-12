#include "Camera.h"

Camera::Camera():m_MyPosition(0.0f,0.0f,0.0f),
				m_MyRotation(0.0f,0.0f,0.0f),
				m_MyLookAtPoint(0,0,0.0f),
				m_MyUpVector(0,1.0f,0),
				m_MyRightVector(1.0f,0,0)
{
}
Camera::~Camera()
{
}
bool Camera::Init(const D3DXVECTOR3& pos)
{
	m_MyPosition=pos;

	CreateViewMatrix();

	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix,D3DX_PI/4,SPRITE_ENGINE->GetBackBufferWidth()/SPRITE_ENGINE->GetBackBufferHeight(),0.5f,512.0f);

	D3DXMATRIX viewproj=m_ViewMatrix*m_ProjectionMatrix;

	return true;
}
void Camera::Update(float dtime)
{
	CreateViewMatrix();

	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix,D3DX_PI/4,SPRITE_ENGINE->GetBackBufferWidth()/SPRITE_ENGINE->GetBackBufferHeight(),0.5f,512.0f);

	D3DXMATRIX viewproj=m_ViewMatrix*m_ProjectionMatrix;
}
void Camera::SetPosition(float x,float y,float z)
{
	m_MyPosition.x=x;
	m_MyPosition.y=y;
	m_MyPosition.z=z;
}
void Camera::TranslateCamera(float x,float y,float z)
{
	m_MyPosition.x+=x;
	m_MyPosition.y+=y;
	m_MyPosition.z+=z;
}
void Camera::RotateCamera(float pitch,float yaw,float roll)
{
	m_MyRotation.x+=pitch;
	m_MyRotation.y+=yaw;
	m_MyRotation.z+=roll;
}
void Camera::ResetCamera()
{
	m_MyPosition=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_MyRotation=D3DXVECTOR3(0.0f,0.0f,0.0f);
}
const D3DXMATRIX& Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}
const D3DXMATRIX& Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}
const D3DXVECTOR3& Camera::GetPosition() const
{
	return m_MyPosition;
}
const D3DXVECTOR3& Camera::GetRotation() const
{
	return m_MyRotation;
}
const D3DXVECTOR3& Camera::GetLookAt() const
{
	return m_MyLookAtPoint;
}
const D3DXVECTOR3& Camera::GetRightVector() const
{
	return m_MyRightVector;
}
void Camera::CreateViewMatrix()
{
	//Resets the axis from the camera:
	m_MyUpVector=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_MyLookAtPoint=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_MyRightVector=D3DXVECTOR3(1.0f,0.0f,0.0f);

	//Apply rotation around the x-axis:
	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &m_MyRightVector, m_MyRotation.x);
	D3DXVec3TransformCoord(&m_MyLookAtPoint, &m_MyLookAtPoint, &pitchMatrix);
	D3DXVec3TransformCoord(&m_MyUpVector, &m_MyUpVector, &pitchMatrix);

	//Apply rotation around the y-axis:
	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationY(&yawMatrix, m_MyRotation.y);
	D3DXVec3TransformCoord(&m_MyLookAtPoint, &m_MyLookAtPoint, &yawMatrix);
	D3DXVec3TransformCoord(&m_MyRightVector, &m_MyRightVector, &yawMatrix); 
	D3DXVec3TransformCoord(&m_MyUpVector, &m_MyUpVector, &yawMatrix);

	//Apply rotation around the z-axis:
	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &m_MyLookAtPoint, m_MyRotation.z);
	D3DXVec3TransformCoord(&m_MyRightVector, &m_MyRightVector, &rollMatrix);
	D3DXVec3TransformCoord(&m_MyUpVector, &m_MyUpVector, &rollMatrix);

	D3DXMatrixIdentity(&m_ViewMatrix);

	float x = -D3DXVec3Dot(&m_MyPosition, &m_MyRightVector);
	float y = -D3DXVec3Dot(&m_MyPosition, &m_MyUpVector);
	float z = -D3DXVec3Dot(&m_MyPosition, &m_MyLookAtPoint);

	m_ViewMatrix(0,0) = m_MyRightVector.x; 
	m_ViewMatrix(1,0) = m_MyRightVector.y; 
	m_ViewMatrix(2,0) = m_MyRightVector.z; 
	m_ViewMatrix(3,0) = x;   

	m_ViewMatrix(0,1) = m_MyUpVector.x;
	m_ViewMatrix(1,1) = m_MyUpVector.y;
	m_ViewMatrix(2,1) = m_MyUpVector.z;
	m_ViewMatrix(3,1) = y;  

	m_ViewMatrix(0,2) = m_MyLookAtPoint.x; 
	m_ViewMatrix(1,2) = m_MyLookAtPoint.y; 
	m_ViewMatrix(2,2) = m_MyLookAtPoint.z; 
	m_ViewMatrix(3,2) = z;   

	m_ViewMatrix(0,3) = 0.0f;
	m_ViewMatrix(1,3) = 0.0f;
	m_ViewMatrix(2,3) = 0.0f;
	m_ViewMatrix(3,3) = 1.0f;
}