#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP
#include <QObject>

class ImageProvider : public QObject
{
    Q_OBJECT

public:
    explicit ImageProvider(QObject* parent = 0);
};

#endif // IMAGE_PROVIDER_HPP
