
#include "OBSTextMethodEditor.h"

//Ui_VariableEditor
VariableEditorUI::VariableEditorUI(QWidget* parent) : QDialog(parent), properties_view(nullptr)
{
	//ui->setupUi(this);

	setSizeGripEnabled(true);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void VariableEditorUI::ShowHideDialog()
{
	SetupPropertiesView();

	setVisible(!isVisible());
}


void VariableEditorUI::SetupPropertiesView()
{
	//if (properties_view) delete properties_view;

	OBSData data = LoadSettings();

	//if (data) obs_data_apply(settings, data);

	//properties_view = new OBSPropertiesView(data, this, (PropertiesReloadCallback)obs_get_output_properties, (PropertiesUpdateCallback)obs_output_update);
	//properties_view->setMinimumHeight(150);
	
	//ui->verticalLayout->addWidget(properties_view);


	//connect(properties_view, SIGNAL(Changed()), this, SLOT(PropertiesChanged()));
}

void VariableEditorUI::PropertiesChanged()
{
	SaveSettings();
}

OBSData VariableEditorUI::LoadSettings()
{
	BPtr<char> path = obs_module_get_config_path(
		obs_current_module(), "textVariableProps.json");
	BPtr<char> jsonData = os_quick_read_utf8_file(path);
	if (!!jsonData) {
		obs_data_t* data = obs_data_create_from_json(jsonData);
		OBSData dataRet(data);
		obs_data_release(data);
		return dataRet;
	}

	return nullptr;
}

void VariableEditorUI::SaveSettings()
{
	BPtr<char> modulePath =
		obs_module_get_config_path(obs_current_module(), "");

	os_mkdirs(modulePath);

	BPtr<char> path = obs_module_get_config_path(
		obs_current_module(), "textVariableProps.json");

	obs_data_t* settings = properties_view->GetSettings();
	if (settings)
		obs_data_save_json_safe(settings, path, "tmp", "bak");
}


