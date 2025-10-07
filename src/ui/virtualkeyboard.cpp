#include "virtualkeyboard.h"
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QLabel>

VirtualKeyboard::VirtualKeyboard(QWidget *parent)
    : QWidget(parent)
    , m_layout(nullptr)
    , m_targetWidget(nullptr)
    , m_keyboardVisible(false)
    , m_numbersWidget(nullptr)
    , m_lettersWidget(nullptr)
    , m_controlsWidget(nullptr)
{
    // Make it a regular embedded widget (no special window flags)
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);  // Prevent keyboard from stealing focus
    
    initializeKeyboard();
    applyTouchStyling();
    
    // Start hidden
    hide();
}

VirtualKeyboard::~VirtualKeyboard()
{
    // Cleanup handled by Qt's parent-child system
}

void VirtualKeyboard::initializeKeyboard()
{
    m_layout = new QHBoxLayout(this);  // Changed to horizontal layout
    m_layout->setContentsMargins(8, 8, 8, 8);
    m_layout->setSpacing(12);
    
    // Create main keyboard area (letters + controls) on the left
    QWidget* mainKeyboardWidget = new QWidget();
    QVBoxLayout* mainKeyboardLayout = new QVBoxLayout(mainKeyboardWidget);
    mainKeyboardLayout->setSpacing(8);
    
    // Create simplified letter pad for basic text input
    m_lettersWidget = createLetterPad();
    mainKeyboardLayout->addWidget(m_lettersWidget);
    
    // Create control buttons
    m_controlsWidget = createControlPad();
    mainKeyboardLayout->addWidget(m_controlsWidget);
    
    // Add main keyboard to left side
    m_layout->addWidget(mainKeyboardWidget, 2);  // Give it more space
    
    // Create number pad on the right side (like standard keyboard)
    m_numbersWidget = createNumberPad();
    m_layout->addWidget(m_numbersWidget, 1);  // Less space for numpad
    
    // Set fixed height for embedded widget (width will be controlled by parent layout)
    setFixedHeight(400);  // Increased height for larger buttons
    setMinimumWidth(1000);  // Increased width for better layout
    
    qDebug() << "Widget-based virtual keyboard initialized successfully";
}

