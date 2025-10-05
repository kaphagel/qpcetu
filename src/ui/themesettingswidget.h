#ifndef THEMESETTINGSWIDGET_H
#define THEMESETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QFrame>
#include "thememanager.h"

/**
 * @brief Theme selection widget for HMI settings
 *
 * Provides touch-friendly theme selection with live preview
 * for industrial operators to choose appropriate themes.
 */
class ThemeSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeSettingsWidget(QWidget *parent = nullptr);

private slots:
    void onThemeChanged(ThemeManager::Theme theme);

private:
    void setupUI();
    void setupStyling();
    void updateThemeButtons();
    void createThemeButton(ThemeManager::Theme theme, const QString &name, const QString &description);

    QVBoxLayout *m_mainLayout;
    QLabel *m_titleLabel;
    QLabel *m_descriptionLabel;
    QHBoxLayout *m_buttonsLayout;
    QButtonGroup *m_themeGroup;

    QPushButton *m_darkThemeBtn;
    QPushButton *m_lightThemeBtn;
    QPushButton *m_highContrastBtn;

    QFrame *m_previewFrame;
    QLabel *m_previewLabel;
};

#endif // THEMESETTINGSWIDGET_H