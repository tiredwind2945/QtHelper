#include "EditableTableWidget.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QToolButton>
#include <QToolBar>
#include <QMessageBox>
#include <QDropEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>


EditableTableWidget::EditableTableWidget(QWidget *parent) : QWidget(parent)
{
    // initialize widgets and layouts
    m_table = new QTableWidget(this);
    m_table->installEventFilter(this);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    m_table->setDragDropMode(QAbstractItemView::InternalMove);
//    m_table->setDropIndicatorShown(true);
//    m_table->setDragDropMode(QAbstractItemView::DragDrop);
//    m_table->setDragEnabled(true);
//    m_table->setAcceptDrops(true);
    \
    m_toolBar = new QToolBar(this);

    auto spacer_item = new QWidget(this);
    spacer_item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_toolBar->addWidget(spacer_item);

    auto tbn_addRow = this->createToolButton("tbn_addRow", ":/images/add_row.svg", tr("添加一行"));
    auto tbn_insertRow = this->createToolButton("tbn_insertRow", ":/images/insert_row.svg", tr("在选中行下插入一行"));
    auto tbn_moveUp = this->createToolButton("tbn_moveUp", ":/images/move_up.svg", tr("将选中行向上移动"));
    auto tbn_moveDown = this->createToolButton("tbn_moveDown", ":/images/move_down.svg", tr("将选中行向下移动"));
    auto tbn_deleteRow = this->createToolButton("tbn_deleteRow", ":/images/delete_row.svg", tr("删除选中行"));
    auto tbn_clear = this->createToolButton("tbn_clear", ":/images/clear.svg", tr("清除所有"));

    auto main_layout = new QVBoxLayout();
    main_layout->setMargin(0);
    main_layout->addWidget(m_toolBar);
    main_layout->addWidget(m_table);
    this->setLayout(main_layout);

    // signals and slots
    connect(tbn_addRow, SIGNAL(clicked()), this, SLOT(slot_addRow()));
    connect(tbn_insertRow, SIGNAL(clicked()), this, SLOT(slot_insertRow()));
    connect(tbn_moveUp, SIGNAL(clicked()), this, SLOT(slot_moveUp()));
    connect(tbn_moveDown, SIGNAL(clicked()), this, SLOT(slot_moveDown()));
    connect(tbn_deleteRow, SIGNAL(clicked()), this, SLOT(slot_deleteRow()));
    connect(tbn_clear, SIGNAL(clicked()), this, SLOT(slot_clear()));
}

EditableTableWidget::~EditableTableWidget()
{

}

void EditableTableWidget::setVerticalHeaderNames(const QStringList &ls_headerNames)
{
    m_table->setRowCount(ls_headerNames.size());
    m_table->setVerticalHeaderLabels(ls_headerNames);

    m_verticalLabels = ls_headerNames;
}

void EditableTableWidget::setHorizontalHeaderNames(const QStringList &ls_headerNames)
{
    m_table->setColumnCount(ls_headerNames.size());
    m_table->setHorizontalHeaderLabels(ls_headerNames);

    m_horizontalLabels = ls_headerNames;
}

//Json::Value EditableTableWidget::getJsonValueVertical()
//{
//    Json::Value root;

//    for(int i = 0; i < m_table->columnCount(); i++)
//    {
//        Json::Value column_value;
//        for(int j = 0; j < m_verticalLabels.size(); j++)
//        {
//            auto label = m_verticalLabels[j];
//            if(m_table->item(j, i))
//            {
//                if(NARI::VAR::INT_HEADER_LABELS.contains(label))
//                    column_value[m_verticalLabels[j].toStdString()] = m_table->item(j, i)->text().toInt();
//                else column_value[m_verticalLabels[j].toStdString()] = m_table->item(j, i)->text().toStdString();
//            }
//            else
//            {
//                qDebug() << "cell in tablewidget is empty!" << endl;
//                return 0;
//            }
//        }
//        root.append(column_value);
//    }

