#ifndef CONTROLLERCARDWIDGET_H
#define CONTROLLERCARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QDateTime>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

/**
 * @brief Modern controller card widget for industrial HMI interface
 *
 * Displays real-time controller information in a card format with:
 * - Controller type and status indicators
 * - IP address and connection status
 * - Key operational metrics (temperature, power, etc.)
 * - Quick action buttons
 * - Modern styling with hover effects and animations
 */
class ControllerCardWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor statusColor READ statusColor WRITE setStatusColor)

public:
    enum ControllerStatus
    {
        Disconnected,
        Connecting,
        Connected,
        Running,
        Warning,
        Error
    };

    explicit ControllerCardWidget(const QString &controllerType,
                                  const QString &ipAddress,
                                  QWidget *parent = nullptr);
    ~ControllerCardWidget() = default;

    // Getters
    QString controllerType() const { return m_controllerType; }
    QString ipAddress() const { return m_ipAddress; }
    ControllerStatus status() const { return m_status; }
    QColor statusColor() const { return m_statusColor; }

    // Setters
    void setStatus(ControllerStatus status);
    void setStatusColor(const QColor &color);
    void setTemperature(double temp);
    void setPowerConsumption(double power);
    void setConnectionQuality(int quality);
    void updateLastSeen();

signals:
    void cardClicked(const QString &ipAddress);
    void configureRequested(const QString &ipAddress);
    void diagnosticsRequested(const QString &ipAddress);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onConfigureClicked();
    void onDiagnosticsClicked();
    void updatePulseAnimation();

private:
    void setupUI();
    void setupStyling();
    void updateStatusIndicator();
    void animateStatusChange();
    QString getStatusText() const;
    QColor getStatusColor() const;
    QString getControllerIcon() const;

    // Core data
    QString m_controllerType;
    QString m_ipAddress;
    ControllerStatus m_status;
    QColor m_statusColor;

    // Metrics
    double m_temperature;
    double m_powerConsumption;
    int m_connectionQuality;
    QDateTime m_lastSeen;

    // UI Components
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_headerLayout;
    QHBoxLayout *m_metricsLayout;
    QHBoxLayout *m_actionsLayout;

    // Header
    QLabel *m_iconLabel;
    QLabel *m_typeLabel;
    QLabel *m_statusIndicator;
    QLabel *m_ipLabel;

    // Metrics
    QLabel *m_temperatureLabel;
    QLabel *m_powerLabel;
    QProgressBar *m_connectionBar;
    QLabel *m_lastSeenLabel;

    // Actions
    QPushButton *m_configureButton;
    QPushButton *m_diagnosticsButton;

    // Visual effects
    QGraphicsDropShadowEffect *m_shadowEffect;
    QPropertyAnimation *m_pulseAnimation;
    QTimer *m_pulseTimer;
    bool m_isHovered;

    // Animation properties
    int m_pulseValue;
};

#endif // CONTROLLERCARDWIDGET_H