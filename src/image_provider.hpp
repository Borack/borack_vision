#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP
#include <QObject>

#include <QQuickImageProvider>
#include <types.hpp>

class ImageProvider : public QQuickImageProvider
{
public:
    explicit ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

    void setNewImage(const QImages &img);
    void setMatchImage(const QImage &matchImage);
    void setFeatureOverlay(const QImages &featureOverlay);

private:
    QImages m_img;
    QImages m_featureOverlay;
    QImage m_matchImage;

};

#endif // IMAGE_PROVIDER_HPP
