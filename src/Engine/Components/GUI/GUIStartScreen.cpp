#include "stdafx.h"

#include "GUIStartScreen.h"
#include "../../Game/Constants.h"
#include "../../Managers/ResourceManager.h"

using namespace sf;
using namespace std;
using namespace tgui;
using namespace ToD;
using namespace Events;
using namespace GUI;
using namespace ToD::Managers;

GUIStartScreen::GUIStartScreen(GameObject* l_owner)
: AGUIComponent(l_owner)
, m_isStartGameClicked(false)
, m_isExitGameClicked(false)
{
}

ReferenceType::RuntimeType GUIStartScreen::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GUIStartScreen::RuntimeType()
{
	return "ToD::Components::GUI::GUIStartScreen";
}

bool GUIStartScreen::GetIsStartGameClicked() const
{
	return m_isStartGameClicked;
}

void GUIStartScreen::SetIsStartGameClicked(bool l_value)
{
	m_isStartGameClicked = l_value;
}

bool GUIStartScreen::GetIsExitGameClicked() const
{
	return m_isExitGameClicked;
}

void GUIStartScreen::SetIsExitGameClicked(bool l_value)
{
	m_isExitGameClicked = l_value;
}

bool GUIStartScreen::GetIsCredistClicked() const
{
	return m_isCredistClicked;
}

void GUIStartScreen::SetIsCredistClicked(const bool l_value)
{
	m_isCredistClicked = l_value;
}

void GUIStartScreen::LoadWidgets()
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
		Picture::Ptr picture = make_shared<Picture>(*resourceManager.GetTexture(Constants::Texture::StartScreenBackground));
		picture->setSize(bindMax(1024, windowWidth), bindMax(768, windowHeight));
		m_gui->add(picture);

		// Create the start button
		Button::Ptr startBtn = theme->load("Button");
		startBtn->setSize(windowWidth / 7, windowHeight / 20);
		startBtn->setPosition((windowWidth * 0.78f), windowHeight * 0.75f);
		startBtn->setText("Start");
		m_gui->add(startBtn);

		// Create the credits button
		Button::Ptr creditBtn = theme->load("Button");
		creditBtn->setSize(windowWidth / 7, windowHeight / 20);
		creditBtn->setPosition((windowWidth * 0.78f), (windowHeight * 0.75f) + startBtn->getFullSize().y + 5);
		creditBtn->setText("Credits");
		m_gui->add(creditBtn);

		// Create the quit button
		Button::Ptr quitBtn = theme->load("Button");
		quitBtn->setSize(windowWidth / 7, windowHeight / 20);
		quitBtn->setPosition((windowWidth * 0.78f), (windowHeight * 0.75f) + startBtn->getFullSize().y + creditBtn->getFullSize().y + 10);
		quitBtn->setText("Quit");
		m_gui->add(quitBtn);

		// Call the start function when the button is pressed
		startBtn->connect("clicked", [this]() { this->SetIsStartGameClicked(true); });

		// Call the credit function when the button is pressed
		creditBtn->connect("clicked", [this]() { this->SetIsCredistClicked(true); });
		
		// Call the exit function when the button is pressed
		quitBtn->connect("clicked", [this]() { this->SetIsExitGameClicked(true); });
	}
	catch (const Exception& e)
	{
		LOG(ERROR) << "Failed to load TGUI widgets: " << e.what();
	}
}
