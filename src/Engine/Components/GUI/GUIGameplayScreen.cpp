#include "stdafx.h"

#include "GUIGameplayScreen.h"
#include "../PlayableCharacter.h"
#include "../SpriteRenderable.h"

#include "../../Events/EventInvoker.h"
#include "../../Events/GameObjectEventArgs.h"
#include "../../Events/GridCellClickedEventArgs.h"

#include "../../Game/Constants.h"
#include "../../Game/GameObject.h"

#include "../../Managers/EventBus.h"
#include "../../Managers/ResourceManager.h"

using namespace sf;
using namespace tgui;
using namespace ToD;
using namespace ToD::Events;
using namespace ToD::Components::GUI;
using namespace ToD::Managers;

GUIGameplayScreen::GUIGameplayScreen(GameObject* l_owner)
: AGUIComponent(l_owner)
{
}

GUIGameplayScreen::~GUIGameplayScreen()
{
}

ReferenceType::RuntimeType GUIGameplayScreen::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GUIGameplayScreen::RuntimeType()
{
	return "ToD::Components::GUI::GUIGameplayScreen";
}

void GUIGameplayScreen::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<GUIGameplayScreen, GameObjectEventArgs>(this, &GUIGameplayScreen::OnTurnSystemNextCharacter);
	Get<EventBus>().Get(EventType::GridCellClicked) += new EventInvoker<GUIGameplayScreen, GridCellClickedEventArgs>(this, &GUIGameplayScreen::OnGridCellClicked);
}

void GUIGameplayScreen::Activate2()
{
	Activateable::Activate2();
}

void GUIGameplayScreen::Deactivate1()
{
	Activateable::Deactivate1();
}

void GUIGameplayScreen::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<GUIGameplayScreen, GameObjectEventArgs>(this, &GUIGameplayScreen::OnTurnSystemNextCharacter);
	Get<EventBus>().Get(EventType::GridCellClicked) -= new EventInvoker<GUIGameplayScreen, GridCellClickedEventArgs>(this, &GUIGameplayScreen::OnGridCellClicked);
}

