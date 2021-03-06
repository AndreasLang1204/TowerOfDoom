#pragma once

#include "../Managers/ObjectContainer.h"

using namespace ToD::Managers;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Used to generate pseudo-random values.
	///
	////////////////////////////////////////////////////////////
	class Randomizer :
		public ObjectContainer::SharedObject
	{
		/// Constructors, destructors
	public:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		Randomizer() IsDefault__;

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		~Randomizer() IsDefault__;

		/// Properties
	public:
		////////////////////////////////////////////////////////////
		/// \brief Gets the static runtime type.
		///
		/// \return The static runtime type.
		///
		////////////////////////////////////////////////////////////
		virtual RuntimeType GetRuntimeType() const override;

		////////////////////////////////////////////////////////////
		/// \brief Gets the static runtime type.
		///
		/// \return The static runtime type.
		///
		////////////////////////////////////////////////////////////
		static RuntimeType RuntimeType();

		/// Methods
	public:
		////////////////////////////////////////////////////////////
		/// \brief Sets the randomizer seed.
		///
		/// \param l_seed The randomizer seed.
		///
		////////////////////////////////////////////////////////////
		void SetSeed(const unsigned int l_seed);

		////////////////////////////////////////////////////////////
		/// \brief Creates a random value.
		///
		/// \return The random value.
		///
		////////////////////////////////////////////////////////////
		int Random();

		////////////////////////////////////////////////////////////
		/// \brief Creates a random value.
		///
		/// \param l_min The minimal value.
		/// \param l_max The maximal value.
		///
		/// \return The random value.
		///
		////////////////////////////////////////////////////////////
		int Random(const int l_min, const int l_max);

		/// Members
	private:
		int																	m_value; ///< The current random value.
	};
}
