#ifndef OPENCVCAMERA_H
#define OPENCVCAMERA_H

#include <QObject>
#include "opencvcapture.h"
#include "opencv2/opencv.hpp"

class OpenCVcamera : public OpenCVcapture
{
  Q_OBJECT
  Q_PROPERTY(int m_cameraId READ cameraId WRITE setCameraId NOTIFY cameraIdChanged)
public:
  explicit OpenCVcamera(QObject *parent = nullptr);
  ~OpenCVcamera();

  int cameraId() const;
  void setCameraId(int id);

  virtual void setRun(bool r);

  cv::Mat *getFrame();

signals:
  void cameraIdChanged();
  void runChanged();
  void frame(const QImage &img);
public slots:

private:
  int m_cameraId;
  int m_openedCameraId;
  cv::Mat *m_image;
  cv::VideoCapture *m_cvCapture;
};

#endif // OPENCVCAMERA_H
