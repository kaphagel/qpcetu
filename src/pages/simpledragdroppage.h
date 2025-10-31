#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class SimpleDragDropPage : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleDragDropPage(QWidget *parent = nullptr);
    ~SimpleDragDropPage();

signals:
    void backRequested();

private slots:
    void onBackClicked();

private:
    void setupUI();

    QVBoxLayout *m_mainLayout;
    QPushButton *m_backButton;
    QLabel *m_titleLabel;
    QLabel *m_contentLabel;
};
