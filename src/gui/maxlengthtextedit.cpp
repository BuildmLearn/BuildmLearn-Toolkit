#include "gui/maxlengthtextedit.h"

#include <QTimer>


MaxLengthTextEdit::MaxLengthTextEdit(QWidget *parent)
  : QTextEdit(parent), m_maxLength(-1) {
  connect(this, SIGNAL(textChanged()), this, SLOT(checkLength()));
}

MaxLengthTextEdit::~MaxLengthTextEdit(){
}

int MaxLengthTextEdit::maxLength() const {
  return m_maxLength;
}

void MaxLengthTextEdit::setMaxLength(int max_length) {
  m_maxLength = max_length;
}

void MaxLengthTextEdit::checkLength() {
  QTimer::singleShot(0, this, SLOT(reallyCheckLength()));
}

void MaxLengthTextEdit::reallyCheckLength() {
  while (m_maxLength >= 0 && toPlainText().size() > m_maxLength) {
    textCursor().deletePreviousChar();
  }
}