void GUIGameplayScreen::LoadWidgets()
{
	auto& resourceManager = Get<ResourceManager>();

	try
	{
		auto guiEnteredHandler = [this]() { Get<EventBus>().Raise(EventType::GuiElementEntering, new EventArgs()); };
		auto guiLeftHandler = [this]() { Get<EventBus>().Raise(EventType::GuiElementLeaving, new EventArgs()); };

		// Load the widgets
		// Load the theme for the edit boxes and button
		auto theme = make_shared<Theme>("../assets/GUI/ToDGUI.txt");

		// Get a bound version of the window size
		// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
		auto windowWidth = bindWidth(*m_gui);
		auto windowHeight = bindHeight(*m_gui);

		// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
		Picture::Ptr border = make_shared<Picture>(*resourceManager.GetTexture(Constants::Texture::GameplayScreenBorder));
		border->setSize(bindMax(1024, windowWidth), bindMax(768, windowHeight));
		m_gui->add(border);

		// Create the endturn button
		Button::Ptr endTurnBtn = theme->load("Button");
		endTurnBtn->setSize(61, 57);
		endTurnBtn->setPosition(602, 667);
		endTurnBtn->setText(" END\nTURN");
		endTurnBtn->setTextSize(0);
		endTurnBtn->connect("mouseentered", guiEnteredHandler);
		endTurnBtn->connect("mouseleft", guiLeftHandler);
		m_gui->add(endTurnBtn);
		m_gui->setWidgetName(endTurnBtn, "endTurnBtn");

		// Create the quit button
		// Create the quit button
		Button::Ptr quitBtn = theme->load("Button");
		quitBtn->setSize(windowWidth / 15, windowHeight / 20);
		quitBtn->setPosition((windowWidth * 0.9f), (windowHeight * 0.04f));
		quitBtn->setText("Quit");
		quitBtn->connect("mouseentered", guiEnteredHandler);
		quitBtn->connect("mouseleft", guiLeftHandler);
		m_gui->add(quitBtn);
		m_gui->setWidgetName(quitBtn, "quitBtn");

		//// Create the skill button
		//Button::Ptr abilityBtn = theme->load("Button");
		//abilityBtn->setSize(70, 50);
		//abilityBtn->setPosition((windowWidth / 3) - (abilityBtn->getFullSize().x / 2), windowHeight * 0.85f);
		//abilityBtn->setText("Attack");
		//m_gui->add(abilityBtn);
		//m_gui->setWidgetName(endTurnBtn, "abilityBtn");

#pragma region Hover Character Panel
		// hover character panel
		Panel::Ptr hoverCharPanel = theme->load("Panel");
		hoverCharPanel->setBackgroundColor(tgui::Color(255, 255, 255, 0));
		hoverCharPanel->setSize(100, 170);
		hoverCharPanel->setPosition(35, 35);
		m_gui->add(hoverCharPanel);
		m_gui->setWidgetName(hoverCharPanel, "hoverCharPanel");

		// background picture
		Picture::Ptr bgPicture = make_shared<Picture>();
		bgPicture->setTexture(*resourceManager.GetTexture(Constants::Texture::GameplayScreenGUIUnitFrame));
		bgPicture->setSize(100, 170);
		bgPicture->setPosition(0, 0);
		bgPicture->connect("mouseentered", guiEnteredHandler);
		bgPicture->connect("mouseleft", guiLeftHandler);
		hoverCharPanel->add(bgPicture, "bgPicture");

		// picture
		Picture::Ptr hoverCharPicture = make_shared<Picture>();
		hoverCharPicture->setTexture({ *resourceManager.GetTexture(Constants::Texture::GameplayScreenGridCursor),{ 64,0,16,16 } });
		hoverCharPicture->setSize(50, 50);
		hoverCharPicture->setPosition(25, 15);
		hoverCharPanel->add(hoverCharPicture, "hoverCharPicture");

		// Level
		Label::Ptr hoverCharLevelLabel = theme->load("Label");
		hoverCharLevelLabel->setPosition(27, 70);
		hoverCharLevelLabel->setTextColor(tgui::Color(0, 0, 0));
		hoverCharLevelLabel->setAutoSize(true);
		hoverCharLevelLabel->setText("LvL:");
		hoverCharPanel->add(hoverCharLevelLabel, "hoverCharLevel");

		// health
		Label::Ptr hoverCharHealthLabel = theme->load("Label");
		hoverCharHealthLabel->setPosition(8, hoverCharLevelLabel->getPosition().y + hoverCharLevelLabel->getFullSize().y + 5);
		hoverCharHealthLabel->setTextColor(tgui::Color(0, 0, 0));
		hoverCharHealthLabel->setAutoSize(true);
		hoverCharHealthLabel->setText("HP:");
		hoverCharPanel->add(hoverCharHealthLabel, "hoverCharHealth");

		// AP
		Label::Ptr hoverCharApLabel = theme->load("Label");
		hoverCharApLabel->setPosition(8, hoverCharHealthLabel->getPosition().y + hoverCharHealthLabel->getFullSize().y + 5);
		hoverCharApLabel->setTextColor(tgui::Color(0, 0, 0));
		hoverCharApLabel->setAutoSize(true);
		hoverCharApLabel->setText("AP:");
		hoverCharPanel->add(hoverCharApLabel, "hoverCharAP");
#pragma endregion

#pragma region Current Chatacter Panel
		// picture
		Picture::Ptr characterPicture = make_shared<Picture>();
		characterPicture->setTexture({ *resourceManager.GetTexture("Undead"),{ 0,0,16,16 } });
		characterPicture->setSize(50, 50);
		characterPicture->setPosition(263, 624);
		m_gui->add(characterPicture);
		m_gui->setWidgetName(characterPicture, "currentCharPicture");

		// health
		Label::Ptr healthLabel = theme->load("Label");
		healthLabel->setPosition(201, 610);
		healthLabel->setSize(38, 29);
		healthLabel->setTextColor(tgui::Color(0, 0, 0));
		healthLabel->setText("HP\n");
		healthLabel->setTextSize(22);
		healthLabel->setVerticalAlignment(Label::VerticalAlignment::Center);
		healthLabel->setHorizontalAlignment(Label::HorizontalAlignment::Center);
		healthLabel->setTextStyle(sf::Text::Style::Bold);
		healthLabel->connect("mouseentered", guiEnteredHandler);
		healthLabel->connect("mouseleft", guiLeftHandler);
		m_gui->add(healthLabel);
		m_gui->setWidgetName(healthLabel, "currentCharHealth");

		// health tooltip
		Label::Ptr healthLabelTooltip = theme->load("ToolTip");
		healthLabelTooltip->setText("Hit-Points \nCharacter dies if his Hit-Points fall below 1!");
		healthLabel->setToolTip(healthLabelTooltip);

		// AP
		Label::Ptr apLabel = theme->load("Label");
		apLabel->setPosition(201, 665);
		apLabel->setSize(38, 29);
		apLabel->setTextColor(tgui::Color(0, 0, 0));
		apLabel->setText("AP\n");
		apLabel->setTextSize(22);
		apLabel->setVerticalAlignment(Label::VerticalAlignment::Center);
		apLabel->setHorizontalAlignment(Label::HorizontalAlignment::Center);
		apLabel->setTextStyle(sf::Text::Style::Bold);
		apLabel->connect("mouseentered", guiEnteredHandler);
		apLabel->connect("mouseleft", guiLeftHandler);
		m_gui->add(apLabel);
		m_gui->setWidgetName(apLabel, "currentCharAP");

		// AP tooltip
		Label::Ptr apLabelTooltip = theme->load("ToolTip");
		apLabelTooltip->setText("Action Points \nDetermine how many actions a character\ncan perform per turn. (Movement, Skills)");
		apLabel->setToolTip(apLabelTooltip);

		// Level
		Label::Ptr lvlLabel = theme->load("Label");
		lvlLabel->setPosition(241, 571);
		lvlLabel->setSize(38, 29);
		lvlLabel->setTextColor(tgui::Color(0, 0, 0));
		lvlLabel->setText("LvL\n");
		lvlLabel->setTextSize(24);
		lvlLabel->setVerticalAlignment(Label::VerticalAlignment::Center);
		lvlLabel->setHorizontalAlignment(Label::HorizontalAlignment::Center);
		lvlLabel->setTextStyle(sf::Text::Style::Bold);
		lvlLabel->connect("mouseentered", guiEnteredHandler);
		lvlLabel->connect("mouseleft", guiLeftHandler);
		m_gui->add(lvlLabel);
		m_gui->setWidgetName(lvlLabel, "currentCharLvl");

		// Level tooltip
		Label::Ptr lvlLabelTooltip = theme->load("ToolTip");
		lvlLabelTooltip->setText("Level \nThe current Level of the character");
		lvlLabel->setToolTip(lvlLabelTooltip);
#pragma endregion


		// Call the start function when the button is pressed
		endTurnBtn->connect("clicked", []() 
		{ 
			Get<ResourceManager>().PlaySound("BtnPress");
			Get<EventBus>().Raise(EventType::GuiEndTurnButtonClicked, new EventArgs()); 
		});

		// Call the exit function when the button is pressed
		quitBtn->connect("clicked", []() { Get<EventBus>().Raise(EventType::TurnSystemShuttingDown, new EventArgs());  });
	}
	catch (const Exception& e)
	{
		LOG(ERROR) << "Failed to load TGUI widgets: " << e.what();
	}
}

