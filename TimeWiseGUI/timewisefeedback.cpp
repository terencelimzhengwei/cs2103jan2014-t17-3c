#include "timewisefeedback.h"

TimeWiseFeedback::TimeWiseFeedback(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint);
	this->setWindowFlags(Qt::FramelessWindowHint);

	QFontDatabase fontDatabase; 
	fontDatabase.addApplicationFont(":/TimeWiseGUI/DK Crayon Crumble.ttf");
	ui.userFeedback->setFont(QFont("DK Crayon Crumble",13));

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

void TimeWiseFeedback::setData(const QString &labelText) {
	ui.userFeedback->setText(labelText);
}