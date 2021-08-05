/****************************************************************************
**
** Author:              wangjun
** E-Mail:              tiredwind@foxmail.com
** Phone Number:        15256527665
** Creation Time:       2021/07/19
**
** Description:
** This custom widget is used to input infomation in QTableWidget
**
**
****************************************************************************/

#ifndef EditableTableWidget_H
#define EditableTableWidget_H

// #include <include/json/json.h>

#include <QWidget>
#include <QPointer>

class QTableWidget;
class QToolBar;
class QToolButton;


class EditableTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditableTableWidget(QWidget *parent = 0);
    ~EditableTableWidget();

    void setVerticalHeaderNames(const QStringList & ls_headerNames);
    void setHorizontalHeaderNames(const QStringList & ls_headerNames);
//    Json::Value getJsonValueHorizontal();
//    Json::Value getJsonValueVertical();

    void moveRow(int currentRow, int toRow);

protected:
    virtual bool eventFilter(QObject * obj, QEvent * event);

private:
    QToolButton * createToolButton(const QString & object_name, const QString & icon_url, const QString & tooltip);

private slots:
    void slot_addRow();
    void slot_insertRow();
    void slot_moveUp();
    void slot_moveDown();
    void slot_deleteRow();
    void slot_clear();

private:
    QPointer<QTableWidget> m_table;
    QPointer<QToolBar> m_toolBar;
    QStringList m_horizontalLabels;
    QStringList m_verticalLabels;
};

#endif // EditableTableWidget_H
