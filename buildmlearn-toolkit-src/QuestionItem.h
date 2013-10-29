#ifndef QUESTIONITEM_H
#define QUESTIONITEM_H

#include <QtGui>

class QuestionItem : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionItem(int index, QString ques_text, QWidget *parent = 0);
    int getIndex();
    void setIndex(int);
signals:
    void removeClicked(int);

public slots:
    void iRemoveButton_clicked();

private:
    QLabel *iQuestionLabel;
    QPushButton *iRemoveButton;
    int iListIndex;
    QGroupBox* iGroupBox;
    QString iText;
};

#endif // QUESTIONITEM_H
