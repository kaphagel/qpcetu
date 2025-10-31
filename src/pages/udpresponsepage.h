#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
class UdpResponsePage : public QWidget {
    Q_OBJECT
public:
    explicit UdpResponsePage(QWidget *parent = nullptr);
    void addResponse(const QString &address, const QByteArray &response);
private:
    QVBoxLayout *m_layout;
    QTextEdit *m_textEdit;
};
