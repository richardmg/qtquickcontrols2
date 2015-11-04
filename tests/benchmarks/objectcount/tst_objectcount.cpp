/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QtTest>
#include <QtQuick>
#include <QtCore/private/qhooks_p.h>

static int qt_verbose = qgetenv("VERBOSE").toInt() != 0;

Q_GLOBAL_STATIC(QObjectList, qt_qobjects)

extern "C" Q_DECL_EXPORT void qt_addQObject(QObject *object)
{
    qt_qobjects->append(object);
}

extern "C" Q_DECL_EXPORT void qt_removeQObject(QObject *object)
{
    qt_qobjects->removeAll(object);
}

class tst_ObjectCount : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void calendar();
    void calendar_data();

    void legacy();
    void legacy_data();

    void controls();
    void controls_data();

private:
    QQmlEngine engine;
};

void tst_ObjectCount::init()
{
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&qt_addQObject);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(&qt_removeQObject);

    // warmup
    QQmlComponent component(&engine);
    component.setData("import QtQuick 2.0; import QtQuick.Controls 1.3 as C1; import Qt.labs.controls 1.0 as C2; Row { C1.Button {} C2.Button {} }", QUrl());
    delete component.create();
}

void tst_ObjectCount::cleanup()
{
    qtHookData[QHooks::AddQObject] = 0;
    qtHookData[QHooks::RemoveQObject] = 0;
}

static void printItems(const QList<QQuickItem *> &items)
{
    qInfo() << "QQuickItems:" << items.count() << "(total of QObjects:" << qt_qobjects->count() << ")";
    if (qt_verbose) {
        foreach (QObject *object, *qt_qobjects)
            qInfo() << "\t" << object;
    }
}

static void addTestRows(const QString &path)
{
    QFileInfoList entries = QDir(path).entryInfoList(QStringList("*.qml"), QDir::Files);
    foreach (const QFileInfo &entry, entries)
        QTest::newRow(qPrintable(entry.baseName())) << QUrl::fromLocalFile(entry.absoluteFilePath());
}

static void doBenchmark(QQmlEngine *engine, const QUrl &url)
{
    QQmlComponent component(engine);

    qt_qobjects->clear();

    component.loadUrl(url);
    QScopedPointer<QObject> object(component.create());
    QVERIFY2(object.data(), qPrintable(component.errorString()));

    QList<QQuickItem *> items;
    foreach (QObject *object, *qt_qobjects()) {
        QQuickItem *item = qobject_cast<QQuickItem *>(object);
        if (item)
            items += item;
    }
    printItems(items);
}

void tst_ObjectCount::calendar()
{
    QFETCH(QUrl, url);
    doBenchmark(&engine, url);
}

void tst_ObjectCount::calendar_data()
{
    QTest::addColumn<QUrl>("url");
    addTestRows(QQC2_IMPORT_PATH "/calendar");
}

void tst_ObjectCount::legacy()
{
    QFETCH(QByteArray, data);

    QQmlComponent component(&engine);

    qt_qobjects->clear();

    component.setData(data, QUrl());
    QScopedPointer<QObject> object(component.create());
    QVERIFY2(object.data(), qPrintable(component.errorString()));

    QList<QQuickItem *> items;
    foreach (QObject *object, *qt_qobjects()) {
        QQuickItem *item = qobject_cast<QQuickItem *>(object);
        if (item)
            items += item;
    }
    printItems(items);
}

void tst_ObjectCount::legacy_data()
{
    QTest::addColumn<QByteArray>("data");

    QTest::newRow("ApplicationWindow")
            << QByteArray("import QtQuick.Controls 1.3; ApplicationWindow { }");
    QTest::newRow("BusyIndicator")
            << QByteArray("import QtQuick.Controls 1.3; BusyIndicator { }");
    QTest::newRow("Button")
            << QByteArray("import QtQuick.Controls 1.3; Button { }");
    QTest::newRow("CheckBox")
            << QByteArray("import QtQuick.Controls 1.3; CheckBox { }");
    QTest::newRow("Dial")
            << QByteArray("import QtQuick.Extras 1.3; Dial { }");
    QTest::newRow("GroupBox")
            << QByteArray("import QtQuick.Controls 1.3; GroupBox { }");
    QTest::newRow("Label")
            << QByteArray("import QtQuick.Controls 1.3; Label { }");
    QTest::newRow("ProgressBar")
            << QByteArray("import QtQuick.Controls 1.3; ProgressBar { }");
    QTest::newRow("RadioButton")
            << QByteArray("import QtQuick.Controls 1.3; RadioButton { }");
    QTest::newRow("ScrollView")
            << QByteArray("import QtQuick.Controls 1.3; ScrollView { }");
    QTest::newRow("Slider")
            << QByteArray("import QtQuick.Controls 1.3; Slider { }");
    QTest::newRow("SpinBox")
            << QByteArray("import QtQuick.Controls 1.3; SpinBox { }");
    QTest::newRow("StackView")
            << QByteArray("import QtQuick.Controls 1.3; StackView { }");
    QTest::newRow("Switch")
            << QByteArray("import QtQuick.Controls 1.3; Switch { }");
    QTest::newRow("TabView")
            << QByteArray("import QtQuick.Controls 1.3; TabView { }");
    QTest::newRow("TextArea")
            << QByteArray("import QtQuick.Controls 1.3; TextArea { }");
    QTest::newRow("TextField")
            << QByteArray("import QtQuick.Controls 1.3; TextField { }");
    QTest::newRow("ToolBar")
            << QByteArray("import QtQuick.Controls 1.3; ToolBar { }");
    QTest::newRow("ToolButton")
            << QByteArray("import QtQuick.Controls 1.3; ToolButton { }");
    QTest::newRow("Tumbler")
            << QByteArray("import QtQuick.Extras 1.3; Tumbler { }");
}

void tst_ObjectCount::controls()
{
    QFETCH(QUrl, url);
    doBenchmark(&engine, url);
}

void tst_ObjectCount::controls_data()
{
    QTest::addColumn<QUrl>("url");
    addTestRows(QQC2_IMPORT_PATH "/controls");
}

QTEST_MAIN(tst_ObjectCount)

#include "tst_objectcount.moc"
