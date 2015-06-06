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

#include "templates/matchthefollowing/slidingstackedwidget.h" 
 
SlidingStackedWidget::SlidingStackedWidget(QWidget *parent) : QStackedWidget(parent) {
	if (parent!=0)
		m_mainwindow=parent;
	else
		m_mainwindow=this;
	
	m_speed=750;
	m_animationtype = QEasingCurve::OutBack;
	m_now=0;
	m_next=0;
	m_wrap=true;
	m_pnow=QPoint(0,0);
	m_active=false;
}
 
 
SlidingStackedWidget::~SlidingStackedWidget(){
}
 
void SlidingStackedWidget::setSpeed(int speed) {
  m_speed = speed;
}
 
void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
  m_animationtype = animationtype;
}
 
void SlidingStackedWidget::setWrap(bool wrap) {
  m_wrap=wrap;
}
 
void SlidingStackedWidget::slideInNext() {
	int now=currentIndex();
	if (m_wrap||(now<count()-1))
		slideInIdx(now+1);
}
 
 
void SlidingStackedWidget::slideInPrev() {
	int now=currentIndex();
	if (m_wrap||(now>0))
		slideInIdx(now-1);
}
 
void SlidingStackedWidget::slideInIdx(int idx, enum t_direction direction) {
	//int idx, t_direction direction=AUTOMATIC
	if (idx>count()-1) {
		direction=RIGHT2LEFT;
		idx=(idx)%count();
	}
	else if (idx<0) {
		direction=LEFT2RIGHT;
		idx=(idx+count())%count();
	}
	slideInWgt(widget ( idx ),direction);
	//widget() is a function inherited from QStackedWidget
}
 
 
void SlidingStackedWidget::slideInWgt(QWidget * newwidget, enum t_direction direction) {
 
	if (m_active)
		return;
	else 
		m_active=true;

	enum t_direction directionhint;
	int now=currentIndex();		//currentIndex() is a function inherited from QStackedWidget
	int next=indexOf(newwidget);
	if (now==next) {
		m_active=false;
		return;
	}
	else if (now<next)
		directionhint=RIGHT2LEFT;
	else 
		directionhint=LEFT2RIGHT;
	if (direction == AUTOMATIC)
		direction=directionhint;
	//NOW....
	//calculate the shifts
	int offsetx=frameRect().width(); //inherited from mother
	int offsety=frameRect().height();//inherited from mother
	//the following is important, to ensure that the new widget
	//has correct geometry information when sliding in first time
	widget(next)->setGeometry ( 0,  0, offsetx, offsety );

	if (direction==RIGHT2LEFT) {
		offsetx=-offsetx;
		offsety=0;
	}
	else if (direction==LEFT2RIGHT)
		offsety=0;
		
	//re-position the next widget outside/aside of the display area
	QPoint pnext=widget(next)->pos();
	QPoint pnow=widget(now)->pos();
	m_pnow=pnow;

	widget(next)->move(pnext.x()-offsetx,pnext.y()-offsety);
	//make it visible/show
	widget(next)->show();
	widget(next)->raise();

	//animate both, the now and next widget to the side, using animation framework
	QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");

	animnow->setDuration(m_speed);
	animnow->setEasingCurve(m_animationtype);
	animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
	animnow->setEndValue(QPoint(offsetx+pnow.x(), offsety+pnow.y()));
	QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
	animnext->setDuration(m_speed);
	animnext->setEasingCurve(m_animationtype);
	animnext->setStartValue(QPoint(-offsetx+pnext.x(), offsety+pnext.y()));
	animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

	QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

	animgroup->addAnimation(animnow);
	animgroup->addAnimation(animnext);

	QObject::connect(animgroup, SIGNAL(finished()),this,SLOT(animationDoneSlot()));
	m_next=next;
	m_now=now;
	m_active=true;
	animgroup->start();
}
 
 
void SlidingStackedWidget::animationDoneSlot(void) {
	//when ready, call the QStackedWidget slot setCurrentIndex(int)
	setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
	//then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
	widget(m_now)->hide();
	//then set the position of the outshifted widget now back to its original
	widget(m_now)->move(m_pnow);
	//so that the application could also still call the QStackedWidget original functions/slots for changings
	//widget(m_now)->update();
	//setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
	m_active=false;
	emit animationFinished();
}
