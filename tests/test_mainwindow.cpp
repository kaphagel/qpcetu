#include <QtTest/QtTest>
#include "../src/mainwindow.h"

class TestMainWindow : public QObject {
    Q_OBJECT
private slots:
    void testWindowTitle();
    void testInitialSize();
};

void TestMainWindow::testWindowTitle() {
    MainWindow window;
    QCOMPARE(window.windowTitle(), QString("QUANTUM TACTICAL PROCESSING CENTER - ETU"));
}

void TestMainWindow::testInitialSize() {
    MainWindow window;
    QVERIFY(window.size().width() >= 1200);
    QVERIFY(window.size().height() >= 800);
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
