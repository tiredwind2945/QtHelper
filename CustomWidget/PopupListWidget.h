#include <QToolButton>
#include <QWidgetAction>
#include <QPointer>
 
class QMenu;
 
class PopupListWidget : public QToolButton
{
	Q_OBJECT
 
public:
	PopupListWidget(QWidget *parent = Q_NULLPTR);
	~PopupListWidget();
 
private:
	QPointer<QWidgetAction> m_popup_widget;
	QPointer<QMenu> m_menu;
};