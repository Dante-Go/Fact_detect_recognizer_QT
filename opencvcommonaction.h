#ifndef OPENCVCOMMONACTION_H
#define OPENCVCOMMONACTION_H

#include <QObject>
#include "opencvaction.h"

class OpenCVcommonAction : public OpenCVaction
{
  Q_OBJECT
public:
  OpenCVcommonAction();
  ~OpenCVcommonAction();
  void action(cv::Mat &imgin, cv::Mat *&imgout);
};

#endif // OPENCVCOMMONACTION_H
