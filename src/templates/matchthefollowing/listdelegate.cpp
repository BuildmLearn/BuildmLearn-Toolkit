/*
  Copyright (c) 2015, BuildmLearn Contributors listed at http://buildmlearn.org/people/
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the BuildmLearn nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "templates/matchthefollowing/listdelegate.h"
#include "definitions/definitions.h"


ListDelegate::ListDelegate() {
}

void ListDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
  QRect r = option.rect;

  // Color: #C4C4C4.
  QPen line_pen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

  // Color: #005A83.
  QPen line_marked_pen(QColor::fromRgb(0,90,131), 1, Qt::SolidLine);

  // Color: #333.
  QPen font_pen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

  // Color: #fff.
  QPen font_marked_pen(Qt::white, 1, Qt::SolidLine);

  // For highlighting the seleted item.
  if (option.state & QStyle::State_Selected) {
    QLinearGradient gradient_selected(r.left(),r.top(),r.left(),r.height()+r.top());
    gradient_selected.setColorAt(0.0, QColor::fromRgb(119,213,247));
    gradient_selected.setColorAt(0.9, QColor::fromRgb(27,134,183));
    gradient_selected.setColorAt(1.0, QColor::fromRgb(0,120,174));
    painter->setBrush(gradient_selected);
    painter->drawRect(r);

    // Creating border.
    painter->setPen(line_marked_pen);
    painter->drawLine(r.topLeft(),r.topRight());
    painter->drawLine(r.topRight(),r.bottomRight());
    painter->drawLine(r.bottomLeft(),r.bottomRight());
    painter->drawLine(r.topLeft(),r.bottomLeft());
    painter->setPen(font_marked_pen);
  } 
  // For items which are not selected.
  else {
    // Background colour.
    // Alternating Colours.
    painter->setBrush( (index.row() % 2) ? Qt::white : QColor(180,180,180,40) );
    painter->drawRect(r);

    // Creating border.
    painter->setPen(line_pen);
    painter->drawLine(r.topLeft(),r.topRight());
    painter->drawLine(r.topRight(),r.bottomRight());
    painter->drawLine(r.bottomLeft(),r.bottomRight());
    painter->drawLine(r.topLeft(),r.bottomLeft());
    painter->setPen(font_pen);
  }

  // Get First list topic and Second list topic.
  QString first_list_topic;
  if (index.data(Qt::UserRole + 3).toString().isEmpty() || index.data(Qt::UserRole + 3).toString().isNull())
    first_list_topic = tr("First List Topic - ") + index.data(Qt::UserRole + 1).toString();
  else
    first_list_topic = index.data(Qt::UserRole + 3).toString() + " - " + index.data(Qt::UserRole + 1).toString();
    
  QString second_list_topic;
  if (index.data(Qt::UserRole + 4).toString().isEmpty() || index.data(Qt::UserRole + 4).toString().isNull())
    second_list_topic = tr("Matching Topic - ") + index.data(Qt::UserRole + 2).toString();
  else
    second_list_topic = index.data(Qt::UserRole + 4).toString() + " - " + index.data(Qt::UserRole + 2).toString();

  // First List Topic.
  r = option.rect.adjusted(LIST_DELEGATE_DX1, LIST_DELEGATE_FDY1, LIST_DELEGATE_DX2, LIST_DELEGATE_FDY2);
  painter->setFont( QFont( QString(), 10, QFont::Normal ) );
  painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft, first_list_topic, &r);

  // Second List Topic.
  r = option.rect.adjusted(LIST_DELEGATE_DX1, LIST_DELEGATE_SDY1, LIST_DELEGATE_DX2, LIST_DELEGATE_SDY2);
  painter->setFont( QFont( QString(), 10, QFont::Normal ) );
  painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, second_list_topic, &r);
}

// Size of the ListWidgetItem.
QSize ListDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const{
  Q_UNUSED(option);
  Q_UNUSED(index);
  return QSize(LIST_DELEGATE_WIDTH, LIST_DELEGATE_HEIGHT);
}

ListDelegate::~ListDelegate()
{
}
