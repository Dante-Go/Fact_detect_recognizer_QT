#ifndef OPENCVCAMERA_H
#define OPENCVCAMERA_H

#include <QObject>
#include "opencvcapture.h"
#include "opencv2/opencv.hpp"

class OpenCVcamera : public OpenCVcapture
{
  Q_OBJECT
  Q_PROPERTY(int m_cameraId READ cameraId WRITE setCameraId NOTIFY cameraIdChanged)
  Q_PROPERTY(bool m_isIPCrtsp READ isIPCrtsp WRITE setIsIPCrtsp NOTIFY isIPCrtspChanged)
  Q_PROPERTY(QString m_rtspAddress READ rtspAddress WRITE setRtspAddress NOTIFY rtspAddressChanged)
public:
  explicit OpenCVcamera(QObject *parent = nullptr);
  ~OpenCVcamera();

  int cameraId() const;
  void setCameraId(int id);

  bool isIPCrtsp() const;
  void setIsIPCrtsp(bool ipcFlag);
  QString rtspAddress() const;
  void setRtspAddress(QString rtspAddr);

  virtual void setRun(bool r);

  cv::Mat *getFrame();

signals:
  void cameraIdChanged();
  void isIPCrtspChanged();
  void rtspAddressChanged();

  void runChanged();
  void frame(const QImage &img);
public slots:

private:
  int m_cameraId;
  int m_openedCameraId;
  cv::Mat *m_image;
  cv::VideoCapture *m_cvCapture;

  bool m_isIPCrtsp;
  QString m_rtspAddress;
};

#endif // OPENCVCAMERA_H
