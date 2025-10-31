#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QFocusEvent>

/**
 * @brief Touch-optimized virtual keyboard for industrial HMI
 * 
 * This class provides an on-screen virtual keyboard that automatically
 * appears when text input fields are focused, optimized for touch
 * screen industrial environments.
 */
class VirtualKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualKeyboard(QWidget *parent = nullptr);
    ~VirtualKeyboard();

    /**
     * @brief Show the virtual keyboard
     */
    void show();
    
    /**
     * @brief Hide the virtual keyboard
     */
    void hide();
    
    /**
     * @brief Check if keyboard is currently visible
     */
    bool isVisible() const;
    
    /**
     * @brief Set the input field that the keyboard should target
     */
    void setTargetWidget(QWidget* widget);

    /**
     * @brief Install event filter on a widget to auto-show keyboard
     */
    void installInputEventFilter(QWidget* widget);

public slots:
    /**
     * @brief Handle focus in events to show keyboard
     */
    void onInputFocusIn(QWidget* widget);
    
    /**
     * @brief Handle focus out events to hide keyboard
     */
    void onInputFocusOut();

private slots:
    /**
     * @brief Handle key button clicks
     */
    void onKeyPressed(const QString& key);
    
    /**
     * @brief Handle backspace button
     */
    void onBackspacePressed();
    
    /**
     * @brief Handle enter button
     */
    void onEnterPressed();
    
    /**
     * @brief Handle clear button
     */
    void onClearPressed();

signals:
    /**
     * @brief Emitted when keyboard visibility changes
     */
    void keyboardVisibilityChanged(bool visible);

protected:
    /**
     * @brief Custom event filter for input widgets
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QBoxLayout* m_layout;
    QWidget* m_targetWidget;
    bool m_keyboardVisible;
    
    // Keyboard layout widgets
    QWidget* m_numbersWidget;
    QWidget* m_lettersWidget;
    QWidget* m_controlsWidget;
    
    /**
     * @brief Initialize the widget-based virtual keyboard
     */
    void initializeKeyboard();
    
    /**
     * @brief Create number pad layout
     */
    QWidget* createNumberPad();
    
    /**
     * @brief Create letter layout (simplified)
     */
    QWidget* createLetterPad();
    
    /**
     * @brief Create control buttons (backspace, enter, clear)
     */
    QWidget* createControlPad();
    
    /**
     * @brief Apply touch-optimized styling
     */
    void applyTouchStyling();
    
    /**
     * @brief Insert text into target widget
     */
    void insertText(const QString& text);
};

/**
 * @brief Input event filter class for automatic keyboard management
 */
class InputEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit InputEventFilter(VirtualKeyboard* keyboard, QObject* parent = nullptr);

signals:
    void inputFocusIn(QWidget* widget);
    void inputFocusOut();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    VirtualKeyboard* m_keyboard;
};
