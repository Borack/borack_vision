#ifndef COMMON_HANDLER_HPP
#define COMMON_HANDLER_HPP

#include <QObject>
#include <QImage>

class CommonHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommonHandler(QObject *parent = 0);
    ~CommonHandler();

    Q_INVOKABLE void loadImage(QString path);

signals:

public slots:

private:
    QImage m_image;

};

#endif // COMMON_HANDLER_HP
