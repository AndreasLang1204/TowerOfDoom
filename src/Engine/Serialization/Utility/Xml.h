#pragma once

#include "rapidxml.hpp"
#include "../Game/ReferenceType.h"

using namespace rapidxml;
using namespace std;

namespace ToD
{
	namespace Serialization
	{
		namespace Utility
		{
			////////////////////////////////////////////////////////////
			/// \brief Provides functionality to easily deal with files and file paths.
			///
			////////////////////////////////////////////////////////////
			class Xml :
				public ReferenceType
			{
				/// Constants
			public:
				////////////////////////////////////////////////////////////
				/// \brief The add operator.
				///
				////////////////////////////////////////////////////////////
				static constexpr char										OperatorAdd = '+';

				////////////////////////////////////////////////////////////
				/// \brief The subtract operator.
				///
				////////////////////////////////////////////////////////////
				static constexpr char										OperatorSubtract = '-';

				////////////////////////////////////////////////////////////
				/// \brief The multiply operator.
				///
				////////////////////////////////////////////////////////////
				static constexpr char										OperatorMultiply = '*';

				////////////////////////////////////////////////////////////
				/// \brief The divide operator.
				///
				////////////////////////////////////////////////////////////
				static constexpr char										OperatorDivide = '/';

				/// Constructors, destructors
			private:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				////////////////////////////////////////////////////////////
				Xml() IsDefault__;

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~Xml() IsDefault__;

				/// Properties
			public:
				////////////////////////////////////////////////////////////
				/// \brief Gets the static runtime type.
				///
				/// \return The static runtime type.
				///
				////////////////////////////////////////////////////////////
				virtual RuntimeType GetRuntimeType() const override;

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Gets the first child node of an XML node.
				///
				/// \param l_node The parent node.
				/// \param l_nodeName The child node name.
				///
				/// \exception std::exception: The node has no child with the specified name.
				///
				////////////////////////////////////////////////////////////
				static xml_node<>* GetNode(const xml_node<>* l_node, const string l_nodeName);

				////////////////////////////////////////////////////////////
				/// \brief Gets the all child nodes of an XML node.
				///
				/// \param l_node The parent node.
				/// \param l_nodeName The child node name.
				///
				/// \exception std::exception: The node has no childs with the specified name.
				///
				////////////////////////////////////////////////////////////
				static vector<xml_node<>*> GetNodes(const xml_node<>* l_node, const string l_nodeName);

				////////////////////////////////////////////////////////////
				/// \brief Gets the first attribute with a specific name of an XML node.
				///
				/// \param l_node The parent node.
				/// \param l_attributeName The attribute name.
				///
				/// \exception std::exception: The node has no attribute with the specified name.
				///
				////////////////////////////////////////////////////////////
				static xml_attribute<>* GetAttribute(const xml_node<>* l_node, const string l_attributeName);

				/*
				////////////////////////////////////////////////////////////
				/// \brief Splits a string by the use of a separator and ensures a certain split length.
				///
				/// \param l_value The string to split.
				/// \param l_separator The separator to use.
				/// \param l_length The expected length.
				///
				/// \return The splitted string as a vector of strings.
				///
				/// \exception std::exception: The actual length of the split is not equal to the expected length.
				///
				////////////////////////////////////////////////////////////
				static vector<string> SplitExactly(const string l_value, const string l_separator, const int l_length);

				////////////////////////////////////////////////////////////
				/// \brief Splits a string by the use of a separator and ensures a certain split length.
				///
				/// The split length will not be checked if l_length is less than zero.
				///
				/// \param l_value The string to split.
				/// \param l_separator The separator to use.
				///
				/// \return The splitted string as a vector of strings.
				///
				////////////////////////////////////////////////////////////
				static vector<string> Split(const string l_value, const string l_separator);

				////////////////////////////////////////////////////////////
				/// \brief Splits a string by a specific separator.
				///
				/// \param l_value The string to split.
				/// \param l_separator The separator to use.
				///
				/// \return The split string as vector of strings.
				///
				////////////////////////////////////////////////////////////
				static vector<string> Split(const string l_value, const char l_separator);

				////////////////////////////////////////////////////////////
				/// \brief Converts a formula from infix to postfix notation.
				///
				/// Blank spaces are placed between formula items.
				///
				/// \param l_formula The formlua in infix notation.
				/// \param l_referenceNames Array where references are added, defined in the formula.
				///
				/// \return The formula in postfix notation.
				///
				////////////////////////////////////////////////////////////
				static string InfixToPostfix(const string l_formula, vector<string>& l_referenceNames);

				////////////////////////////////////////////////////////////
				/// \brief Extracts the roll count and dice value in infix notation from a certain string.
				///
				/// \param l_value The value string.
				/// \param l_rollCount The extracted roll count.
				/// \param l_diceValue The extracted dice value.
				/// \param l_referenceNames Array where references are added, defined in the formula.
				///
				/// \return When the method returns the extracted values are stored in l_rollCount and l_diceValue.
				///
				/// \exception std::exception: The extraction was not possible because the string was not well formatted.
				///
				////////////////////////////////////////////////////////////
				static void ExtractRollCountAndDiceValueAsInfix(const string l_value, string& l_rollCount, string& l_diceValue, vector<string>& l_referenceNames);
				*/
			};
		}
	}
}
