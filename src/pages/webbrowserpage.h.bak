#ifndef WEBBROWSERPAGE_H
#define WEBBROWSERPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QUrl>

// Forward declarations to avoid hard dependency
class QWebEngineView;
class QWebEnginePage;

/**
 * @brief Web browser page using QWebEngineView for rendering controller web interfaces
 * 
 * This page provides a Chromium-based web view for displaying controller web interfaces.
 * Designed as a comparison/alternative to the native Qt widget XML transformation approach.
 * 
 * Features:
 * - Full Chromium rendering engine
 * - Touch-optimized navigation controls
 * - Address bar for URL input
 * - Back/Forward/Reload controls
 * - Progress indicator
 * - Industrial styling
 */
class WebBrowserPage : public QWidget
{
    Q_OBJECT

public:
    explicit WebBrowserPage(QWidget *parent = nullptr);
    ~WebBrowserPage();

    /**
     * @brief Load a specific URL in the browser
     * @param url The URL to load (e.g., "http://192.168.10.243")
     */
    void loadUrl(const QString &url);

    /**
     * @brief Set the controller URL to display
     * @param ip Controller IP address
     * @param page Optional page path (default: empty for root)
     */
    void setControllerUrl(const QString &ip, const QString &page = QString());

signals:
    /**
     * @brief Emitted when page loading starts
     */
    void loadStarted();

    /**
     * @brief Emitted when page loading finishes
     * @param success True if page loaded successfully
     */
    void loadFinished(bool success);

    /**
     * @brief Emitted when the URL changes
     * @param url New URL
     */
    void urlChanged(const QUrl &url);

private slots:
    void onLoadStarted();
    void onLoadFinished(bool success);
    void onLoadProgress(int progress);
    void onUrlChanged(const QUrl &url);
    void onAddressBarReturnPressed();
    void onBackButtonClicked();
    void onForwardButtonClicked();
    void onReloadButtonClicked();
    void onHomeButtonClicked();

private:
    void setupUI();
    void applyIndustrialStyling();
    void updateNavigationButtons();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_toolbarLayout;
    QHBoxLayout *m_navigationLayout;
    
    // Navigation controls (large touch targets)
    QPushButton *m_backButton;
    QPushButton *m_forwardButton;
    QPushButton *m_reloadButton;
    QPushButton *m_homeButton;
    QLineEdit *m_addressBar;
    QPushButton *m_goButton;
    
    QProgressBar *m_progressBar;
    QLabel *m_statusLabel;
    
    // WebEngine components (nullptr if not available)
    QWebEngineView *m_webView;
    
    QString m_homeUrl;
    bool m_webEngineAvailable;
};

#endif // WEBBROWSERPAGE_H
