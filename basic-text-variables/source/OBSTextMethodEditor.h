#pragma once

#include "common.h"
#include <QObject>
#include <QDialog>

#include <QWidget>
#include <QWindow>
#include <QScreen>
#include <QResizeEvent>
#include <QShowEvent>
#include <UI/properties-view.hpp>


struct VariableEditorUI : QDialog
{
	Q_OBJECT

private:
	OBSPropertiesView* properties_view;

public slots:
	void PropertiesChanged();

public:

	std::unique_ptr<void*> ui;
	VariableEditorUI(QWidget* parent = nullptr);

	void ShowHideDialog();
	OBSData LoadSettings();
	void SaveSettings();
	void SetupPropertiesView();

};

