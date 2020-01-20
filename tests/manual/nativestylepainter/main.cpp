#include <QtGui/qguiapplication.h>
#include <QtGui/qrasterwindow.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>
#include <QtCore/qdebug.h>

#include "qnativecommonstyle.h"
#include "qnativestyleoption.h"

class RasterWindow : public QRasterWindow
{
public:

    RasterWindow()
    {
        m_commonStyle.m_window = this;
    }

    void paintEvent(QPaintEvent *) override;
    void drawButton(QPainter *p);

    QCommonStyle m_commonStyle;
    QStyle *m_style = &m_commonStyle;
};

void RasterWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));

    drawButton(&p);
}

void RasterWindow::drawButton(QPainter *p)
{
    QStyleOptionButton option;
    option.rect = QRect(10, 10, 100, 50);
    option.text = QStringLiteral("Push me");
    m_style->drawControl(QStyle::CE_PushButton, &option, p);

}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    RasterWindow window;
    window.resize(680, 420);
    window.show();

    return app.exec();
}
