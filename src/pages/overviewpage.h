#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>
#include <QEvent>

/**
 * @brief iOS-style home page with large touch-optimized navigation cards
 * 
 * Clean, minimal design following Apple Human Interface Guidelines
 * adapted for industrial tablet navigation.
 */
class OverviewPage : public QWidget {
    Q_OBJECT
public:
    explicit OverviewPage(QWidget *parent = nullptr);
    ~OverviewPage() = default;

signals:
    void iconClicked(int pageIndex);

private slots:
    void onThemeChanged();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void createNavigationCard(const QString &title, const QString &subtitle, 
                             const QString &iconPath, int pageIndex);
    void updateCardStyles();
    
    QVBoxLayout *m_mainLayout;
    QGridLayout *m_cardsLayout;
    QLabel *m_welcomeLabel;
    QLabel *m_subtitleLabel;
    QVector<QWidget*> m_cardWidgets;  // Store card references for theme updates
};
