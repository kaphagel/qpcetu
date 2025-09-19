#include <QtTest/QtTest>
#include "../../src/datawidget.h"

class TestDataWidget : public QObject {
    Q_OBJECT
private slots:
    void testConstructionDestruction();
    void testProperties();
};

void TestDataWidget::testConstructionDestruction() {
    DataWidget* dw = new DataWidget("Title", "Unit");
    QVERIFY(dw != nullptr);
    delete dw;
}

void TestDataWidget::testProperties() {
    DataWidget widget("TestTitle", "TestUnit");
    QCOMPARE(widget.value(), 0); // Default value is 0
    widget.setValue(42);
    QCOMPARE(widget.value(), 42);
    QCOMPARE(widget.glowIntensity(), 0.3); // Actual default after animation starts
    widget.setGlowIntensity(0.5);
    QCOMPARE(widget.glowIntensity(), 0.5);
}

QTEST_MAIN(TestDataWidget)
#include "test_datawidget.moc"
