#include "titlebar.h"
#include <QtCore/QDebug>
#include <QtCore/QEvent>

TitleBar::TitleBar(QWidget *parent)
    : QGroupBox(parent),
      m_leftButtonPressed(false),
      m_useGradient(false),
      m_start(QPoint(0,0)),
      p(parent),
      m_layout(new QHBoxLayout(this)),
      m_iconLabel(new QLabel(this)),
      m_titleLable(new QLabel(this)),
      m_minimizeButtonIcon(nullptr),
      m_maximizeButtonIcon(nullptr),
      m_closeButtonIcon(nullptr),
      m_minimizeButton(new QPushButton(this)),
      m_maximizeButton(new QPushButton(this)),
      m_closeButton(new QPushButton(this))
{
    m_layout->addWidget(m_iconLabel);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_titleLable);
    m_layout->addStretch(1);
    m_layout->addWidget(m_minimizeButton);
    m_layout->addWidget(m_maximizeButton);
    m_layout->addWidget(m_closeButton);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);
    m_layout->setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(30);
    m_iconLabel->setFixedSize(30, 30);
    m_titleLable->setFixedHeight(30);
    m_titleLable->setAlignment(Qt::AlignCenter);
    m_minimizeButton->setFixedSize(30, 30);
    m_maximizeButton->setFixedSize(30, 30);
    m_closeButton->setFixedSize(30, 30);
    this->setFixedWidth(parent->width());
    qDebug() << "title bar layout width" << this->width();
}

TitleBar::~TitleBar()
{
    p = nullptr;
    delete m_iconLabel;
    delete m_titleLable;
    delete m_minimizeButton;
    delete m_maximizeButton;
    delete m_closeButton;
}

void TitleBar::initUi(TitleBarColorStyle style, TitleBarButtonMode mode)
{
    m_buttonMode = mode;

    switch (style) {
    case TitleBarColorStyle::Black:
        this->setStyleSheet("QWidget{font:15px;color:#f0f0f0}"
                                "QGroupBox{border:none;background:#202020;}"
                                "QPushButton{background:transparent;border:none;border-radius:0px}"
                                "QPushButton:hover{color:#f0f0f0;background-color:#303030}");
    case TitleBarColorStyle::White:
    default:
        break;
    }
//    if(useGradient){
//        this->setStyleSheet(QString("QWidget{font:15px;color:%1}"
//                                "QGroupBox{border:none;background:%2;}"
//                                "QPushButton{background:transparent;border:none;border-radius:0px}"
//                                "QPushButton:hover{color:%3;background-color:%4}")
//                            .arg(textColor).arg(background).arg(hover_textColor).arg(hover_backgroundColor));
//    }else{
//        this->setStyleSheet(QString("QWidget{font:15px;color:%1}"
//                                "QGroupBox{border:none;background-color:%2;}"
//                                "QPushButton{background:transparent;border:none;border-radius:0px}"
//                                "QPushButton:hover{color:%3;background-color:%4}")
//                            .arg(textColor).arg(background).arg(hover_textColor).arg(hover_backgroundColor));
//    }

    if (hasButtonMode(NoCloseButton)) {
        m_closeButton->setVisible(false);
    } else {
        if(!hasCloseButtonIcon()){
            m_closeButton->setStyleSheet("QPushButton{font:bold;border:none;border-radius:0px}"
                                         "QPushButton:hover{background-color:rgb(232,17,35)}");
            m_closeButton->setText("X");//⨯✗✘（✕）✖X❌
        }
        else{
            m_closeButton->setStyleSheet("QPushButton:hover{background-color:rgb(232,17,35)}");
        }
        connect(m_closeButton, &QPushButton::clicked, this,[=]{p->close();});
    }

    if (hasButtonMode(NoMaxButton)) {
        m_maximizeButton->setVisible(false);
    } else {
        if(!hasMaximizeButtonIcon()){
            m_maximizeButton->setStyleSheet("QPushButton{font:bold;border:none;border-radius:0px}"
                                "QPushButton:hover{color:rgb(93,94,95);background-color:black}");
            m_maximizeButton->setText("█");
        }
        connect(m_maximizeButton, &QPushButton::clicked, this,[=]{
            if(m_isMax){
                p->showNormal();
                m_isMax = false;
            }else{
                p->showMaximized();
                m_isMax = true;
            }
        });
    }

    if (hasButtonMode(NoMinButton)) {
        m_minimizeButton->setVisible(false);
    } else {
        if(!hasMinimizeButtonIcon()){m_minimizeButton->setText("━");}
                connect(m_minimizeButton, &QPushButton::clicked, this,[=]{p->showMinimized();});
    }

    return;

    const int right = this->width();
    const int size = this->height();
    m_iconLabel->setGeometry(0, 0, size, size);
    m_titleLable->setGeometry(size+5,0,700,size);
    int pos = 1;
    // config closeButton
    if(mode & NoCloseButton){
        m_closeButton->hide();
    }
    else{
        m_closeButton->setGeometry(right - size, 0, size, size);
        if(!hasCloseButtonIcon()){
            m_closeButton->setStyleSheet("QPushButton{font:bold;border:none;border-radius:0px}"
                                       "QPushButton:hover{background-color:rgb(232,17,35)}");
            m_closeButton->setText("X");//⨯✗✘（✕）✖X❌
        }
        else{
            m_closeButton->setStyleSheet("QPushButton:hover{background-color:rgb(232,17,35)}");
        }
        connect(m_closeButton, &QPushButton::clicked, this,[=]{p->close();});
        pos++;

    }

    // config maximumButton
    if(mode & NoMaxButton){
        m_maximizeButton->hide();
    }
    else{
        m_maximizeButton->setGeometry(right - pos*size, 0, size, size);
        if(!hasMaximizeButtonIcon()){
            m_maximizeButton->setStyleSheet("QPushButton{font:bold;border:none;border-radius:0px}"
                                "QPushButton:hover{color:rgb(93,94,95);background-color:black}");
            m_maximizeButton->setText("█");
        }
        connect(m_maximizeButton, &QPushButton::clicked, this,[=]{
            if(m_isMax){
                p->showNormal();
                m_isMax = false;
            }else{
                p->showMaximized();
                m_isMax = true;
            }
        });
        pos++;
    }

    // config minimumButton
    if(mode & NoMinButton){
        m_minimizeButton->hide();

    }
    else{
        m_minimizeButton->setGeometry(right - pos*size, 0, size, size);
        if(!hasMinimizeButtonIcon()){m_minimizeButton->setText("━");}
        connect(m_minimizeButton, &QPushButton::clicked, this,[=]{p->showMinimized();});
        pos++;
    }
}

