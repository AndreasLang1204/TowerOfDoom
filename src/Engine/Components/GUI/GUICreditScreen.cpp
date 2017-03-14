#include "stdafx.h"

#include "GUICreditScreen.h"
#include "../../Game/Constants.h"
#include "../../Managers/ResourceManager.h"

using namespace sf;
using namespace std;
using namespace tgui;
using namespace ToD;
using namespace Events;
using namespace GUI;
using namespace ToD::Managers;

GUICreditScreen::GUICreditScreen(GameObject* l_owner)
: AGUIComponent(l_owner)
, m_isExitScreenClicked(false)
{
}

ReferenceType::RuntimeType GUICreditScreen::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GUICreditScreen::RuntimeType()
{
	return "ToD::Components::GUI::GUICreditScreen";
}

bool GUICreditScreen::GetIsExitScreenClicked() const
{
	return m_isExitScreenClicked;
}

void GUICreditScreen::SetIsExitScreenClicked(bool l_value)
{
	m_isExitScreenClicked = l_value;
}

void GUICreditScreen::LoadWidgets()
{
	auto& resourceManager = Get<ResourceManager>();

	try
	{
		// Load the widgets
		// Load the theme for the edit boxes and button
		auto theme = make_shared<Theme>("../assets/GUI/Black.txt");

		// Get a bound version of the window size
		// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
		auto windowWidth = bindWidth(*m_gui);
		auto windowHeight = bindHeight(*m_gui);

		// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
		Picture::Ptr picture = make_shared<Picture>(*resourceManager.GetTexture(Constants::Texture::CreditScreenBackground));
		picture->setSize(bindMax(1024, windowWidth), bindMax(768, windowHeight));
		m_gui->add(picture);

		// Create the quit button
		Button::Ptr quitBtn = theme->load("Button");
		quitBtn->setSize(windowWidth / 7, windowHeight / 20);
		quitBtn->setPosition((windowWidth * 0.49f) - quitBtn->getFullSize().x / 2, (windowHeight * 0.05f));
		quitBtn->setText("Quit");
		m_gui->add(quitBtn);

		// Call the exit function when the button is pressed
		quitBtn->connect("clicked", [this]() { this->SetIsExitScreenClicked(true); });
	}
	catch (const Exception& e)
	{
		LOG(ERROR) << "Failed to load TGUI widgets: " << e.what();
	}
}