QWidget* VirtualKeyboard::createNumberPad()
{
    QWidget* numberWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(numberWidget);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    
    // Title for number pad
    QLabel* title = new QLabel("Numbers");
    title->setStyleSheet("font-weight: bold; color: white; font-size: 14px;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);
    
    // Create grid layout for numbers
    QGridLayout* numberLayout = new QGridLayout();
    numberLayout->setSpacing(6);
    
    // Standard numpad layout: 7,8,9 / 4,5,6 / 1,2,3 / 0,.,- 
    QStringList numbers = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", ".", "-"};
    
    int row = 0, col = 0;
    for (const QString& num : numbers) {
        QPushButton* btn = new QPushButton(num);
        
        // Much larger buttons for touch screen
        if (num == "0") {
            btn->setMinimumSize(180, 65);  // Wide zero button
            btn->setMaximumSize(200, 75);
        } else {
            btn->setMinimumSize(85, 65);   // Larger square buttons
            btn->setMaximumSize(100, 75);
        }
        
        btn->setFocusPolicy(Qt::NoFocus);  // Prevent buttons from stealing focus
        btn->setStyleSheet(
            "QPushButton {"
            "  background-color: #3a3a3a;"
            "  color: white;"
            "  border: 1px solid #555;"
            "  border-radius: 8px;"
            "  font-size: 18px;"      // Larger font
            "  font-weight: bold;"
            "}"
            "QPushButton:pressed {"
            "  background-color: #555;"
            "  border: 1px solid #777;"
            "}"
        );
        
        connect(btn, &QPushButton::clicked, [this, num]() {
            onKeyPressed(num);
        });
        
        // Special layout for zero (spans 2 columns)
        if (num == "0") {
            numberLayout->addWidget(btn, row, 0, 1, 2);  // Span 2 columns
            col = 2;  // Move to next position
        } else {
            numberLayout->addWidget(btn, row, col);
            col++;
        }
        
        if (col > 2) {
            col = 0;
            row++;
        }
    }
    
    mainLayout->addLayout(numberLayout);
    mainLayout->addStretch();  // Push content to top
    
    return numberWidget;
}

QWidget* VirtualKeyboard::createLetterPad()
{
    QWidget* letterWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(letterWidget);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    
    // Title for letters
    QLabel* title = new QLabel("Letters");
    title->setStyleSheet("font-weight: bold; color: white; font-size: 14px;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);
    
    QGridLayout* letterLayout = new QGridLayout();
    letterLayout->setSpacing(4);
    
    // Simplified QWERTY layout for industrial use
    QStringList letters = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "A", "S", "D", "F", "G", "H", "J", "K", "L",
        "Z", "X", "C", "V", "B", "N", "M"
    };
    
    int row = 0, col = 0;
    int maxCols[3] = {10, 9, 7}; // Different row lengths for QWERTY
    
    for (const QString& letter : letters) {
        QPushButton* btn = new QPushButton(letter);
        
        // Much larger buttons for touch screen
        btn->setMinimumSize(65, 55);   // Increased from 45x40
        btn->setMaximumSize(75, 65);   // Increased from 55x45
        
        btn->setFocusPolicy(Qt::NoFocus);  // Prevent buttons from stealing focus
        btn->setStyleSheet(
            "QPushButton {"
            "  background-color: #2c2c2c;"
            "  color: white;"
            "  border: 1px solid #444;"
            "  border-radius: 6px;"     // Slightly larger radius
            "  font-size: 16px;"        // Larger font
            "  font-weight: 500;"
            "}"
            "QPushButton:pressed {"
            "  background-color: #444;"
            "  border: 1px solid #666;"
            "}"
        );
        
        connect(btn, &QPushButton::clicked, [this, letter]() {
            onKeyPressed(letter);
        });
        
        letterLayout->addWidget(btn, row, col);
        
        col++;
        if (col >= maxCols[row]) {
            col = 0;
            row++;
        }
    }
    
    mainLayout->addLayout(letterLayout);
    mainLayout->addStretch();  // Push content to top
    
    return letterWidget;
}

QWidget* VirtualKeyboard::createControlPad()
{
    QWidget* controlWidget = new QWidget();
    QHBoxLayout* controlLayout = new QHBoxLayout(controlWidget);
    controlLayout->setSpacing(12);  // Increased spacing for larger buttons
    
    // Space button
    QPushButton* spaceBtn = new QPushButton("SPACE");
    spaceBtn->setMinimumSize(220, 60);  // Much larger
    spaceBtn->setMaximumSize(250, 70);
    spaceBtn->setFocusPolicy(Qt::NoFocus);  // Prevent focus stealing
    connect(spaceBtn, &QPushButton::clicked, [this]() {
        onKeyPressed(" ");
    });
    
    // Backspace button
    QPushButton* backspaceBtn = new QPushButton("⌫");
    backspaceBtn->setMinimumSize(100, 60);  // Larger
    backspaceBtn->setMaximumSize(120, 70);
    backspaceBtn->setFocusPolicy(Qt::NoFocus);  // Prevent focus stealing
    connect(backspaceBtn, &QPushButton::clicked, this, &VirtualKeyboard::onBackspacePressed);
    
    // Enter button
    QPushButton* enterBtn = new QPushButton("ENTER");
    enterBtn->setMinimumSize(100, 60);  // Larger
    enterBtn->setMaximumSize(120, 70);
    enterBtn->setFocusPolicy(Qt::NoFocus);  // Prevent focus stealing
    connect(enterBtn, &QPushButton::clicked, this, &VirtualKeyboard::onEnterPressed);
    
    // Clear button
    QPushButton* clearBtn = new QPushButton("CLEAR");
    clearBtn->setMinimumSize(100, 60);  // Larger
    clearBtn->setMaximumSize(120, 70);
    clearBtn->setFocusPolicy(Qt::NoFocus);  // Prevent focus stealing
    connect(clearBtn, &QPushButton::clicked, this, &VirtualKeyboard::onClearPressed);
    
    // Apply styling to control buttons
    QString controlStyle = 
        "QPushButton {"
        "  background-color: #4a4a4a;"
        "  color: white;"
        "  border: 1px solid #666;"
        "  border-radius: 8px;"        // Larger radius
        "  font-size: 16px;"           // Larger font
        "  font-weight: bold;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #666;"
        "  border: 1px solid #888;"
        "}";
    
    spaceBtn->setStyleSheet(controlStyle);
    backspaceBtn->setStyleSheet(controlStyle);
    enterBtn->setStyleSheet(controlStyle);
    clearBtn->setStyleSheet(controlStyle);
    
    controlLayout->addWidget(clearBtn);
    controlLayout->addWidget(backspaceBtn);
    controlLayout->addWidget(spaceBtn);
    controlLayout->addWidget(enterBtn);
    
    return controlWidget;
}

void VirtualKeyboard::applyTouchStyling()
{
    setStyleSheet(
        "VirtualKeyboard {"
        "  background-color: #2c3136;"  // Solid background for app window
        "  border: 2px solid #444;"
        "  border-radius: 12px;"
        "  margin: 8px;"
        "}"
    );
}

void VirtualKeyboard::show()
{
    if (!m_keyboardVisible) {
        m_keyboardVisible = true;
        QWidget::show();
        emit keyboardVisibilityChanged(true);
        qDebug() << "Virtual keyboard shown (embedded widget)";
    }
}

void VirtualKeyboard::hide()
{
    if (m_keyboardVisible) {
        m_keyboardVisible = false;
        QWidget::hide();
        emit keyboardVisibilityChanged(false);
        qDebug() << "Virtual keyboard hidden (embedded widget)";
    }
}

bool VirtualKeyboard::isVisible() const
{
    return m_keyboardVisible;
}

void VirtualKeyboard::setTargetWidget(QWidget* widget)
{
    m_targetWidget = widget;
    
    if (widget) {
        // Ensure the target widget has focus
        widget->setFocus();
        qDebug() << "Virtual keyboard target set to:" << widget->objectName();
    }
}

void VirtualKeyboard::installInputEventFilter(QWidget* widget)
{
    if (widget) {
        InputEventFilter* filter = new InputEventFilter(this, widget);
        widget->installEventFilter(filter);
        
        // Connect signals
        connect(filter, &InputEventFilter::inputFocusIn, this, &VirtualKeyboard::onInputFocusIn);
        connect(filter, &InputEventFilter::inputFocusOut, this, &VirtualKeyboard::onInputFocusOut);
        
        qDebug() << "Input event filter installed on:" << widget->objectName();
    }
}

void VirtualKeyboard::onInputFocusIn(QWidget* widget)
{
    // Only show for text input widgets
    if (qobject_cast<QLineEdit*>(widget) || qobject_cast<QTextEdit*>(widget)) {
        setTargetWidget(widget);
        show();
    }
}

void VirtualKeyboard::onInputFocusOut()
{
    // Hide keyboard when focus is lost, with longer delay to prevent flickering
    QTimer::singleShot(500, this, [this]() {
        // Check if focus moved to keyboard itself or if target widget still has focus
        QWidget* focusWidget = QApplication::focusWidget();
        if (!focusWidget || 
            (!isAncestorOf(focusWidget) && focusWidget != m_targetWidget)) {
            hide();
        }
    });
}

bool VirtualKeyboard::eventFilter(QObject *watched, QEvent *event)
{
    // Handle keyboard-specific events if needed
    return QWidget::eventFilter(watched, event);
}

void VirtualKeyboard::onKeyPressed(const QString& key)
{
    insertText(key);
}

void VirtualKeyboard::onBackspacePressed()
{
    if (m_targetWidget) {
        if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(m_targetWidget)) {
            lineEdit->backspace();
        } else if (QTextEdit* textEdit = qobject_cast<QTextEdit*>(m_targetWidget)) {
            QTextCursor cursor = textEdit->textCursor();
            cursor.deletePreviousChar();
            textEdit->setTextCursor(cursor);
        }
    }
}

