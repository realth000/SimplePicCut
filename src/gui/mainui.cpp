#include "mainui.h"
#include "./ui_mainui.h"
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QDebug>

#include "defines.h"
// test
#include <QtCore/QFile>
#include <QtGui/QPixmap>

#define USE_BORDER
MainUi::MainUi(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainUi)
{
    ui->setupUi(this);
    this->setFixedSize(800,400);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->titleBar->setCloseIcon(":/pic/close.png");
    ui->titleBar->setMinIcon(":/pic/minimize.png");
    ui->titleBar->setMaxIcon(":/pic/minimize.png");
    ui->titleBar->setTitleText("aaaaaaaaaaaaaaaa");
    ui->titleBar->setUseGradient(true);
    ui->titleBar->setTitleIcon(":/pic/minimize.png");
    ui->titleBar->initUi();
//, "rgb(240,255,255)", "rgb(93,94,95)",
//    "qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(18,18,18), stop: 1 rgb(21,21,21))", "rgb(240,255,255)"
#ifdef USE_BORDER
    ui->verticalLayout->setContentsMargins(10,10,10,10);
#else
    ui->verticalLayout->setContentsMargins(0,0,0,0);
#endif
    this->setStyleSheet("QWidget{background:#202020}");
    ui->MainPicView->setFrameStyle(QFrame::NoFrame);

    // test
    QString picFilePath = "c:/QtProjects/SimplePicCut/test/test.jpg";
    QFile picFile(picFilePath);

    if (!picFile.exists() || !picFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Can not open file" << picFilePath;
        return;
    }
    ui->MainPicView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


    QPixmap picPixmap(picFilePath);
    this->resize(picPixmap.size());
    ui->MainPicView->addPixmap(picPixmap);
    m_picRect = QRectF(picPixmap.rect());
}

MainUi::~MainUi()
{
    delete ui;
}

void MainUi::resizeEvent(QResizeEvent *event)
{
    ui->titleBar->setFixedWidth(this->width());
#ifdef USE_BORDER
    ui->MainPicView->resize(QSize(event->size().width()-20, event->size().height()-20));
#else
    ui->MainPicView->resize(QSize(event->size().width()-0, event->size().height()-0));
#endif
}
