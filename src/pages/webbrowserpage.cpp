#include "webbrowserpage.h"
#include "../ui/thememanager.h"
#include <QMessageBox>
#include <QDebug>

// Try to include QWebEngineView, but handle if not available
#ifdef QT_WEBENGINEWIDGETS_LIB
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWebEngineHistory>
#define WEBENGINE_AVAILABLE
#endif

WebBrowserPage::WebBrowserPage(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_toolbarLayout(nullptr)
    , m_navigationLayout(nullptr)
    , m_backButton(nullptr)
    , m_forwardButton(nullptr)
    , m_reloadButton(nullptr)
    , m_homeButton(nullptr)
    , m_addressBar(nullptr)
    , m_goButton(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
    , m_webView(nullptr)
    , m_homeUrl("http://192.168.10.243")
    , m_webEngineAvailable(false)
{
    setupUI();
    applyIndustrialStyling();
    
#ifdef WEBENGINE_AVAILABLE
    m_webEngineAvailable = true;
    qDebug() << "WebBrowserPage: QWebEngineView available and initialized";
#else
    m_webEngineAvailable = false;
    qWarning() << "WebBrowserPage: QWebEngineView not available - Qt5WebEngineWidgets module not found";
    
    // Show error message in the page
    QLabel *errorLabel = new QLabel(
        "⚠️ Web Engine Not Available\n\n"
        "Qt5WebEngineWidgets module is not installed.\n\n"
        "To enable web browsing:\n"
        "1. Install: sudo apt install qtwebengine5-dev\n"
        "2. Rebuild application\n\n"
        "Current XML transformation with native Qt widgets\n"
        "is the recommended approach for industrial HMI.", this);
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setStyleSheet("QLabel { color: #FFB84D; font-size: 16px; padding: 40px; }");
    m_mainLayout->addWidget(errorLabel);
#endif
}

WebBrowserPage::~WebBrowserPage()
{
    // Cleanup handled by Qt parent-child relationship
}

void WebBrowserPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    
    // Toolbar container
    QWidget *toolbarContainer = new QWidget(this);
    m_toolbarLayout = new QVBoxLayout(toolbarContainer);
    m_toolbarLayout->setContentsMargins(12, 12, 12, 12);
    m_toolbarLayout->setSpacing(8);
    
    // Navigation controls layout
    m_navigationLayout = new QHBoxLayout();
    m_navigationLayout->setSpacing(8);
    
    // Back button (large touch target)
    m_backButton = new QPushButton("← Back", this);
    m_backButton->setMinimumSize(100, 60);
    m_backButton->setEnabled(false);
    connect(m_backButton, &QPushButton::clicked, this, &WebBrowserPage::onBackButtonClicked);
    m_navigationLayout->addWidget(m_backButton);
    
    // Forward button
    m_forwardButton = new QPushButton("Forward →", this);
    m_forwardButton->setMinimumSize(100, 60);
    m_forwardButton->setEnabled(false);
    connect(m_forwardButton, &QPushButton::clicked, this, &WebBrowserPage::onForwardButtonClicked);
    m_navigationLayout->addWidget(m_forwardButton);
    
    // Reload button
    m_reloadButton = new QPushButton("🔄 Reload", this);
    m_reloadButton->setMinimumSize(100, 60);
    connect(m_reloadButton, &QPushButton::clicked, this, &WebBrowserPage::onReloadButtonClicked);
    m_navigationLayout->addWidget(m_reloadButton);
    
    // Home button
    m_homeButton = new QPushButton("🏠 Home", this);
    m_homeButton->setMinimumSize(100, 60);
    connect(m_homeButton, &QPushButton::clicked, this, &WebBrowserPage::onHomeButtonClicked);
    m_navigationLayout->addWidget(m_homeButton);
    
    m_navigationLayout->addStretch();
    
    m_toolbarLayout->addLayout(m_navigationLayout);
    
    // Address bar layout
    QHBoxLayout *addressLayout = new QHBoxLayout();
    addressLayout->setSpacing(8);
    
    QLabel *urlLabel = new QLabel("🌐 URL:", this);
    urlLabel->setMinimumHeight(60);
    addressLayout->addWidget(urlLabel);
    
    m_addressBar = new QLineEdit(this);
    m_addressBar->setPlaceholderText("Enter controller URL (e.g., http://192.168.10.243)");
    m_addressBar->setText(m_homeUrl);
    m_addressBar->setMinimumHeight(60);
    connect(m_addressBar, &QLineEdit::returnPressed, this, &WebBrowserPage::onAddressBarReturnPressed);
    addressLayout->addWidget(m_addressBar);
    
    m_goButton = new QPushButton("→ Go", this);
    m_goButton->setMinimumSize(80, 60);
    connect(m_goButton, &QPushButton::clicked, this, &WebBrowserPage::onAddressBarReturnPressed);
    addressLayout->addWidget(m_goButton);
    
    m_toolbarLayout->addLayout(addressLayout);
    
    // Progress bar
    m_progressBar = new QProgressBar(this);
    m_progressBar->setMinimumHeight(8);
    m_progressBar->setMaximumHeight(8);
    m_progressBar->setTextVisible(false);
    m_progressBar->setVisible(false);
    m_toolbarLayout->addWidget(m_progressBar);
    
    m_mainLayout->addWidget(toolbarContainer);
    
    // Status label
    m_statusLabel = new QLabel("Ready", this);
    m_statusLabel->setMinimumHeight(30);
    m_statusLabel->setStyleSheet("QLabel { padding: 4px 12px; }");
    
#ifdef WEBENGINE_AVAILABLE
    // Create web view
    m_webView = new QWebEngineView(this);
    
    // Configure web engine settings for industrial use
    QWebEngineSettings *settings = m_webView->settings();
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    settings->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    
    // Connect signals
    connect(m_webView, &QWebEngineView::loadStarted, this, &WebBrowserPage::onLoadStarted);
    connect(m_webView, &QWebEngineView::loadFinished, this, &WebBrowserPage::onLoadFinished);
    connect(m_webView, &QWebEngineView::loadProgress, this, &WebBrowserPage::onLoadProgress);
    connect(m_webView, &QWebEngineView::urlChanged, this, &WebBrowserPage::onUrlChanged);
    
    m_mainLayout->addWidget(m_webView, 1); // Give it stretch factor
    
    // Load home URL by default
    loadUrl(m_homeUrl);
#endif
    
    m_mainLayout->addWidget(m_statusLabel);
}

void WebBrowserPage::applyIndustrialStyling()
{
    ThemeManager *themeManager = ThemeManager::instance();
    
    QString buttonStyle = QString(
        "QPushButton {"
        "    background-color: %1;"
        "    color: %2;"
        "    border: none;"
        "    border-radius: 8px;"
        "    font-size: 16px;"
        "    font-weight: 600;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: %3;"
        "}"
        "QPushButton:pressed {"
        "    background-color: %4;"
        "}"
        "QPushButton:disabled {"
        "    background-color: %5;"
        "    color: %6;"
        "}"
    ).arg(themeManager->color(ThemeManager::ButtonBackground).name())
     .arg(themeManager->color(ThemeManager::PrimaryText).name())
     .arg(themeManager->color(ThemeManager::ButtonHover).name())
     .arg(themeManager->color(ThemeManager::ButtonPressed).name())
     .arg(themeManager->color(ThemeManager::CardBackground).name())
     .arg(themeManager->color(ThemeManager::SecondaryText).name());
    
    m_backButton->setStyleSheet(buttonStyle);
    m_forwardButton->setStyleSheet(buttonStyle);
    m_reloadButton->setStyleSheet(buttonStyle);
    m_homeButton->setStyleSheet(buttonStyle);
    m_goButton->setStyleSheet(buttonStyle);
    
    QString addressBarStyle = QString(
        "QLineEdit {"
        "    background-color: %1;"
        "    color: %2;"
        "    border: 2px solid %3;"
        "    border-radius: 8px;"
        "    padding: 8px 16px;"
        "    font-size: 16px;"
        "}"
        "QLineEdit:focus {"
        "    border-color: %4;"
        "}"
    ).arg(themeManager->color(ThemeManager::CardBackground).name())
     .arg(themeManager->color(ThemeManager::PrimaryText).name())
     .arg(themeManager->color(ThemeManager::BorderColor).name())
     .arg(themeManager->color(ThemeManager::Primary).name());
    
    m_addressBar->setStyleSheet(addressBarStyle);
    
    QString progressStyle = QString(
        "QProgressBar {"
        "    background-color: %1;"
        "    border: none;"
        "    border-radius: 4px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: %2;"
        "    border-radius: 4px;"
        "}"
    ).arg(themeManager->color(ThemeManager::CardBackground).name())
     .arg(themeManager->color(ThemeManager::Primary).name());
    
    m_progressBar->setStyleSheet(progressStyle);
    
    QString statusStyle = QString(
        "QLabel {"
        "    background-color: %1;"
        "    color: %2;"
        "    border-top: 1px solid %3;"
        "}"
    ).arg(themeManager->color(ThemeManager::MainBackground).name())
     .arg(themeManager->color(ThemeManager::SecondaryText).name())
     .arg(themeManager->color(ThemeManager::BorderColor).name());
    
    m_statusLabel->setStyleSheet(statusStyle);
}

void WebBrowserPage::loadUrl(const QString &url)
{
    if (!m_webEngineAvailable) {
        qWarning() << "WebBrowserPage: Cannot load URL - WebEngine not available";
        return;
    }
    
#ifdef WEBENGINE_AVAILABLE
    QString urlString = url;
    if (!urlString.startsWith("http://") && !urlString.startsWith("https://")) {
        urlString = "http://" + urlString;
    }
    
    qDebug() << "WebBrowserPage: Loading URL:" << urlString;
    m_webView->load(QUrl(urlString));
    m_addressBar->setText(urlString);
#endif
}

void WebBrowserPage::setControllerUrl(const QString &ip, const QString &page)
{
    QString url = QString("http://%1").arg(ip);
    if (!page.isEmpty()) {
        url += "/" + page;
    }
    
    m_homeUrl = url;
    loadUrl(url);
}

void WebBrowserPage::onLoadStarted()
{
    m_progressBar->setVisible(true);
    m_progressBar->setValue(0);
    m_statusLabel->setText("Loading...");
    emit loadStarted();
}

void WebBrowserPage::onLoadFinished(bool success)
{
    m_progressBar->setVisible(false);
    
    if (success) {
        m_statusLabel->setText("✓ Page loaded successfully");
        qDebug() << "WebBrowserPage: Page loaded successfully";
    } else {
        m_statusLabel->setText("✗ Failed to load page");
        qWarning() << "WebBrowserPage: Failed to load page";
    }
    
    updateNavigationButtons();
    emit loadFinished(success);
}

void WebBrowserPage::onLoadProgress(int progress)
{
    m_progressBar->setValue(progress);
    m_statusLabel->setText(QString("Loading... %1%").arg(progress));
}

void WebBrowserPage::onUrlChanged(const QUrl &url)
{
    m_addressBar->setText(url.toString());
    updateNavigationButtons();
    emit urlChanged(url);
}

void WebBrowserPage::onAddressBarReturnPressed()
{
    QString url = m_addressBar->text().trimmed();
    if (!url.isEmpty()) {
        loadUrl(url);
    }
}

void WebBrowserPage::onBackButtonClicked()
{
#ifdef WEBENGINE_AVAILABLE
    if (m_webView && m_webView->history()->canGoBack()) {
        m_webView->back();
    }
#endif
}

void WebBrowserPage::onForwardButtonClicked()
{
#ifdef WEBENGINE_AVAILABLE
    if (m_webView && m_webView->history()->canGoForward()) {
        m_webView->forward();
    }
#endif
}

void WebBrowserPage::onReloadButtonClicked()
{
#ifdef WEBENGINE_AVAILABLE
    if (m_webView) {
        m_webView->reload();
    }
#endif
}

void WebBrowserPage::onHomeButtonClicked()
{
    loadUrl(m_homeUrl);
}

void WebBrowserPage::updateNavigationButtons()
{
#ifdef WEBENGINE_AVAILABLE
    if (m_webView) {
        m_backButton->setEnabled(m_webView->history()->canGoBack());
        m_forwardButton->setEnabled(m_webView->history()->canGoForward());
    }
#endif
}
