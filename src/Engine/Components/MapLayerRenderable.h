#pragma once

#include "AGameComponent.h"
#include "../Components/Renderable.h"

using namespace sf;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to render a map layer.
		///
		////////////////////////////////////////////////////////////
		class MapLayerRenderable :
			public Renderable
		{
			/// Nested classes & structs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Compares sprites by their x position.
			///
			////////////////////////////////////////////////////////////
			struct TileComparerX
			{
				////////////////////////////////////////////////////////////
				/// \brief Compares sprites by their x position.
				///
				/// \param lhs The first sprite.
				/// \param rhs The first sprite.
				///
				/// \return true when lhs x is less than rhs x.
				///
				////////////////////////////////////////////////////////////
				bool operator() (const Sprite* lhs, const Sprite* rhs) const;
			};

			////////////////////////////////////////////////////////////
			/// \brief Compares sprites by their y position.
			///
			////////////////////////////////////////////////////////////
			struct TileComparerY
			{
				////////////////////////////////////////////////////////////
				/// \brief Compares sprites by their y position.
				///
				/// \param lhs The first sprite.
				/// \param rhs The first sprite.
				///
				/// \return true when lhs y is less than rhs y.
				///
				////////////////////////////////////////////////////////////
				bool operator() (const Sprite* lhs, const Sprite* rhs) const;
			};

			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the tile array type.
			///
			////////////////////////////////////////////////////////////
			typedef vector<Sprite*>											TileArray;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the x direction sorted tile set type.
			///
			////////////////////////////////////////////////////////////
			typedef multiset<Sprite*, TileComparerX>						TileSetX;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the y direction sorted tile set type.
			///
			////////////////////////////////////////////////////////////
			typedef multiset<Sprite*, TileComparerY>						TileSetY;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			/// \param l_size The layer size, in tiles not in pixels.
			/// \param l_tileSize Size of a single tile, in pixel.
			///
			////////////////////////////////////////////////////////////
			MapLayerRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, const Vector2i l_size, const Vector2i l_tileSize);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~MapLayerRenderable();

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

			////////////////////////////////////////////////////////////
			/// \brief Gets the tile size in pixel.
			///
			/// \return The tile size.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetTileSize() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the map size in tiles.
			///
			/// \return The map size.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetSize() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Avtivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Avtivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) override;

			////////////////////////////////////////////////////////////
			/// \brief Adds a tile to the map layer.
			///
			/// \param l_tile The til eto add.
			///
			////////////////////////////////////////////////////////////
			void AddTile(Sprite* l_tile);
		
			/// Members
		private:
			Vector2i														m_size; ///< The layer dimension.
			Vector2i														m_tileSize; ///< used tile size (for example 32x32)
			TileArray														m_tiles; ///< Contains all tiles
			TileSetX														m_tilesX; ///< Contains all tiles sorted in x direction
			TileSetY														m_tilesY; ///< Contains all tiles sorted in y direction
		};
	}
}
