#ifndef OPENCVACTION_H
#define OPENCVACTION_H

#include <QObject>
#include "opencv2/opencv.hpp"

class OpenCVaction : public QObject
{
  Q_OBJECT
public:
  explicit OpenCVaction(QObject *parent = nullptr);
  virtual ~OpenCVaction();
  virtual void action(cv::Mat &imgin, cv::Mat *&imgout) = 0;
signals:

public slots:
};

#endif // OPENCVACTION_H
