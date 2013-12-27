#ifndef NEWPROJECTWIDGET_H
#define NEWPROJECTWIDGET_H

#include <QWidget>
#include <QtGui>

class NewProjectWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit NewProjectWidget(QWidget *parent = 0);

signals:
    void startProject(int);

public slots:
    void TemplateSelectionChanged(int index);
    void iChooseButton_clicked();
    void iOpenButton_clicked();
private:
    QWidget* iWidget;
    QWidget* iLeftWidget;

    QListWidget* iTemplateList;
    QLabel* iChooseTemplateLabel;
    QPushButton* iOpenButton;
    QPushButton* iChooseButton;
    QPushButton* iCancelButton;
    QWidget* iRightWidget;

    QLabel* iRightImageWidget;
    QLabel* iRightInfoWidget;

    QStringList iTemplateInfoList;
    QStringList iTemplateImageList;
};

#endif // NEWPROJECTWIDGET_H
