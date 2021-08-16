/****************************************************************************
**
** Author:              wangjun
** E-Mail:              tiredwind@foxmail.com
** Phone Number:        15256527665
** Creation Time:       2021/08/14
**
** Description:
** This is a side bar based on QWidget, like Qt Creator's
**
** Usage:
** -- SideBar sidebar;
** -- sidebar.addAction();
**
** Copyright (c) RnD,  Ltd. Corp.
** 2010 - 2021 All rights reserved
**
****************************************************************************/

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QAction>
#include <QWidget>
#include <QPointer>


class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = 0);
    ~SideBar();

    void addAction(QAction *action);
    QAction *addAction(const QString & text, const QString & icon, const QString & tooltip = "", const QString & shortcut = "");
    void setIndex(int index);

signals:
    void sig_index_changed(int index);

public slots:

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual QSize minimumSizeHint() const;

    QAction *actionAt(const QPoint &at);
    int getIndex();

private:
    QList<QAction *> m_actions;
    QPointer<QAction> m_ac_checked;
    QPointer<QAction> m_ac_over;

    int m_index;
};

#endif // SIDEBAR_H