void VirtualKeyboard::onEnterPressed()
{
    insertText("\n");
}

void VirtualKeyboard::onClearPressed()
{
    if (m_targetWidget) {
        if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(m_targetWidget)) {
            lineEdit->clear();
        } else if (QTextEdit* textEdit = qobject_cast<QTextEdit*>(m_targetWidget)) {
            textEdit->clear();
        }
    }
}

void VirtualKeyboard::insertText(const QString& text)
{
    if (m_targetWidget) {
        // Ensure target widget still has focus
        if (!m_targetWidget->hasFocus()) {
            m_targetWidget->setFocus();
        }
        
        if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(m_targetWidget)) {
            lineEdit->insert(text);
        } else if (QTextEdit* textEdit = qobject_cast<QTextEdit*>(m_targetWidget)) {
            textEdit->insertPlainText(text);
        }
        
        // Ensure target widget maintains focus after text insertion
        m_targetWidget->setFocus();
    }
}

// InputEventFilter implementation
InputEventFilter::InputEventFilter(VirtualKeyboard* keyboard, QObject* parent)
    : QObject(parent)
    , m_keyboard(keyboard)
{
}

bool InputEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    QWidget* widget = qobject_cast<QWidget*>(watched);
    if (!widget) {
        return false;
    }
    
    switch (event->type()) {
    case QEvent::FocusIn:
        emit inputFocusIn(widget);
        break;
        
    case QEvent::FocusOut:
        emit inputFocusOut();
        break;
        
    case QEvent::MouseButtonPress:
        // Also trigger on mouse press for touch screen simulation
        if (qobject_cast<QLineEdit*>(widget) || qobject_cast<QTextEdit*>(widget)) {
            widget->setFocus();
        }
        break;
        
    default:
        break;
    }
    
    return false; // Don't consume the event
}