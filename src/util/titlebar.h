#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

enum TitleBarButtonMode {
    DefaultButton =      0x00,
    NoMinButton =       0x01,
    NoMaxButton =       0x02,
    NoCloseButton =     0x04,
    NoMinAndMaxButton = 0x03
};

Q_DECLARE_FLAGS(TitleBarButtonModes, TitleBarButtonMode)
Q_DECLARE_OPERATORS_FOR_FLAGS(TitleBarButtonModes)

enum TitleBarColorStyle {
    Black = 0,
    White
};

class TitleBar : public QGroupBox
{
    Q_OBJECT

public:
    TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void initUi(TitleBarColorStyle style = TitleBarColorStyle::Black, TitleBarButtonMode mode = TitleBarButtonMode::DefaultButton);
    void setTitleText(QString title) const;
    void setTitleIcon(QString filePath);
    void setMinIcon(QString filePath);
    void setMaxIcon(QString filePath);
    void setCloseIcon(QString filePath);
    void setUseGradient(bool use);
    bool getUseGradient() const;
    bool hasButtonMode(TitleBarButtonMode mode) const;
    bool hasMinimizeButtonIcon() const;
    bool hasMaximizeButtonIcon() const;
    bool hasCloseButtonIcon() const;

//    void setTitle(const QString &title) = delete;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_leftButtonPressed;
    bool m_useGradient;
    bool m_isMax = false;

    QPoint m_start;
    TitleBarButtonModes m_buttonMode;
    QWidget *p;
    QHBoxLayout *m_layout;
    QLabel *m_iconLabel;
    QLabel *m_titleLable;
    QIcon *m_minimizeButtonIcon;
    QIcon *m_maximizeButtonIcon;
    QIcon *m_closeButtonIcon;
    QPushButton *m_minimizeButton;
    QPushButton *m_maximizeButton;
    QPushButton *m_closeButton;

    QPixmap makeScaledPixmap(QString p);

};

#endif // TITLEBAR_H
