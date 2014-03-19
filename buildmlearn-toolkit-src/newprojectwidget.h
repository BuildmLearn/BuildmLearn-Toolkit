/* Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef NEWPROJECTWIDGET_H
#define NEWPROJECTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QtGui>
#include <QMainWindow>

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
