#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP
#include <QObject>

#include <QQuickImageProvider>
#include <QImage>

class ImageProvider : public QQuickImageProvider
{
public:
    explicit ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

    void setNewImage(const QImage &img);

private:
    QImage m_img;

};

#endif // IMAGE_PROVIDER_HPP
