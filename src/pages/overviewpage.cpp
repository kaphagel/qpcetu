#include "overviewpage.h"
#include "../ui/thememanager.h"
#include <QFont>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QFrame>

OverviewPage::OverviewPage(QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(32);
    m_mainLayout->setContentsMargins(40, 40, 40, 40);

    // Welcome section - iOS style
    m_welcomeLabel = new QLabel("Welcome");
    QFont welcomeFont("SF Pro Display", 34, QFont::Bold);
    m_welcomeLabel->setFont(welcomeFont);
    m_welcomeLabel->setAlignment(Qt::AlignLeft);
    
    m_subtitleLabel = new QLabel("Select a category to get started");
    QFont subtitleFont("SF Pro Text", 17, QFont::Normal);
    m_subtitleLabel->setFont(subtitleFont);
    m_subtitleLabel->setAlignment(Qt::AlignLeft);
    
    // Apply theme colors
    ThemeManager *theme = ThemeManager::instance();
    m_welcomeLabel->setStyleSheet(QString("color: %1; background: transparent; padding: 0px;")
        .arg(theme->colorString(ThemeManager::PrimaryText)));
    m_subtitleLabel->setStyleSheet(QString("color: %1; background: transparent; padding: 0px; margin-bottom: 16px;")
        .arg(theme->colorString(ThemeManager::SecondaryText)));
    
    m_mainLayout->addWidget(m_welcomeLabel);
    m_mainLayout->addWidget(m_subtitleLabel);
    m_mainLayout->addSpacing(8);

    // Navigation cards grid - uniform 2 column layout
    m_cardsLayout = new QGridLayout();
    m_cardsLayout->setSpacing(20);
    m_cardsLayout->setContentsMargins(0, 0, 0, 0);
    m_cardsLayout->setColumnStretch(0, 1);  // Equal column widths
    m_cardsLayout->setColumnStretch(1, 1);

    // Create navigation cards with iOS-style design
    struct CardInfo {
        QString title;
        QString subtitle;
        QString iconPath;
        int pageIndex;
    };

    CardInfo cards[] = {
        {"Dashboard", "View system status and overview", ":/icons/dashboard.svg", 1},
        {"Graphs", "Real-time data visualization", ":/icons/graphs.svg", 2},
        {"Settings", "Configure system preferences", ":/icons/settings.svg", 3},
        {"UDP Discovery", "Network device scanning", ":/icons/udp.svg", 4},
        {"Industrial Data", "Controller data interface", ":/icons/dragdrop.svg", 8},
        {"Web Browser", "Chromium-based web view", ":/icons/udp.svg", 9}
    };

    // Create cards in a clean grid (cards are added by createNavigationCard)
    for (const auto &card : cards) {
        createNavigationCard(card.title, card.subtitle, card.iconPath, card.pageIndex);
    }

    m_mainLayout->addLayout(m_cardsLayout);
    m_mainLayout->addStretch();

    // Set overall background
    setStyleSheet(QString("OverviewPage { background: %1; }")
        .arg(theme->colorString(ThemeManager::MainBackground)));
    
    // Connect to theme changes
    connect(theme, &ThemeManager::themeChanged, this, &OverviewPage::onThemeChanged);
}

void OverviewPage::onThemeChanged()
{
    ThemeManager *theme = ThemeManager::instance();
    
    // Update page background
    setStyleSheet(QString("OverviewPage { background: %1; }")
        .arg(theme->colorString(ThemeManager::MainBackground)));
    
    // Update welcome labels
    m_welcomeLabel->setStyleSheet(QString("color: %1; background: transparent; padding: 0px;")
        .arg(theme->colorString(ThemeManager::PrimaryText)));
    m_subtitleLabel->setStyleSheet(QString("color: %1; background: transparent; padding: 0px; margin-bottom: 16px;")
        .arg(theme->colorString(ThemeManager::SecondaryText)));
    
    // Update all card styles
    updateCardStyles();
}

