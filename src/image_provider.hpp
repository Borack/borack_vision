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
    void setFeatureOverlay(const QImage &featureOverlay);

private:
    QImage m_img;
    QImage m_featureOverlay;

};

#endif // IMAGE_PROVIDER_HPP
