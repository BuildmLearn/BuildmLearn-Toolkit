#include "templates/matchthefollowing/listDelegate.h"

ListDelegate::ListDelegate() {
}

void ListDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	QRect r = option.rect;

	//Color: #C4C4C4
	QPen linePen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

	//Color: #005A83
	QPen lineMarkedPen(QColor::fromRgb(0,90,131), 1, Qt::SolidLine);

	//Color: #333
	QPen fontPen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

	//Color: #fff
	QPen fontMarkedPen(Qt::white, 1, Qt::SolidLine);

	//For highlighting the seleted item
	if(option.state & QStyle::State_Selected) {
		QLinearGradient gradientSelected(r.left(),r.top(),r.left(),r.height()+r.top());
		gradientSelected.setColorAt(0.0, QColor::fromRgb(119,213,247));
		gradientSelected.setColorAt(0.9, QColor::fromRgb(27,134,183));
		gradientSelected.setColorAt(1.0, QColor::fromRgb(0,120,174));
		painter->setBrush(gradientSelected);
		painter->drawRect(r);

		//BORDER
		painter->setPen(lineMarkedPen);
		painter->drawLine(r.topLeft(),r.topRight());
		painter->drawLine(r.topRight(),r.bottomRight());
		painter->drawLine(r.bottomLeft(),r.bottomRight());
		painter->drawLine(r.topLeft(),r.bottomLeft());
		
		painter->setPen(fontMarkedPen);
	} 
	//For items which are not selected
	else {
		//BACKGROUND
					//ALTERNATING COLORS
		painter->setBrush( (index.row() % 2) ? Qt::white : QColor(180,180,180,40) );
		painter->drawRect(r);

		//BORDER
		painter->setPen(linePen);
		painter->drawLine(r.topLeft(),r.topRight());
		painter->drawLine(r.topRight(),r.bottomRight());
		painter->drawLine(r.bottomLeft(),r.bottomRight());
		painter->drawLine(r.topLeft(),r.bottomLeft());

		painter->setPen(fontPen);
	}

	//Get First list topic and Second list topic
	QString firstListTopic = "First List Topic - ";
	firstListTopic = firstListTopic + index.data(Qt::UserRole + 1).toString();
	QString secondListTopic = "Matching Topic - ";
	secondListTopic= secondListTopic + index.data(Qt::UserRole + 2).toString();

	//First List Topic
	r = option.rect.adjusted(10, 0, -10, -24);
	painter->setFont( QFont( "", 10, QFont::Normal ) );
	painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft, firstListTopic, &r);

	//Second List Topic
	r = option.rect.adjusted(10, 27, -10, 20);
	painter->setFont( QFont( "", 10, QFont::Normal ) );
	painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, secondListTopic, &r);
}

//Size of the ListWidgetItem
QSize ListDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
	Q_UNUSED(option);
	Q_UNUSED(index);
	return QSize(40, 50);
}

ListDelegate::~ListDelegate()
{
}
