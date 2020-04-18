/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qquickstyleitem.h"

#include <QtQml/qqmlinfo.h>
#include <QtQuick/qsgninepatchnode.h>
#include <QtQuick/private/qquickwindow_p.h>

#include <QtQuickTemplates2/private/qquickcontrol_p.h>
#include <QtQuickTemplates2/private/qquickbutton_p.h>

#include <QtQml/qqml.h>

#include "qquickstyleitembutton.h"
#include "qquickstylehelper_p.h"

QT_BEGIN_NAMESPACE

QStyle *QQuickStyleItem::s_style = nullptr;

QDebug operator<<(QDebug debug, const QQuickStylePadding &padding)
{
    QDebugStateSaver saver(debug);
    debug.nospace();
    debug << "StylePadding(";
    debug << padding.left() << ", ";
    debug << padding.top() << ", ";
    debug << padding.right() << ", ";
    debug << padding.bottom();
    debug << ')';
    return debug;
}

QQuickStyleItem::QQuickStyleItem()
{
    setFlag(QQuickItem::ItemHasContents);
}

QQuickStyleItem::~QQuickStyleItem()
{
}

void QQuickStyleItem::connectToControl()
{
    connect(this, &QQuickStyleItem::enabledChanged, this, &QQuickStyleItem::markImageDirty);
    connect(this, &QQuickStyleItem::activeFocusChanged, this, &QQuickStyleItem::markImageDirty);
    connect(this, &QQuickStyleItem::windowChanged, this, &QQuickStyleItem::markImageDirty);
    connect(window(), &QQuickWindow::activeChanged, this, &QQuickStyleItem::markImageDirty);
}

void QQuickStyleItem::markImageDirty()
{
    m_dirty.setFlag(DirtyFlag::Image);
    polish();
}

void QQuickStyleItem::markGeometryDirty()
{
    m_dirty.setFlag(DirtyFlag::Geometry);
    polish();
}

QSGNode *QQuickStyleItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGNinePatchNode *node = static_cast<QSGNinePatchNode *>(oldNode);
    if (!node)
        node = window()->createNinePatchNode();

    auto texture = window()->createTextureFromImage(m_paintedImage, QQuickWindow::TextureCanUseAtlas);
    const QSize padding = m_useNinePatchImage ? m_controlGeometry.imageSize / 2 : QSize(0, 0);

    node->setTexture(texture);
    node->setBounds(boundingRect());
    node->setDevicePixelRatio(window()->devicePixelRatio());
    node->setPadding(padding.width(), padding.height(), padding.width(), padding.height());
    node->update();

    return node;
}

void QQuickStyleItem::initStyleOptionBase(QStyleOption &styleOption)
{
    styleOption.control = m_control;
    styleOption.window = window();
    styleOption.palette = QQuickItemPrivate::get(m_control)->palette()->toQPalette();
    styleOption.rect = QRect(QPoint(0, 0), m_controlGeometry.imageSize);
    styleOption.direction = m_control->isMirrored() ? Qt::RightToLeft : Qt::LeftToRight;

    styleOption.state = QStyle::State_None;

    if (m_control->isEnabled())
        styleOption.state |= QStyle::State_Enabled;
    if (m_control->hasVisualFocus())
        styleOption.state |= QStyle::State_HasFocus;
    if (m_control->isUnderMouse())
        styleOption.state |= QStyle::State_MouseOver;
    if (styleOption.window->isActive())
        styleOption.state |= QStyle::State_Active;

    // TODO: add proper API for small and mini
    if (m_control->metaObject()->indexOfProperty("qqc2_style_small") != -1)
        styleOption.state |= QStyle::State_Small;
    if (m_control->metaObject()->indexOfProperty("qqc2_style_mini") != -1)
        styleOption.state |= QStyle::State_Mini;

#ifdef QT_DEBUG
    if (m_debug)
        qDebug() << Q_FUNC_INFO << styleOption;
#endif
}

void QQuickStyleItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    // Note that a change in geometry should not lead us into
    // recalculating the styling based geometry, as that will
    // change our implicitSize and controlSize, which will
    // cause a binding loop.
    if (!m_useNinePatchImage) {
        // Since the image has the same size as
        // the control, we need to repaint it.
        m_dirty.setFlag(DirtyFlag::Image);
        polish();
    } else {
        update();
    }
}

