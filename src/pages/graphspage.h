#ifndef GRAPHSPAGE_H
#define GRAPHSPAGE_H
#include <QWidget>
#include "../../deps/external/libmodbus/src/modbus.h"
#include "../../deps/external/libmodbus/src/modbus-tcp.h"

extern "C" {
#include "../../deps/external/libmodbus/src/modbus.h"
#include "../../deps/external/libmodbus/src/modbus-tcp.h"
}

#include "../graphwidget.h"

class GraphsPage : public QWidget {
    Q_OBJECT
public:
    explicit GraphsPage(QWidget *parent = nullptr);

private:
    GraphWidget *m_eegGraph;
    GraphWidget *m_graph2;
    GraphWidget *m_graph3;
    GraphWidget *m_graph4;
    QTimer *m_pollTimer;
    modbus_t *m_modbusCtx;
    void pollEEG();
};
#endif // GRAPHSPAGE_H
