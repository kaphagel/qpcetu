#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>

class OverviewPage : public QWidget {
    Q_OBJECT
public:
    explicit OverviewPage(QWidget *parent = nullptr);
    ~OverviewPage() = default;

signals:
    void iconClicked(int pageIndex);

private:
    QGridLayout *m_gridLayout;
};

#endif // OVERVIEWPAGE_H
