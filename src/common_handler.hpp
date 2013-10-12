#ifndef COMMON_HANDLER_HPP
#define COMMON_HANDLER_HPP

#include <QObject>
#include <QImage>

#include "image_provider.hpp"

class CommonHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommonHandler(ImageProvider* imageProvider, QObject *parent = 0);
    ~CommonHandler();

    Q_INVOKABLE void loadImage(QString path);

signals:
    void newImage();

public slots:

private:

    void findFeatures();

    QImage m_image;
    ImageProvider* m_imgProvider;

};

#endif // COMMON_HANDLER_HP
