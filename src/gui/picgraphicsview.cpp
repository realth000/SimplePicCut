#include "picgraphicsview.h"
#include <QRectF>

#include <QMetaObject>
#include <QScrollBar>
PicGraphicsView::PicGraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      m_scene(new QGraphicsScene),
      m_loadedPicItem(nullptr),
      m_isSelectingArea(false),
      m_isMoveingDrawShape(false),
      m_currentDrawItem(nullptr)
{
    m_drawShapePen = QPen(QColor(255, 0, 0));
    m_shape = DrawShape::Rectangle;
    this->setBackgroundBrush(QColor("#202020"));
    this->QGraphicsView::setScene(m_scene);
    setCacheMode(QGraphicsView::CacheBackground);
    setDragMode(QGraphicsView::NoDrag);
}

void PicGraphicsView::addPixmap(QPixmap pixmap)
{
    m_loadedPicItem = m_scene->addPixmap(pixmap);

    // Disable scale scene when item move near to scene border.
    setSceneRect(m_loadedPicItem->pixmap().rect());
}

void PicGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) {
        return;
    }
    QGraphicsItem *selectedItem = this->itemAt(event->pos());
    if (selectedItem != nullptr) {
        if (selectedItem->flags() & QGraphicsItem::ItemIsMovable) {
            m_moveStartPoint =  mapToScene(event->pos()).toPoint();
            return;
        }
        this->startDrawArea();
        m_drawShapeStartPoint = mapToScene(event->pos()).toPoint();
    }
}

void PicGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsItem *selectedItem = this->itemAt(event->pos());
    if (selectedItem  != nullptr) {
        this->stopStopgArea();
        if (selectedItem->flags() & QGraphicsItem::ItemIsMovable) {
            return;
        }

    }
}

void PicGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    // TODO: Reduce CPU consumption.
    QGraphicsView::mouseMoveEvent(event);
    if (event->buttons() != Qt::LeftButton) {
        return;
    }
    if (this->isSelectingArea()) {
        if (m_currentDrawItem != nullptr) {
            m_scene->removeItem(m_currentDrawItem);
            delete m_currentDrawItem;
            m_currentDrawItem = nullptr;
        }
        int x1 = mapToScene(event->pos()).toPoint().x();
        int y1 = mapToScene(event->pos()).toPoint().y();
        QPoint p = QPoint(qMin(x1, m_drawShapeStartPoint.x()), qMin(y1, m_drawShapeStartPoint.x()));
        QSize s = QSize(qAbs(x1 - m_drawShapeStartPoint.x()), qAbs(y1 - m_drawShapeStartPoint.x()));
        m_currentDrawItem = m_scene->addRect(QRect(p, s), QPen(Qt::green));
        m_currentDrawItem->setFlags(QGraphicsItem::ItemIsMovable);
    } else if (this->itemAt(event->pos())->flags() & QGraphicsItem::ItemIsMovable) {
        QPoint p = mapToScene(event->pos()).toPoint();
        this->itemAt(event->pos())->setTransform(QTransform(1,0,0,
                                                         0,1,0,
                                                            p.x() - m_moveStartPoint.x(), p.y() - m_moveStartPoint.y(), 1));
    }
}

void PicGraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void PicGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void PicGraphicsView::startDrawArea()
{
    m_isSelectingArea = true;
}

void PicGraphicsView::stopStopgArea()
{
    m_isSelectingArea = false;
}

bool PicGraphicsView::isSelectingArea()
{
    return this->m_isSelectingArea;
}
