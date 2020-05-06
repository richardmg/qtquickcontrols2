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

#ifdef QT_DEBUG
#define qqc2Debug() if (!m_debug.isEmpty()) qDebug() << m_debug << __FUNCTION__
#else
#define qqc2Debug() if (false) qDebug()
#endif

QT_BEGIN_NAMESPACE

using namespace QQC2;

class QQuickStyleMargins
{
    Q_GADGET

    Q_PROPERTY(int left READ left())
    Q_PROPERTY(int right READ right())
    Q_PROPERTY(int top READ top())
    Q_PROPERTY(int bottom READ bottom())

    QML_NAMED_ELEMENT(StyleMargins)

public:
    QQuickStyleMargins() {}
    QQuickStyleMargins(const QQuickStyleMargins &other) : m_margins(other.m_margins) {}
    QQuickStyleMargins(const QMargins &margins) : m_margins(margins) {}
    QQuickStyleMargins(const QRect &outer, const QRect &inner)
    {
        const int left = inner.left() - outer.left();
        const int top = inner.top() - outer.top();
        const int right = outer.right() - inner.right();
        const int bottom = outer.bottom() - inner.bottom();
        m_margins = QMargins(left, top, right, bottom);
    }

    inline void operator=(const QQuickStyleMargins &other) { m_margins = other.m_margins; }
    inline bool operator==(const QQuickStyleMargins &other) const { return other.m_margins == m_margins; }
    inline bool operator!=(const QQuickStyleMargins &other) const { return other.m_margins != m_margins; }

    inline int left() const { return m_margins.left(); }
    inline int right() const { return m_margins.right(); }
    inline int top() const { return m_margins.top(); }
    inline int bottom() const { return m_margins.bottom(); }

    QMargins m_margins;
};

QDebug operator<<(QDebug debug, const QQuickStyleMargins &padding);

struct ControlGeometry
{
    // 'minimumSize' size should be the minimum possible size that the item can have
    // (_without_ taking content size into consideration) and still render correctly.
    // This will also then be the size of the nine patch image. If the
    // QQuickStyleItem::useNinePatchImage is set to false, the image size will be overwritten
    // to be the same as the control size (since we we're then not supposed to scale the image).

    // 'implicitSize' should reflect the preferred size of the item, taking the
    // given content size (as set from QML) into account (But note that not all controls
    // have contents, e.g slider).

    // 'contentRect' should be the free space where the contents can be placed. Note that
    // this rect does not need to have the same size as the contentSize provided as input
    // to the style item. QStyle will typically calculate a rect that is bigger.

    // 'layoutRect' can be set to shift the position of the whole control so
    // that aligns correctly with other controls.

    QSize minimumSize;
    QSize implicitSize;
    QRect contentRect;
    QRect layoutRect;
};

QDebug operator<<(QDebug debug, const ControlGeometry &cg);

class QQuickStyleItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QQuickControl *control MEMBER m_control)
    Q_PROPERTY(qreal contentWidth READ contentWidth WRITE setContentWidth)
    Q_PROPERTY(qreal contentHeight READ contentHeight WRITE setContentHeight)
    Q_PROPERTY(QQuickStyleMargins contentPadding READ contentPadding() NOTIFY contentPaddingChanged)
    Q_PROPERTY(QQuickStyleMargins insets READ insets() NOTIFY insetsChanged)
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

    QQuickStyleMargins contentPadding() const;
    QQuickStyleMargins insets() const;

    void markGeometryDirty();
    void markImageDirty();

signals:
    void contentPaddingChanged();
    void insetsChanged();

protected:
    void componentComplete() override;
    QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void updatePolish() override;

    virtual void connectToControl();
    virtual void paintEvent(QPainter *painter) = 0;
    virtual ControlGeometry calculateControlGeometry() = 0;

    void initStyleOptionBase(QStyleOption &styleOption);

    inline QSize contentSize() { return m_contentSize.toSize(); }
    inline static QStyle *style() { return QQuickNativeStyle::style(); }
    template <class T> inline const T* control() const { return static_cast<T *>(m_control.data()); }

#ifdef QT_DEBUG
    QString m_debug;
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
