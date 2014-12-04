#ifndef TEKSETTINGS_H
#define TEKSETTINGS_H

#include <QWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>

#include <iostream>

#include "observer/observer.h"
#include "tekVisa/tekmodule.h"
#include "tekVisa/chipmodule.h"
#include "types.hpp"

using namespace std;

class tekSettings : public QGroupBox, public Observer
{
	Q_OBJECT
public:
	explicit tekSettings(tekModule *mod,const QString &title, QWidget *parent = 0);
	~tekSettings();
	int		currentChannel () {return channel;}
	void	obsUpdate(const Subject *subject);

	void	setHighLevel();
	void	setLowLevel();
	vector<char> getChipChannel()	const;
protected:
	void	setSettings();
	void	writeSettings();
	void	readSettings();
	int		getCurrentChannel();
	void	createWidgets();
	void	createLayouts();
protected:
	void	setLeftFront();
	void	setRightFront();
	void	setInterval();
	void	setWidth();
	void	setChannel();
	void	setChipChannel();
	void	updateSettings();
private:
	tekModule				*_module;
	chipModule				*_chip;
	int						channel;

	QFormLayout				*layout;
	QHBoxLayout				*mainLayout;
	QVBoxLayout				*chipLayout;

	QRadioButton			*channelOneC;
	QRadioButton			*channelTwoC;
	vector<QCheckBox*>		chipChannel;

	QLineEdit				*leftFrontL;
	QLineEdit				*rightFrontL;
	QLineEdit				*intervalL;
	QLineEdit				*widthL;
	QLineEdit				*lowLevelL;
	QLineEdit				*highLevelL;
	QLineEdit				*ampStartL;
	QLineEdit				*ampEndL;
	QLineEdit				*ampStepL;
};

#endif // TEKSETTINGS_H
