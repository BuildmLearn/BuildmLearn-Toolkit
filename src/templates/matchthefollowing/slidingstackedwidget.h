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

#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>

#include <QtGui>
#include <QWidget>
#include <QDebug>
#include <QEasingCurve>

/// \brief QStackedWidget with sliding animation.
/// \ingroup template-matchthefollowing
class SlidingStackedWidget : public QStackedWidget
{
  Q_OBJECT

    public:
    // This enumeration is used to define the animation direction.
    enum t_direction {
      LEFT2RIGHT,
      RIGHT2LEFT,
      AUTOMATIC
    };
    // The Constructor and Destructor.
    SlidingStackedWidget(QWidget *parent);
    ~SlidingStackedWidget(void);


  public slots:
    // Some basic settings API.
    // Animation duration in milliseconds.
    void setSpeed(int speed);
    // Check out the QEasingCurve documentation for different styles.
    void setAnimation(enum QEasingCurve::Type animationtype);
    // Wrapping is related to slideInNext/Prev;it defines the behaviour when reaching last/first page.
    void setWrap(bool wrap);

    // The Animation / Page Change API
    void slideInNext();
    void slideInPrev();
    void slideInIdx(int idx, enum t_direction direction=AUTOMATIC);

  signals:
    // This is used for internal purposes in the class engine.
    void animationFinished(void);

  protected slots:
    // This is used for internal purposes in the class engine.
    void animationDoneSlot(void);

  protected:
    // This is used for internal purposes in the class engine.
    void slideInWgt(QWidget * widget, enum t_direction direction=AUTOMATIC);

    QWidget *m_mainwindow;

    int m_speed;
    enum QEasingCurve::Type m_animationtype;
    int m_now;
    int m_next;
    bool m_wrap;
    QPoint m_pnow;
    bool m_active;

    QList<QWidget*> blockedPageList;
};

#endif // SLIDINGSTACKEDWIDGET_H
