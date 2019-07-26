#ifndef VIDEOFILTER_H
#define VIDEOFILTER_H

#include <QQuickItem>
#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

class MyFilterRunnable : public QVideoFilterRunnable
{
public:
  QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
};

class VideoFilter : public QAbstractVideoFilter
{
  Q_OBJECT
public:
  QVideoFilterRunnable *createFilterRunnable(){return new MyFilterRunnable;}
signals:
  void finished(QObject *result);
};

#endif // VIDEOFILTER_H
