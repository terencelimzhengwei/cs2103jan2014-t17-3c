//@author A0097330H
#include "timewisehelp.h"

TimeWiseHelp::TimeWiseHelp(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint); //remove title header of help window
	ui.textEdit->scrollToAnchor(SPACE);            //set help window to scroll to the top upon initialization (else window will be scrolled to bottom)
	ui.pushButton_ok->setFocus();				   //bring focus to ok button so that user can press Enter and leave the page immediately.
}

TimeWiseHelp::~TimeWiseHelp() {
}

//overrides dialog widget's stylesheet configuration (put simply, allow background of pop-up box to be set)
void TimeWiseHelp::paintEvent(QPaintEvent *pe) {                                                                                                                                        
	QStyleOption o;                                                                                                                                                                  
	o.initFrom(this);                                                                                                                                                                
	QPainter p(this);                                                                                                                                                                
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);                                                                                                                         
}