void QQuickStyleItem::updateControlGeometry()
{
    m_dirty.setFlag(DirtyFlag::Geometry, false);
    const QQuickStylePadding oldBackgroundPadding = backgroundPadding();
    const QQuickStylePadding oldContentPadding = contentPadding();
    m_controlGeometry = calculateControlGeometry();

#ifdef QT_DEBUG
    if (m_controlGeometry.controlSize.isEmpty())
        qmlWarning(this) << "controlSize is not set (or is empty)";
    if (m_controlGeometry.imageSize.isEmpty())
        qmlWarning(this) << "imageSize is not set (or is empty)";
#endif

    if (backgroundPadding() != oldBackgroundPadding)
        emit backgroundPaddingChanged();

    if (contentPadding() != oldContentPadding)
        emit contentPaddingChanged();

    // Implicitt size is the same as contentRect.size pluss content
    // padding. Note that this size was calculated from qstyle, and
    // can differ from the content size assigned to us from QML.
    setImplicitSize(m_controlGeometry.backgroundRect.width(), m_controlGeometry.backgroundRect.height());
    // Clear the dirty flag after setting implicit size, since the following call
    // to geometryChanged() might set it again, which is unnecessary.
    m_dirty.setFlag(DirtyFlag::Geometry, false);

    if (!m_useNinePatchImage)
        m_controlGeometry.imageSize = size().toSize();

#ifdef QT_DEBUG
    if (m_debug)
        qDebug() << Q_FUNC_INFO
                 << m_controlGeometry
                 << "bounding rect:" << boundingRect()
                 << "background padding:" << backgroundPadding()
                 << "content padding:" << contentPadding();
#endif
}

void QQuickStyleItem::paintControlToImage()
{
    if (m_controlGeometry.imageSize.isEmpty())
        return;

    m_dirty.setFlag(DirtyFlag::Image, false);
    const qreal scale = window()->devicePixelRatio();
    m_paintedImage = QImage(m_controlGeometry.imageSize * scale, QImage::Format_ARGB32_Premultiplied);
    m_paintedImage.setDevicePixelRatio(scale);
    m_paintedImage.fill(Qt::transparent);

    QPainter painter(&m_paintedImage);
    paintEvent(&painter);

#ifdef QT_DEBUG
    if (m_debug)
        painter.fillRect(m_paintedImage.rect(), QColor(rand() % 255, rand() % 255, rand() % 255, 50));
#endif

    update();
}

void QQuickStyleItem::updatePolish()
{
    if (m_dirty.testFlag(DirtyFlag::Geometry))
        updateControlGeometry();
    if (m_dirty.testFlag(DirtyFlag::Image))
        paintControlToImage();
}

void QQuickStyleItem::componentComplete()
{
    Q_ASSERT_X(m_control, Q_FUNC_INFO, "You need to assign a value to property 'control'");

#ifdef QT_DEBUG
    if (qEnvironmentVariable("QQC2_USE_NINEPATCH_IMAGE") == QStringLiteral("false"))
        m_useNinePatchImage = false;
    if (qEnvironmentVariable("QQC2_DEBUG") == QStringLiteral("true")
            && m_control->objectName() == QLatin1String("debug"))
        m_debug = true;
#endif

    QQuickItem::componentComplete();
    connectToControl();
    polish();
}

qreal QQuickStyleItem::contentWidth()
{
    return m_contentSize.width();
}

void QQuickStyleItem::setContentWidth(qreal contentWidth)
{
    if (qFuzzyCompare(m_contentSize.width(), contentWidth))
        return;

    m_contentSize.setWidth(contentWidth);
    markGeometryDirty();
}

qreal QQuickStyleItem::contentHeight()
{
    return m_contentSize.height();
}

void QQuickStyleItem::setContentHeight(qreal contentHeight)
{
    if (qFuzzyCompare(m_contentSize.height(), contentHeight))
        return;

    m_contentSize.setHeight(contentHeight);
    markGeometryDirty();
}

QQuickStylePadding QQuickStyleItem::backgroundPadding() const
{
    QMargins m;
    const ControlGeometry &cg = m_controlGeometry;
    m.setLeft(cg.backgroundRect.left());
    m.setTop(cg.backgroundRect.top());
    m.setRight(cg.controlSize.width() - cg.backgroundRect.right() - 1);
    m.setBottom(cg.controlSize.height() - cg.backgroundRect.bottom() - 1);
    return QQuickStylePadding(m);
}

QQuickStylePadding QQuickStyleItem::contentPadding() const
{
    QMargins m;
    const ControlGeometry &cg = m_controlGeometry;
    m.setLeft(cg.contentRect.left());
    m.setTop(cg.contentRect.top());
    m.setRight(cg.controlSize.width() - cg.contentRect.right() - 1);
    m.setBottom(cg.controlSize.height() - cg.contentRect.bottom() - 1);
    return QQuickStylePadding(m);
}

QT_END_NAMESPACE