#ifndef MOUSE_TRACKER_H
#define MOUSE_TRACKER_H

#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDebug>
#include <QEvent>
#include <QLabel>

class Mouse_tracker : public QLabel
{
    Q_OBJECT

private:

public:
    explicit Mouse_tracker(QWidget *parent = 0);
    ~Mouse_tracker();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseleaveEvent(QEvent *);
    void mousePressandHoldEvent(QMouseEvent *ev);

    int x, y;
    bool left;

    bool hasMouseLeft() const;

protected:
    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaveEvent(QDragLeaveEvent * event);
    void dragMoveEvent(QDragMoveEvent * event);

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Mouse_Hold();
    void Mouse_Release();

public slots:
};

#endif // MOUSE_TRACKER_H
