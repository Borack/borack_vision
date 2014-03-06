#ifndef PHOTOMONTAGE_HPP
#define PHOTOMONTAGE_HPP

#include <QObject>

#include <QPixmap>

class PhotoMontage : public QObject
{
   Q_OBJECT
public:
   explicit PhotoMontage(const QPixmap &pixmap, QObject *parent = 0);

signals:

public slots:

private:

   void setupGraphCut();

   const QPixmap& m_inputSource;

};

#endif // PHOTOMONTAGE_HPP
