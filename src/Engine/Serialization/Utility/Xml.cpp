#include "stdafx.h"

#include "Xml.h"

using namespace ToD;
using namespace ToD::Serialization::Utility;

ReferenceType::RuntimeType Xml::GetRuntimeType() const
{
	return "ToD::Serialization::XmlUtility";
}

xml_node<>* Xml::GetNode(const xml_node<>* l_node, const string l_nodeName)
{
	auto child = l_node->first_node(l_nodeName.c_str());
	if (child == nullptr)
	{
		throw exception(string("The node " + l_nodeName + " is missing.").c_str());
	}

	return child;
}

vector<xml_node<>*> Xml::GetNodes(const xml_node<>* l_node, const string l_nodeName)
{
	auto current = GetNode(l_node, l_nodeName);

	auto nodes = vector<xml_node<char>*>();

	while (current != nullptr)
	{
		nodes.push_back(current);

		current = current->next_sibling(l_nodeName.c_str());
	}

	return nodes;
}

xml_attribute<>* Xml::GetAttribute(const xml_node<>* l_node, const string l_attributeName)
{
	auto attribute = l_node->first_attribute(l_attributeName.c_str());
	if (attribute == nullptr)
	{
		throw exception(string("The node " + string(l_node->name()) + " has no attribute " + l_attributeName + ".").c_str());
	}

	return attribute;
}

/*
vector<string> XmlUtility::SplitExactly(string l_value, const string l_separator, const int l_length)
{
	auto position = size_t(0);
	auto result = vector<string>();

	while ((position = l_value.find(l_separator)) != string::npos)
	{
		result.push_back(l_value.substr(0, position));
		l_value.erase(0, position + l_separator.length());
	}

	result.push_back(l_value);

	if (result.size() == l_length)
	{
		return result;
	}

	auto message = stringstream();
	message << "The size of the splitted string (" << result.size() << ") is not equal to the expected length " << l_length;
	throw exception(message.str().c_str());
}

vector<string> XmlUtility::Split(string l_value, const string l_separator)
{
	auto position = size_t(0);
	auto result = vector<string>();

	while ((position = l_value.find(l_separator)) != string::npos)
	{
		result.push_back(l_value.substr(0, position));
		l_value.erase(0, position + l_separator.length());
	}

	result.push_back(l_value);

	return result;
}

vector<string> XmlUtility::Split(const string l_value, const char l_separator)
{
	auto stringStream = stringstream(l_value);
	auto result = vector<string>();
	auto current = string();

	while (getline(stringStream, current, l_separator))
	{
		result.push_back(current);
	}

	return result;
}

void XmlUtility::ExtractRollCountAndDiceValueAsInfix(const string l_value, string& l_rollCount, string& l_diceValue, vector<string>& l_referenceNames)
{
	constexpr auto ValueSplitLength = 2;
	constexpr auto IndexValueRollCount = 0;
	constexpr auto IndexValueDiceValue = 1;

	auto valueSplit = SplitExactly(l_value, " D ", ValueSplitLength);

	l_rollCount = InfixToPostfix(valueSplit[IndexValueRollCount], l_referenceNames);
	l_diceValue = InfixToPostfix(valueSplit[IndexValueDiceValue], l_referenceNames);
}

string XmlUtility::InfixToPostfix(const string l_formula, vector<string>& l_referenceNames)
{
	// Todo. create unit tests, check for correct round bracets
	// Todo. fix bug-> formula {5 + (ReferenceValue * 2)} is not correctly resolved

	auto postfix = string();
	auto operators = stack<string>();
	auto curly = 0;
	auto valueString = string();
	auto referenceString = string();

	for (auto i = 0u; i < l_formula.size(); ++i)
	{
		auto c = l_formula[i];

		if (c == OperatorAdd || c == OperatorSubtract || c == OperatorMultiply || c == OperatorDivide)
		{
			operators.push(string(1, c));
		}
		else if ('0' <= c && c <= '9')
		{
			valueString += c;
		}
		else if (c == '(')
		{
		}
		else if (c == ')')
		{
			if (!referenceString.empty())
			{
				postfix += referenceString;

				l_referenceNames.push_back(referenceString);

				referenceString.clear();

				postfix += ' ';
			}

			if (!valueString.empty())
			{
				postfix += valueString;

				valueString.clear();

				postfix += ' ';
			}

			if (operators.size() > 0)
			{
				postfix = postfix + operators.top();
				operators.pop();

				postfix += ' ';
			}
		}
		else if (c == ' ')
		{
			if (!referenceString.empty())
			{
				postfix += referenceString;

				l_referenceNames.push_back(referenceString);

				referenceString.clear();

				postfix += ' ';
			}

			if (!valueString.empty())
			{
				postfix += valueString;

				valueString.clear();

				postfix += ' ';
			}
		}
		else if (c == '{' || c == '}')
		{
			curly += static_cast<int>(c);
		}
		else
		{
			referenceString += c;
		}
	}

	if (curly != static_cast<int>('{') + static_cast<int>('}'))
	{
		throw exception("The curly bracets are incorrecly set.");
	}

	if (operators.size() > 1)
	{
		throw exception("The round bracets are incorrectly set.");
	}

	if (!valueString.empty())
	{
		postfix += valueString;

		valueString.clear();

		postfix += ' ';
	}

	if (operators.size() == 1)
	{
		postfix += operators.top();
		operators.pop();
	}

	postfix = Functions::TrimRight(postfix);

	return postfix;
}
*/
