#include <QtTest/QtTest>
#include "../../src/animatedprogressbar.h"

class TestAnimatedProgressBar : public QObject {
    Q_OBJECT
private slots:
    void testConstructionDestruction();
    void testProperties();
};

void TestAnimatedProgressBar::testConstructionDestruction() {
    AnimatedProgressBar* apb = new AnimatedProgressBar();
    QVERIFY(apb != nullptr);
    delete apb;
}

void TestAnimatedProgressBar::testProperties() {
    AnimatedProgressBar bar;
    QCOMPARE(bar.value(), -1); // Actual default value for QProgressBar
    bar.QProgressBar::setValue(77); // Set value directly, bypass animation
    QCOMPARE(bar.value(), 77);
    QCOMPARE(bar.animationOffset(), 0.0); // Default offset is 0.0
    bar.setAnimationOffset(1.0);
    QCOMPARE(bar.animationOffset(), 1.0);
}

QTEST_MAIN(TestAnimatedProgressBar)
#include "test_animatedprogressbar.moc"
