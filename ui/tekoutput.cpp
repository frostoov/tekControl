#include "tekoutput.h"

tekOutput::tekOutput(tekModule *mod, QWidget *parent)
	: QPlainTextEdit(parent) , _module(mod)
{
	setReadOnly(true);
	logStream.open("log",ofstream::binary | ofstream::app);
	print("Starting tekControl");
	print(tr("Date: [") + getDate(QDateTime::currentDateTime()) + tr("]"));
	print(tr("Time: [") + getTime(QDateTime::currentDateTime()) + tr("]"));
}

tekOutput::~tekOutput()
{
	print("Closing tekControl");
	if(logStream.is_open())
		logStream.close();
}


void tekOutput::obsUpdate(const Subject *subject)
{
	if(subject == _module)
	{
		while( _module->getActions().size() )
		{
			printAction( _module->getActions().front() );
			_module->getActions().pop();
		}
	}
}

void tekOutput::print(const QString &text)
{
	outputLock.lock();
	appendPlainText(text);
	if(logStream.is_open())
		logStream << text.toUtf8().data() << endl;
	outputLock.unlock();
}

void tekOutput::printAction(const actionInfo_s &act)
{
	if(act.errCode == VI_SUCCESS)
		print(getDataTime(QDateTime::currentDateTime()) + tr("\t") +
			  tr("%1 - OK").arg(_module->decodeAction(act.actCode)) );
	else
		print(getDataTime(QDateTime::currentDateTime()) +tr("\t") +
			  tr("%1 - FAILED").arg(_module->decodeAction(act.actCode)) );
	ensureCursorVisible();
}

QString tekOutput::getDate(const QDateTime &dt)
{
	return	tr("%1.%2.%3").
			arg(dt.date().day(),2,10,QChar('0')).
			arg(dt.date().month(),2,10,QChar('0')).
			arg(dt.date().year(),4,10,QChar('0'));
}

QString tekOutput::getTime(const QDateTime &tm)
{
	return	tr("%1:%2:%3").
			arg(tm.time().hour(),2,10,QChar('0')).
			arg(tm.time().minute(),2,10,QChar('0')).
			arg(tm.time().second(),2,10,QChar('0'));
}

QString tekOutput::getDataTime(const QDateTime &tmdt)
{
	return tr("[") + getTime(tmdt) + tr("]");
}
