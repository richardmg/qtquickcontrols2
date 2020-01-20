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
    node->setTexture(texture);
    node->setBounds(boundingRect());
    node->setDevicePixelRatio(window()->devicePixelRatio());
    node->setPadding(m_ninePatchGeometry.padding.left(),
                     m_ninePatchGeometry.padding.top(),
                     m_ninePatchGeometry.padding.right(),
                     m_ninePatchGeometry.padding.bottom());
    node->update();

    return node;
}

void QQuickStyleItem::initStyleOptionBase(QStyleOption &styleOption)
{
    styleOption.control = m_control;
    styleOption.window = window();
    styleOption.palette = QQuickItemPrivate::get(m_control)->palette()->toQPalette();
    styleOption.rect = QRect(QPoint(0, 0), m_ninePatchGeometry.imageSize);
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

    QQC2_DEBUG(styleOption);
}

void QQuickStyleItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    m_dirty.setFlag(DirtyFlag::Geometry);
    if (!m_useNinePatchImage) {
        // Since the image has the same size as
        // the control, we need to repaint it.
        m_dirty.setFlag(DirtyFlag::Image);
    }
    polish();
}

void QQuickStyleItem::updateControlGeometry()
{
    // The cg.controlSize size should reflect the preferred size of the control, taking
    // the given content size (as set from QML) into account. (But note that not all
    // controls have contents, e.g slider).
    // cg.ninePatchGeometry.imageSize size should be the minimum possible size that an
    // image needs to have (_without_ taking content size into consideration) to be able
    // to paint the control onto it, and scale it correctly (taking to content rect into
    // consideration). If the style tells us to not use a nine patch image, the image size
    // will be overwritten below to be the same as the control size (since we we're not
    // supposed to scale the image).
    m_dirty.setFlag(DirtyFlag::Geometry, false);
    // Clear these properties, so we don't use their old values by
    // accident anywhere while calculating the new ones.
    m_ninePatchGeometry = NinePatchGeometry();
    m_padding = QMargins();

    ControlGeometry cg = calculateControlGeometry();

#ifdef QT_DEBUG
    if (cg.controlSize.isEmpty())
        qmlWarning(this) << "controlSize is not set (or is empty)";
    if (cg.ninePatchGeometry.imageSize.isEmpty())
        qmlWarning(this) << "imageSize is not set (or is empty)";
#endif

    const QMargins newPadding = cg.contentPadding();
    if (m_padding != newPadding) {
        m_padding = newPadding;
        emit paddingChanged();
    }

    setImplicitSize(cg.controlSize.width(), cg.controlSize.height());
    // Clear the dirty flag after setting implicit size, since the call
    // to geometryChanged() will set it again, which is unnecessary.
    m_dirty.setFlag(DirtyFlag::Geometry, false);

    if (m_useNinePatchImage)
        m_ninePatchGeometry = cg.ninePatchGeometry;
    else
        m_ninePatchGeometry.imageSize = size().toSize();
}

void QQuickStyleItem::paintControlToImage()
{
    if (m_ninePatchGeometry.imageSize.isEmpty())
        return;

    m_dirty.setFlag(DirtyFlag::Image, false);
    const qreal scale = window()->devicePixelRatio();
    m_paintedImage = QImage(m_ninePatchGeometry.imageSize * scale, QImage::Format_ARGB32_Premultiplied);
    m_paintedImage.setDevicePixelRatio(scale);
    m_paintedImage.fill(Qt::transparent);

#ifdef QT_DEBUG
    if (m_debug)
        m_paintedImage.fill(QColor(rand() % 255, rand() % 255, rand() % 255, 50));
#endif

    QPainter painter(&m_paintedImage);
    paintEvent(&painter);
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
    Q_ASSERT(m_control);

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

int QQuickStyleItem::topPadding()
{
    return m_padding.top();
}

int QQuickStyleItem::bottomPadding()
{
    return m_padding.bottom();
}

int QQuickStyleItem::leftPadding()
{
    return m_padding.left();
}

int QQuickStyleItem::rightPadding()
{
    return m_padding.right();
}

QT_END_NAMESPACE
