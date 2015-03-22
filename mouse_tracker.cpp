#include "mouse_tracker.h"

Mouse_tracker::Mouse_tracker(QWidget *parent)
    : QLabel(parent)
{
}

Mouse_tracker::~Mouse_tracker()
{
}

void Mouse_tracker::mouseMoveEvent(QMouseEvent *ev)
{
        this->x = ev->x();
        this->y = ev->y();
        emit Mouse_Pos();
}

void Mouse_tracker::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void Mouse_tracker::mouseleaveEvent(QEvent *)
{
    emit Mouse_Left();
}

bool Mouse_tracker::hasMouseLeft() const
{
    return this->left;
}

void Mouse_tracker::mousePressandHoldEvent(QMouseEvent *ev)
{
    emit Mouse_Release();
}

void Mouse_tracker::dragEnterEvent(QDragEnterEvent * event)
{
    event->accept();
}

void Mouse_tracker::dragLeaveEvent(QDragLeaveEvent * event)
{
    event->accept();
}

void Mouse_tracker::dragMoveEvent(QDragMoveEvent * event)
{
    event->accept();
}


