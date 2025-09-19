#include <QtTest/QtTest>
#include "../../src/graphwidget.h"

class TestGraphWidget : public QObject {
    Q_OBJECT
private slots:
    void testConstructionDestruction();
    void testProperties();
};

void TestGraphWidget::testConstructionDestruction() {
    GraphWidget* gw = new GraphWidget("Graph", GraphWidget::SineWave);
    QVERIFY(gw != nullptr);
    delete gw;
}

void TestGraphWidget::testProperties() {
    GraphWidget graph("TestGraph", GraphWidget::SineWave);
    // Test public API only
    graph.setColor(Qt::red); // Should not crash
    graph.setRange(-10.0, 10.0); // Should not crash
    graph.addDataPoint(5.5); // Should not crash
    // If you want to verify state, add public getters to GraphWidget
}

QTEST_MAIN(TestGraphWidget)
#include "test_graphwidget.moc"
