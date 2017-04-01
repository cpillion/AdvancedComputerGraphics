#ifndef HW07F_H
#define HW07F_H

#include <QAbstractVideoSurface>

class Hw07frame : public QAbstractVideoSurface
{
Q_OBJECT
public:
    Hw07frame(QObject* parent=0);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
signals:
    void frameAvailable(QImage frame);
};

#endif