void TitleBar::setTitleText(QString title) const
{
    m_titleLable->setText(title);
    m_titleLable->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    p->setWindowTitle(title);
}

void TitleBar::setTitleIcon(QString fileName)
{
    p->setWindowIcon(QIcon(fileName));
    m_iconLabel->setPixmap(makeScaledPixmap(fileName));
    m_iconLabel->setScaledContents(true);
}

void TitleBar::setMinIcon(QString filePath)
{
    if (m_minimizeButtonIcon != nullptr) {
        delete m_minimizeButtonIcon;
        m_minimizeButtonIcon = nullptr;
    }
    m_minimizeButtonIcon = new QIcon(makeScaledPixmap(filePath));
    m_minimizeButton->setIcon(*m_minimizeButtonIcon);
}

void TitleBar::setMaxIcon(QString filePath)
{
    if (m_maximizeButtonIcon != nullptr) {
        delete m_maximizeButtonIcon;
        m_maximizeButtonIcon = nullptr;
    }
    m_maximizeButtonIcon = new QIcon(makeScaledPixmap(filePath));
    m_maximizeButton->setIcon(*m_maximizeButtonIcon);
}

void TitleBar::setCloseIcon(QString filePath)
{
    if (m_closeButtonIcon != nullptr) {
        delete m_closeButtonIcon;
        m_closeButtonIcon = nullptr;
    }
    m_closeButtonIcon = new QIcon(makeScaledPixmap(filePath));
    m_closeButton->setIcon(*m_closeButtonIcon);
}

void TitleBar::setUseGradient(bool use)
{
    m_useGradient = use;
}

bool TitleBar::getUseGradient() const
{
    return m_useGradient;
}

bool TitleBar::hasButtonMode(TitleBarButtonMode mode) const
{
    return m_buttonMode & mode;
}

bool TitleBar::hasMinimizeButtonIcon() const
{
    return m_minimizeButtonIcon != nullptr;
}

bool TitleBar::hasMaximizeButtonIcon() const
{
     return m_maximizeButtonIcon != nullptr;
}

bool TitleBar::hasCloseButtonIcon() const
{
     return m_closeButtonIcon != nullptr;
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = true;
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        m_start = event->globalPosition().toPoint();
#else
        m_start = event->globalPos();
#endif
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_leftButtonPressed)
    {

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        parentWidget()->move(parentWidget()->geometry().topLeft() + event->globalPosition().toPoint() - start);
        start = event->globalPosition().toPoint();
#else
        parentWidget()->move(parentWidget()->geometry().topLeft() + event->globalPos() - m_start);
        m_start = event->globalPos();
#endif
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = false;
    }
}

QPixmap TitleBar::makeScaledPixmap(QString p)
{
    return QPixmap(p).scaled(QSize(this->height(), this->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
