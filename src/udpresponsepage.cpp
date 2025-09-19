#include "udpresponsepage.h"

UdpResponsePage::UdpResponsePage(QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout(this)), m_textEdit(new QTextEdit(this))
{
    m_textEdit->setReadOnly(true);
    m_layout->addWidget(m_textEdit);
    setLayout(m_layout);
}

void UdpResponsePage::addResponse(const QString &address, const QByteArray &response)
{
    m_textEdit->append(QString("From %1: %2").arg(address, QString::fromUtf8(response)));
}