void OverviewPage::updateCardStyles()
{
    ThemeManager *theme = ThemeManager::instance();
    
    // Update each card widget's styling
    for (QWidget *card : m_cardWidgets) {
        if (!card) continue;
        
        // Update card background and hover
        QString cardStyle = QString(
            "QWidget {"
            "   background: %1;"
            "   border-radius: 16px;"
            "   border: none;"
            "}"
            "QWidget:hover {"
            "   background: %2;"
            "}"
        ).arg(theme->colorString(ThemeManager::CardBackground))
         .arg(theme->colorString(ThemeManager::ButtonHover));
        
        card->setStyleSheet(cardStyle);
        
        // Find and update child widgets (icon container and labels)
        QList<QWidget*> children = card->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
        for (QWidget *child : children) {
            if (child->objectName() == "iconContainer") {
                child->setStyleSheet(QString(
                    "QWidget {"
                    "   background: %1;"
                    "   border-radius: 16px;"
                    "   border: none;"
                    "}"
                ).arg(theme->colorString(ThemeManager::Primary)));
            }
        }
        
        // Update text labels
        QList<QLabel*> labels = card->findChildren<QLabel*>();
        for (QLabel *label : labels) {
            if (label->objectName() == "cardTitle") {
                label->setStyleSheet(QString("color: %1; background: transparent;")
                    .arg(theme->colorString(ThemeManager::PrimaryText)));
            } else if (label->objectName() == "cardSubtitle") {
                label->setStyleSheet(QString("color: %1; background: transparent;")
                    .arg(theme->colorString(ThemeManager::SecondaryText)));
            } else if (label->objectName() == "cardArrow") {
                label->setStyleSheet(QString("color: %1; background: transparent;")
                    .arg(theme->colorString(ThemeManager::SecondaryText)));
            }
        }
    }
}

void OverviewPage::createNavigationCard(const QString &title, const QString &subtitle, 
                                       const QString &iconPath, int pageIndex)
{
    ThemeManager *theme = ThemeManager::instance();
    
    // Card container with iOS-style design
    QWidget *cardWidget = new QWidget();
    cardWidget->setFixedSize(380, 140); // Large touch target
    cardWidget->setCursor(Qt::PointingHandCursor);
    
    // iOS-style card background with subtle shadow effect
    QString cardStyle = QString(
        "QWidget {"
        "   background: %1;"
        "   border-radius: 16px;"
        "   border: none;"
        "}"
        "QWidget:hover {"
        "   background: %2;"
        "}"
    ).arg(theme->colorString(ThemeManager::CardBackground))
     .arg(theme->colorString(ThemeManager::ButtonHover));
    
    cardWidget->setStyleSheet(cardStyle);
    
    // Card layout
    QHBoxLayout *cardLayout = new QHBoxLayout(cardWidget);
    cardLayout->setContentsMargins(24, 20, 24, 20);
    cardLayout->setSpacing(20);
    
    // Icon container with iOS-style colored background
    QWidget *iconContainer = new QWidget();
    iconContainer->setObjectName("iconContainer");
    iconContainer->setFixedSize(72, 72);
    iconContainer->setStyleSheet(QString(
        "QWidget {"
        "   background: %1;"
        "   border-radius: 16px;"
        "   border: none;"
        "}"
    ).arg(theme->colorString(ThemeManager::Primary)));
    
    QLabel *iconLabel = new QLabel(iconContainer);
    iconLabel->setPixmap(QIcon(iconPath).pixmap(QSize(44, 44)));
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setGeometry(14, 14, 44, 44);
    iconLabel->setStyleSheet("background: transparent; border: none;");
    
    // Text content
    QWidget *textContainer = new QWidget();
    textContainer->setStyleSheet("background: transparent; border: none;");
    QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(6);
    
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("cardTitle");
    QFont titleFont("SF Pro Display", 19, QFont::DemiBold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet(QString("color: %1; background: transparent;")
        .arg(theme->colorString(ThemeManager::PrimaryText)));
    
    QLabel *subtitleLabel = new QLabel(subtitle);
    subtitleLabel->setObjectName("cardSubtitle");
    QFont subtitleFont("SF Pro Text", 14, QFont::Normal);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setStyleSheet(QString("color: %1; background: transparent;")
        .arg(theme->colorString(ThemeManager::SecondaryText)));
    subtitleLabel->setWordWrap(true);
    
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(subtitleLabel);
    textLayout->addStretch();
    
    // Arrow indicator (iOS style)
    QLabel *arrowLabel = new QLabel("›");
    arrowLabel->setObjectName("cardArrow");
    QFont arrowFont("SF Pro Display", 32, QFont::Light);
    arrowLabel->setFont(arrowFont);
    arrowLabel->setStyleSheet(QString("color: %1; background: transparent;")
        .arg(theme->colorString(ThemeManager::SecondaryText)));
    arrowLabel->setAlignment(Qt::AlignCenter);
    arrowLabel->setFixedWidth(24);
    
    cardLayout->addWidget(iconContainer);
    cardLayout->addWidget(textContainer, 1);
    cardLayout->addWidget(arrowLabel);
    
    // Make entire card clickable
    cardWidget->installEventFilter(this);
    cardWidget->setProperty("pageIndex", pageIndex);
    
    // Store card reference for theme updates
    m_cardWidgets.append(cardWidget);
    
    // Add to cards layout
    int row = m_cardsLayout->count() / 2;
    int col = m_cardsLayout->count() % 2;
    m_cardsLayout->addWidget(cardWidget, row, col);
}

bool OverviewPage::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if (widget && widget->property("pageIndex").isValid()) {
            int pageIndex = widget->property("pageIndex").toInt();
            emit iconClicked(pageIndex);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