//    return root;
//}

//Json::Value EditableTableWidget::getJsonValueHorizontal()
//{
//    Json::Value root;

//    for(int i = 0; i < m_table->rowCount(); i++)
//    {
//        Json::Value row_value;
//        for(int j = 0; j < m_horizontalLabels.size(); j++)
//        {
//            auto label = m_horizontalLabels[j];
//            if(m_table->item(i, j))
//            {
//                if(NARI::VAR::INT_HEADER_LABELS.contains(label))
//                    row_value[m_horizontalLabels[j].toStdString()] = m_table->item(i, j)->text().toInt();
//                else row_value[m_horizontalLabels[j].toStdString()] = m_table->item(i, j)->text().toStdString();
//            }
//            else
//            {
//                qDebug() << "cell in tablewidget is empty!" << endl;
//                return 0;
//            }
//        }
//        root.append(row_value);
//    }

//    return root;
//}

void EditableTableWidget::moveRow(int currentRow, int toRow)
{
    int nRowCount = m_table->rowCount();
    int nColumnCount = m_table->columnCount();

    m_table->setFocus();

    if(currentRow == toRow)
        return;

    if(currentRow < 0 || toRow <0 || currentRow > nRowCount || toRow > nRowCount)
        return;

    if(toRow < currentRow)
        currentRow++;

    m_table->insertRow(toRow);

    for(int i = 0; i < nColumnCount; i++)
    {
        m_table->setItem(toRow, i, m_table->takeItem(currentRow, i));
    }
    if(currentRow < toRow)
        toRow--;

    m_table->removeRow(currentRow);
    m_table->selectRow(toRow);
}

QToolButton * EditableTableWidget::createToolButton(const QString &object_name, const QString &icon_url, const QString & tooltip)
{
    auto tbn = new QToolButton(this);
    tbn->setObjectName(object_name);
    tbn->setIcon(QIcon(icon_url));
    tbn->setFixedSize(QSize(25, 25));
    tbn->setToolButtonStyle(/*Qt::ToolButtonTextBesideIcon*/Qt::ToolButtonIconOnly);
    tbn->setToolTip(tooltip);
    m_toolBar->addWidget(tbn);

    return tbn;
}

void EditableTableWidget::slot_addRow()
{
    m_table->insertRow(m_table->rowCount());
    m_table->selectRow(m_table->rowCount() - 1);
}

void EditableTableWidget::slot_insertRow()
{
    m_table->insertRow(m_table->currentRow() + 1);
    m_table->selectRow(m_table->currentRow() + 1);
}

void EditableTableWidget::slot_moveUp()
{
    this->moveRow(m_table->currentRow(), m_table->currentRow() - 1);
}

void EditableTableWidget::slot_moveDown()
{
    this->moveRow(m_table->currentRow(), m_table->currentRow() + 2);
}

void EditableTableWidget::slot_deleteRow()
{
    m_table->removeRow(m_table->currentRow());
}

void EditableTableWidget::slot_clear()
{
    m_table->clear();
    m_table->setRowCount(0);
}

bool EditableTableWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_table->viewport())
    {
        if(event->type() == QEvent::Drop)
        {
            int row_src, row_dst;
            row_src = m_table->currentRow();
            QTableWidgetItem * item = m_table->itemAt(((QDropEvent*)event)->pos());
            if(item)
            {
                row_dst = item->row();
                row_src = (row_src > row_dst ? row_src + 1 : row_src);
                row_dst = (row_src < row_dst ? row_dst + 1 : row_dst);
                m_table->insertRow(row_dst);
            }
            else
            {
                row_dst = m_table->rowCount();
                m_table->insertRow(row_dst);
            }

            for(int i = 0; i < m_table->columnCount(); i++)
                m_table->setItem(row_dst, i, m_table->takeItem(row_src, i));
            m_table->removeRow(row_src);
        }
    }
    return QWidget::eventFilter(obj, event);
}
