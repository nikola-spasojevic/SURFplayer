#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();

signals:

public slots:
};

#endif // IMAGEVIEW_H
