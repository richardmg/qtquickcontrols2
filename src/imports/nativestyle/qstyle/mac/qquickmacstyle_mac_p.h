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

#ifndef QMACSTYLE_MAC_P_H
#define QMACSTYLE_MAC_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qquickcommonstyle.h"

QT_BEGIN_NAMESPACE

class QPalette;

namespace QQC2 {

class QStyleOptionButton;
class QMacStylePrivate;

class QMacStyle : public QCommonStyle
{
    Q_OBJECT
public:
    QMacStyle();
    virtual ~QMacStyle();

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p) const;
    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p) const;
    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p) const;

    QRect subElementRect(SubElement r, const QStyleOption *opt) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc) const;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, const QPoint &pt) const;

    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt, const QSize &contentsSize) const;
    QFont font(ControlElement element, const QStyle::State state) const;

    int pixelMetric(PixelMetric pm, const QStyleOption *opt = 0) const;
    virtual int styleHint(StyleHint sh, const QStyleOption *opt = 0, QStyleHintReturn *shret = 0) const;

    QPixmap standardPixmap(StandardPixmap sp, const QStyleOption *opt) const;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const;

    virtual void drawItemText(QPainter *p, const QRect &r, int flags, const QPalette &pal,
                              bool enabled, const QString &text,
                              QPalette::ColorRole textRole  = QPalette::NoRole) const;

    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = 0) const;

private:
    Q_DISABLE_COPY_MOVE(QMacStyle)
    Q_DECLARE_PRIVATE(QMacStyle)
};

} // namespace QQC2

QT_END_NAMESPACE

#endif // QMACSTYLE_MAC_P_H
