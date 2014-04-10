#include "timewisefeedback.h"

TimeWiseFeedback::TimeWiseFeedback(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint);
	ui.textEdit->scrollToAnchor("hello");
	ui.pushButton_ok->setFocus();
}

TimeWiseFeedback::~TimeWiseFeedback() {
}

//overrides dialog widget's stylesheet configuration (put simply, allow background of pop-up box to be set)
void TimeWiseFeedback::paintEvent(QPaintEvent *pe) {                                                                                                                                        
	QStyleOption o;                                                                                                                                                                  
	o.initFrom(this);                                                                                                                                                                
	QPainter p(this);                                                                                                                                                                
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);                                                                                                                         
}