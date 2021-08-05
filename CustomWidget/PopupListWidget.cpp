#include "PopupListWidget.h"
 
#include <QMenu>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
 
#pragma execution_character_set("utf-8")
 
PopupListWidget::PopupListWidget(QWidget *parent)
	: QToolButton(parent)
{
	// set ToolButton attribute
	this->setPopupMode(QToolButton::InstantPopup);
	this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	this->setIcon(QIcon(":/images/error.png"));
	this->setText("弹出");
 
	m_popup_widget = new QWidgetAction(this);
	m_menu = new QMenu(this);
 
	QPointer<QListWidget> lwd = new QListWidget;
	lwd->setMinimumSize(QSize(400, 400));
	lwd->setViewMode(QListView::IconMode);
	lwd->setIconSize(QSize(80, 80));
	for (int i = 0; i < 10; i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QIcon(":/images/warning.png"), "Test");
		lwd->addItem(item);
	}
 
	QPointer<QVBoxLayout> layout_main = new QVBoxLayout;
	layout_main->addWidget(lwd);
	QPointer<QWidget> default_widget = new QWidget;
	default_widget->setLayout(layout_main);
	m_popup_widget->setDefaultWidget(default_widget);
 
	m_menu->addAction(m_popup_widget);
	this->setMenu(m_menu);
}
 
PopupListWidget::~PopupListWidget()
{
}