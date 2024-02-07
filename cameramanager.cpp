#include "cameramanager.h"

CameraManager::CameraManager(QObject *parent) : QObject(parent), m_camera(nullptr)
{
}

CameraManager::~CameraManager()
{
    stopCamera();
}

void CameraManager::setupCamera(QCameraViewfinder *viewfinder)
{
    if (!m_camera)
    {
        m_camera = new QCamera(this);
        m_camera->setViewfinder(viewfinder);
    }
}

void CameraManager::startCamera()
{
    if (m_camera)
    {
        m_camera->start();
    }
}

void CameraManager::stopCamera()
{
    if (m_camera)
    {
        m_camera->stop();
        delete m_camera;
        m_camera = nullptr;
    }
}

QCamera* CameraManager::getCamera() const
{
    return m_camera;
}
