#include "toolbar.h"

#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>


ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
    this->setMinimumHeight(28);
    this->setProperty("styleID", "ToolBar");

    main_layout = new QHBoxLayout();
    main_layout->setMargin(0);
    main_layout->setSpacing(6);
    this->setLayout(main_layout);
}

ToolBar::~ToolBar()
{

}

void ToolBar::addWidget(QWidget *widget)
{
    main_layout->addWidget(widget);
}

void ToolBar::insertWidget(int index, QWidget *widget)
{
    main_layout->insertWidget(index, widget);
}

void ToolBar::addSpacing(int size)
{
    main_layout->addSpacing(size);
}

void ToolBar::addSpacerItem()
{
    main_layout->addStretch(0);
}

void ToolBar::addSeparator()
{

}
