#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>

class CameraManager : public QObject
{
    Q_OBJECT

public:
    explicit CameraManager(QObject *parent = nullptr);
    ~CameraManager();
    QCamera* getCamera() const;

    void setupCamera(QCameraViewfinder *viewfinder);
    void startCamera();
    void stopCamera();

private:
   QCamera *m_camera;
};


#endif // CAMERAMANAGER_H
