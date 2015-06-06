#include <QPainter>
#include <QAbstractItemDelegate>
 
class ListDelegate : public QAbstractItemDelegate {
	public:
		ListDelegate();
 
		void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
		QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
 
		virtual ~ListDelegate();
};
