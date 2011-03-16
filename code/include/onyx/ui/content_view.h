#ifndef CENTENT_VIEW_H_
#define CENTENT_VIEW_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "onyx/ui/line_edit.h"
#include "onyx/data/data.h"

namespace ui
{

class ContentView : public QWidget
{
    Q_OBJECT

public:
    ContentView(QWidget *parent);
    virtual ~ContentView();

public:
    bool updateData(OData* data, bool force_update = false);
    OData * data();
    virtual void updateView() = 0;

    void activate(int user_data = 0);
    void repaintAndRefreshScreen();

    void setChecked(bool checked = true);
    bool isChecked();

    int penWidth() { return pen_width_; }
    void setPenWidth(int w) { pen_width_ = w; }

    void setBkColor(Qt::GlobalColor color) { bk_color_ = color; }
    Qt::GlobalColor bkColor() { return bk_color_; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    void changeEvent(QEvent *event);
    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent * event);
    bool event(QEvent * event);
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent * event);

Q_SIGNALS:
    void activated(ContentView *item, int user_data);
    void keyRelease(ContentView *item, QKeyEvent *key);
    void mouse(QPoint last, QPoint current);

protected:
    bool isPressed();
    void setPressed(bool p = true);

private:
    OData* data_;
    bool pressed_;
    bool checked_;
    int pen_width_;
    Qt::GlobalColor bk_color_;
};


/// Cover view provides a cover and title support.
class CoverView : public ContentView
{
    Q_OBJECT

public:
    CoverView(QWidget *parent);
    virtual ~CoverView();

    static const QString type();

public:
    virtual void updateView();

protected:
    void paintEvent(QPaintEvent * event);
    void drawCover(QPainter & painter, QRect rect);
    void drawTitle(QPainter & painter, QRect rect);
};

/// CheckBox view provides a checkbox and title support.
class CheckBoxView : public ContentView
{
    Q_OBJECT

public:
    CheckBoxView(QWidget *parent);
    virtual ~CheckBoxView();

    static const QString type();

public:
    virtual void updateView();

protected:
    void paintEvent(QPaintEvent * event);
    QRect drawCheckBox(QPainter & painter, QRect rect);
    QRect drawCover(QPainter & painter, QRect rect);
    void drawTitle(QPainter & painter, QRect rect);
};


/// LineEditView.
class LineEditView : public ContentView
{
    Q_OBJECT

public:
    LineEditView(QWidget *parent);
    virtual ~LineEditView();

    static const QString type();

public:
    virtual void updateView();

protected:
    void keyPressEvent(QKeyEvent * event);
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent * event);

private Q_SLOTS:
    void onEditOutOfRange(QKeyEvent *ke);

private:
    void createLayout();

private:
    OnyxLineEdit inner_edit_;
    QHBoxLayout layout_;
    bool forward_focus_;
};


};

#endif
