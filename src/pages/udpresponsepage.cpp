// UdpResponsePage implementation
#include "udpresponsepage.h"
#include "../ui/modernmainwindow.h"
#include "../navigation/navigationmanager.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QDateTime>
#include <QTextCursor>

UdpResponsePage::UdpResponsePage(QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout), m_textEdit(new QTextEdit(this))
    {
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->setSpacing(16);
        mainLayout->setContentsMargins(16, 16, 16, 16);

        // Top app bar with back/home button
        QWidget *topBar = new QWidget;
        QHBoxLayout *topLayout = new QHBoxLayout(topBar);
        topLayout->setContentsMargins(0, 0, 0, 0);
        topLayout->setSpacing(12);
        
        QPushButton *homeBtn = new QPushButton("🏠 Back to Overview");
        homeBtn->setMinimumSize(160, 44); // Touch-friendly size
        homeBtn->setMaximumSize(160, 44);
        homeBtn->setStyleSheet(
            "QPushButton {"
            "  background: #007AFF;"
            "  color: white;"
            "  border: none;"
            "  border-radius: 8px;"
            "  padding: 8px 16px;"
            "  font-weight: bold;"
            "  font-size: 14px;"
            "}"
            "QPushButton:hover {"
            "  background: #0051D0;"
            "}"
            "QPushButton:pressed {"
            "  background: #003d99;"
            "}"
        );
        homeBtn->setToolTip("Navigate back to the main overview page");
        topLayout->addWidget(homeBtn, 0, Qt::AlignLeft);
        
        QLabel *titleLabel = new QLabel("🌐 Network Discovery Monitor");
        titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #007AFF; background: transparent;");
        topLayout->addWidget(titleLabel, 1, Qt::AlignLeft);
        topLayout->addStretch();
        
        // Add test button for simulating UDP responses in development/testing
        QPushButton *testBtn = new QPushButton("📡 Test Response");
        testBtn->setStyleSheet("QPushButton { background: #007AFF; color: white; border: none; border-radius: 8px; padding: 8px 16px; font-weight: bold; } QPushButton:pressed { background: #0051D0; }");
        testBtn->setToolTip("Click to simulate a UDP response for testing");
        connect(testBtn, &QPushButton::clicked, this, [this]() {
            static int testCounter = 1;
            QString testAddress = QString("192.168.10.%1").arg(100 + testCounter);
            QByteArray testResponse = QString("Protocol version = 1.00;FB type = EPIC%1;Module version = 1.99;MAC = C0-22-F1-41-03-%2;IP = %3;Port = 502;Status = Running;Uptime = %4s")
                .arg(testCounter % 5 == 0 ? "5" : "4")
                .arg(QString::number(0x30 + testCounter, 16).toUpper().rightJustified(2, '0'))
                .arg(testAddress)
                .arg(testCounter * 3600 + 1234).toUtf8();
            addResponse(testAddress, testResponse);
            testCounter++;
        });
        topLayout->addWidget(testBtn);
        
        mainLayout->addWidget(topBar);
        
        // Add information panel
        QLabel *infoLabel = new QLabel(
            "📡 <b>Network Discovery Monitor</b><br><br>"
            "This page displays real-time UDP responses from industrial controllers on the network.<br>"
            "• <b>Live Mode:</b> Real responses from EPIC4/EPIC5/SNAP_PAC controllers<br>"
            "• <b>Test Mode:</b> Click 'Test Response' to simulate controller responses<br>"
            "• <b>Format:</b> Each response shows source IP and full protocol data<br><br>"
            "<i>In WSL/Docker environments, use the Test button to simulate network responses.</i>"
        );
        infoLabel->setStyleSheet("QLabel { background: #f0f0f0; border: 1px solid #ddd; border-radius: 8px; padding: 16px; margin: 8px 0; }");
        infoLabel->setWordWrap(true);
        mainLayout->addWidget(infoLabel);
        
        // Configure text edit for better display
        m_textEdit->setStyleSheet("QTextEdit { background: #ffffff; border: 2px solid #007AFF; border-radius: 8px; padding: 12px; font-family: 'Courier New', monospace; font-size: 12px; }");
        m_textEdit->setPlaceholderText("UDP responses will appear here...\nClick 'Test Response' to simulate controller responses in development environments.");
        
        mainLayout->addWidget(m_textEdit);
        connect(homeBtn, &QPushButton::clicked, this, [this]() {
            QWidget *mw = this->window();
            if (auto mainWin = qobject_cast<ModernMainWindow*>(mw)) {
                mainWin->navigateToPage(NavigationManager::PageId::Overview);
            }
        });
        setLayout(mainLayout);
}

void UdpResponsePage::addResponse(const QString &address, const QByteArray &response)
{
    qDebug() << "📝 UdpResponsePage::addResponse called - From:" << address << "Data:" << response;
    
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString responseText = QString::fromUtf8(response);
    
    // Format the response nicely
    QString formattedEntry = QString("[%1] 🌐 %2\n📦 %3\n%4\n")
        .arg(timestamp)
        .arg(address)
        .arg(responseText)
        .arg(QString("-").repeated(80));
    
    m_textEdit->append(formattedEntry);
    
    // Auto-scroll to bottom
    QTextCursor cursor = m_textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    m_textEdit->setTextCursor(cursor);
}
