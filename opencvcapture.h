#ifndef OPENCVCAPTURE_H
#define OPENCVCAPTURE_H

#include <QObject>
#include "opencv2/opencv.hpp"

class OpenCVcapture : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool m_run READ run WRITE setRun NOTIFY runChanged)
public:
  explicit OpenCVcapture(QObject *parent = nullptr);
  virtual ~OpenCVcapture();

  bool run() const;
  virtual void setRun(bool r);

  virtual cv::Mat *getFrame() = 0;

signals:
  void runChanged();
public slots:

protected:
  bool m_run;
};

#endif // OPENCVCAPTURE_H
