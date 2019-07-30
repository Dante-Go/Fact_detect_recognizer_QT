#ifndef OPENCVCANNYACTION_H
#define OPENCVCANNYACTION_H

#include "opencvaction.h"

class OpenCVcannyAction : public OpenCVaction
{
  Q_OBJECT
public:
  explicit OpenCVcannyAction(QObject *parent = nullptr);
  ~OpenCVcannyAction();

  void action(cv::Mat &imgin, cv::Mat *&imgout);

signals:

public slots:
};

#endif // OPENCVCANNYACTION_H
