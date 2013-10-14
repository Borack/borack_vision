#include "image_provider.hpp"
#include <QDebug>

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

//-----------------------------------------------------------------------------

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    if(id == "features")
    {
        size->setWidth(m_featureOverlay.width());
        size->setHeight(m_featureOverlay.height());

        return m_featureOverlay;
    }
    else
    {
        size->setWidth(m_img.width());
        size->setHeight(m_img.height());

        return m_img;
    }
}

//-----------------------------------------------------------------------------

void ImageProvider::setNewImage(const QImage &img)
{
    qDebug() << Q_FUNC_INFO;
    m_img = img;
}

void ImageProvider::setFeatureOverlay(const QImage &featureOverlay)
{
    m_featureOverlay = featureOverlay;
}
