#include "sidebar.h"

#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#define action_height 60


SideBar::SideBar(QWidget *parent) : QWidget(parent)
{
    m_ac_checked = 0;
    m_ac_over = 0;
    m_index = 0;

    setMouseTracking(true);
}

SideBar::~SideBar()
{

}

void SideBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    int action_y = 0;
    p.fillRect(rect(), QColor(250, 250, 250));
    for(int i = 0; i < m_actions.size(); i++)
    {
        QRect sideRect(0, action_y, 2, action_height);
        QRect actionRect(2, action_y, event->rect().width()-2, action_height);

        if (m_actions[i]->isChecked()) {
            p.fillRect(sideRect, QColor(61, 159, 249));
            p.fillRect(actionRect, QColor(204, 236, 255));
        }

        if (m_actions[i] == m_ac_over) {
            p.fillRect(sideRect, QColor(206, 212, 218));
            p.fillRect(actionRect, QColor(206, 212, 218));
        }

        p.setPen(QColor(95, 95, 95));
        QSize size = p.fontMetrics().size(Qt::TextSingleLine, m_actions[i]->text());
        QRect actionTextRect(QPoint(actionRect.width() / 2 - size.width() / 2, actionRect.bottom() - size.height() - 5), size);
        p.drawText(actionTextRect, Qt::AlignCenter, m_actions[i]->text());

        QRect actionIconRect(0, action_y + 10, actionRect.width(), actionRect.height() - 2 * actionTextRect.height());
        QIcon actionIcon(m_actions[i]->icon());
        actionIcon.paint(&p, actionIconRect);

        action_y += actionRect.height();
    }
}

QSize SideBar::minimumSizeHint() const
{
    return action_height * QSize(1, m_actions.size());
}

void SideBar::addAction(QAction *action)
{
    m_actions.push_back(action);
    action->setCheckable(true);
    update();
}

QAction *SideBar::addAction(const QString &text, const QIcon &icon)
{
    QAction *action = new QAction(icon, text, this);
    action->setCheckable(true);
    m_actions.push_back(action);
    update();
    return action;
}

void SideBar::setIndex(int index)
{
    m_index = index;
    m_ac_checked = m_actions[m_index];
    m_ac_checked ->setChecked(true);
    update();
}

void SideBar::mousePressEvent(QMouseEvent *event)
{
    QAction *tempAction = actionAt(event->pos());
    if (tempAction == 0 || tempAction->isChecked())
        return;

    for(int i = 0; i < m_actions.size(); i++)
    {
        if(tempAction == m_actions[i])
        {
            m_index = i;
            break;
        }
    }

    if (m_ac_checked)
        m_ac_checked->setChecked(false);

    if (m_ac_over == tempAction)
        m_ac_over = 0;

    m_ac_checked = tempAction;
    tempAction->setChecked(true);
    update();
    emit sig_index_changed(m_index);

    QWidget::mousePressEvent(event);
}

void SideBar::mouseMoveEvent(QMouseEvent *event)
{
    QAction *tempAction = actionAt(event->pos());
    if (tempAction == 0)
    {
        m_ac_over = 0;
        update();
        return;
    }
    if (tempAction->isChecked() || m_ac_over == tempAction)
        return;
    m_ac_over = tempAction;
    update();

    QWidget::mouseMoveEvent(event);
}

void SideBar::leaveEvent(QEvent *event)
{
    m_ac_over = 0;
    update();

    QWidget::leaveEvent(event);
}

QAction *SideBar::actionAt(const QPoint &at)
{
    int action_y = 0;
    for(int i = 0; i < m_actions.size(); i++)
    {
        QRect actionRect(0, action_y, rect().width(), action_height);
        if (actionRect.contains(at))
            return m_actions[i];
        action_y += actionRect.height();
    }
    return 0;
}

int SideBar::getIndex()
{
    return m_index;
}

#undef action_height
