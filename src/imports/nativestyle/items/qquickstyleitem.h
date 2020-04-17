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

#ifndef QQUICKSTYLEITEM_H
#define QQUICKSTYLEITEM_H

#include <QtCore/qdebug.h>
#include <QtQml/qqml.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>

#include "qquicknativestyle.h"
#include "qquickstyle.h"
#include "qquickstyleoption.h"

// Work-around for now, to avoid creator getting confused
// about missing macros. Should eventually be defined
// in qt declarative somewhere I assume.
#ifndef QML_NAMED_ELEMENT
#define QML_NAMED_ELEMENT(NAME)
#define QML_UNCREATABLE(NAME)
#endif

QT_BEGIN_NAMESPACE

using namespace QQC2;

class QQuickStylePadding
{
    Q_GADGET

    Q_PROPERTY(int left READ left())
    Q_PROPERTY(int right READ right())
    Q_PROPERTY(int top READ top())
    Q_PROPERTY(int bottom READ bottom())

    QML_NAMED_ELEMENT(StylePadding)

public:
    QQuickStylePadding(const QQuickStylePadding &other) : m_margins(other.m_margins) {}
    QQuickStylePadding(const QMargins &margins) : m_margins(margins) {}
    inline void operator=(const QQuickStylePadding &other) { m_margins = other.m_margins; }
    inline bool operator==(const QQuickStylePadding &other) const { return other.m_margins == m_margins; }
    inline bool operator!=(const QQuickStylePadding &other) const { return other.m_margins != m_margins; }

    inline int left() const { return m_margins.left(); }
    inline int right() const { return m_margins.right(); }
    inline int top() const { return m_margins.top(); }
    inline int bottom() const { return m_margins.bottom(); }

    QMargins m_margins;
};

QDebug operator<<(QDebug debug, const QQuickStylePadding &padding);

class QQuickStyleItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickControl *control MEMBER m_control)

    Q_PROPERTY(qreal contentWidth READ contentWidth WRITE setContentWidth)
    Q_PROPERTY(qreal contentHeight READ contentHeight WRITE setContentHeight)

    Q_PROPERTY(qreal controlWidth READ controlWidth NOTIFY controlWidthChanged)
    Q_PROPERTY(qreal controlHeight READ controlHeight NOTIFY controlHeightChanged)

    Q_PROPERTY(QQuickStylePadding contentPadding READ contentPadding() NOTIFY contentPaddingChanged)

    Q_PROPERTY(bool useNinePatchImage MEMBER m_useNinePatchImage)

    QML_NAMED_ELEMENT(StyleItem)
    QML_UNCREATABLE("StyleItem is an abstract base class.")

public:
    enum DirtyFlag {
        Nothing = 0,
        Geometry,
        Image,
        Everything = 255
    };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    QQuickStyleItem();
    ~QQuickStyleItem() override;

    qreal contentWidth();
    void setContentWidth(qreal contentWidth);
    qreal contentHeight();
    void setContentHeight(qreal contentHeight);

    qreal controlWidth();
    qreal controlHeight();

    QQuickStylePadding contentPadding() const;

    void markGeometryDirty();
    void markImageDirty();

signals:
    void contentPaddingChanged();
    void controlWidthChanged();
    void controlHeightChanged();

protected:
    void componentComplete() override;
    QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void updatePolish() override;

    virtual void connectToControl();
    virtual void paintEvent(QPainter *painter) = 0;
    virtual ControlGeometry calculateControlGeometry() = 0;

    void initStyleOptionBase(QStyleOption &styleOption);

    inline QSize contentSize() { return m_contentSize.toSize(); }
    inline static QStyle *style() { return QQuickNativeStyle::style(); }
    template <class T> inline const T* control() const { return static_cast<T *>(m_control.data()); }

#ifdef QT_DEBUG
    bool m_debug = false;
#endif

private:
    inline void updateControlGeometry();
    inline void paintControlToImage();

private:
    QPointer<QQuickControl> m_control;
    QImage m_paintedImage;
    ControlGeometry m_controlGeometry;
    QSizeF m_contentSize;

    DirtyFlags m_dirty = Everything;
    bool m_useNinePatchImage = true;

private:
    static QStyle *s_style;
    friend class QtQuickControls2MacOSStylePlugin;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QQuickStyleItem::DirtyFlags)
QML_DECLARE_TYPE(QQuickStyleItem)

QT_END_NAMESPACE

#endif // QQUICKSTYLEITEM_H