void GUIGameplayScreen::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	Picture* picture = dynamic_cast<Picture*>(m_gui->get("currentCharPicture", true).get());
	Label* hp = dynamic_cast<Label*>(m_gui->get("currentCharHealth", true).get());
	Label* ap = dynamic_cast<Label*>(m_gui->get("currentCharAP", true).get());
	Label* lvl = dynamic_cast<Label*>(m_gui->get("currentCharLvl", true).get());
		
	auto object = l_args->GetGameObject();
	auto character = object->GetComponent<PlayableCharacter>();

	auto characterSprite = object->GetComponent<SpriteRenderable>()->GetSprite();
	auto hpValue = character->GetRole()->GetMainAttribute(Constants::Attribute::HitPoints)->GetCurrentValue();
	auto apValue = character->GetRole()->GetMainAttribute(Constants::Attribute::ActionPoints)->GetCurrentValue();
	auto lvlValue = character->GetRole()->GetLevel();
	
	picture->setTexture({ *characterSprite.getTexture(), characterSprite.getTextureRect() });
	hp->setText(to_string(hpValue));
	ap->setText(to_string(apValue));
	lvl->setText(to_string(lvlValue));
}

void GUIGameplayScreen::OnGridCellClicked(GridCellClickedEventArgs* l_args)
{
	if (l_args->GetButton() == Mouse::Button::Left)
	{
		Picture* picture = dynamic_cast<Picture*>(m_gui->get("hoverCharPicture", true).get());
		Label* hp = dynamic_cast<Label*>(m_gui->get("hoverCharHealth", true).get());
		Label* ap = dynamic_cast<Label*>(m_gui->get("hoverCharAP", true).get());
		Label* lvl = dynamic_cast<Label*>(m_gui->get("hoverCharLevel", true).get());

		if (l_args->GetCell()->GetIsOccupied())
		{
			// if one of the occupants is a Player or Enemy --> update displayed information
			auto object = l_args->GetCell()->GetOccupantWithAnyTag({ GameObjectTag::Player, GameObjectTag::Enemy });
			
			if (object != nullptr)
			{
				auto character = object->GetComponent<PlayableCharacter>();

				auto characterSprite = object->GetComponent<SpriteRenderable>()->GetSprite();
				auto hpValue = character->GetRole()->GetMainAttribute(Constants::Attribute::HitPoints)->GetCurrentValue();
				auto apValue = character->GetRole()->GetMainAttribute(Constants::Attribute::ActionPoints)->GetCurrentValue();
				auto lvlValue = character->GetRole()->GetLevel();

				picture->setTexture({ *characterSprite.getTexture(), characterSprite.getTextureRect() });
				hp->setText("HP: " + to_string(hpValue));
				ap->setText("AP: " + to_string(apValue));
				lvl->setText("Lvl: " + to_string(lvlValue));
				
				return;
			}
			
		}
		// else --> display default data
		picture->setTexture({ *Get<ResourceManager>().GetTexture(Constants::Texture::GameplayScreenGridCursor), {64,0,16,16} });
		hp->setText("HP:");
		ap->setText("AP:");
		lvl->setText("Lvl:");
	}
}

//void GUIGameplayScreen::OnCharValueChanged(CharacterValueChangedEventArgs* l_args)
//{
//	if (l_args->GetAttributeName() == "ActionPoints")
//	{
//		Label* ap = dynamic_cast<Label*>(m_gui->get("characterAP", true).get());
//		auto apValue = l_args->GetGameObject()->GetComponent<Role>()->GetAttribute("ActionPoints")->GetValue();
//		ap->setText("AP: " + to_string(apValue));
//	}
//
//	if (l_args->GetAttributeName() == "HitPoints")
//	{
//		Label* hp = dynamic_cast<Label*>(m_gui->get("characterHealth", true).get());
//		auto hpValue = l_args->GetGameObject()->GetComponent<Role>()->GetAttribute("HitPoints")->GetValue();
//		hp->setText("Health: " + to_string(hpValue));
//	}
//}
