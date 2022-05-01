#ifndef PICGRAPHICSVIEW_H
#define PICGRAPHICSVIEW_H

#include <QtGui/QMouseEvent>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsView>

#include "defines.h"

class PicGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    PicGraphicsView(QWidget *parent = nullptr);
    enum DrawShape {
        Rectangle = 0
    };

    // Not allow to change scene, use addPixmap instead.
    void setScene(QGraphicsScene *scene) = delete;
    void addPixmap(QPixmap pixmap);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_loadedPicItem;

    bool m_isSelectingArea;
    bool m_isMoveingDrawShape;
    QPoint m_drawShapeStartPoint;
    QPoint m_moveStartPoint;
    QPen m_drawShapePen;
    QBrush m_drawShapeBrush;
    DrawShape m_shape;
    QRectF *m_currentDrawRect;
    QGraphicsItem *m_currentDrawItem;

    void startDrawArea();
    void stopStopgArea();
    bool isSelectingArea();
};

#endif // PICGRAPHICSVIEW_H
