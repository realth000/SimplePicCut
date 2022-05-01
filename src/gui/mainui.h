#ifndef MAINUI_H
#define MAINUI_H

#include <QtWidgets/QWidget>

#include "util/titlebar.h"
// test
#include <QtGui/QMouseEvent>
#include "gui/picgraphicsview.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainUi; }
QT_END_NAMESPACE

class MainUi : public QWidget
{
    Q_OBJECT

public:
    MainUi(QWidget *parent = nullptr);
    ~MainUi();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainUi *ui;

    QRectF m_picRect;
};
#endif // MAINUI_H
