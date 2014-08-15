#ifndef MAXLENGTHTEXTEDIT_H
#define MAXLENGTHTEXTEDIT_H

#include <QTextEdit>


class MaxLengthTextEdit : public QTextEdit {
    Q_OBJECT

  public:
    explicit MaxLengthTextEdit(QWidget *parent = 0);
    virtual ~MaxLengthTextEdit();

    int maxLength() const;
    void setMaxLength(int max_length);

  private slots:
    void checkLength();
    void reallyCheckLength();

  private:
    int m_maxLength;

};

#endif // MAXLENGTHTEXTEDIT_H
