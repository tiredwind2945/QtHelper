#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QPointer>

class QHBoxLayout;


class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void addWidget(QWidget * widget);
    void insertWidget(int index, QWidget * widget);
    void addSpacing(int size);
    void addSpacerItem();
    void addSeparator();

private:
    QPointer<QHBoxLayout> main_layout;
};

#endif // TOOLBAR_H
