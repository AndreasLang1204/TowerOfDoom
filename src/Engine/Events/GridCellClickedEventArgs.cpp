#include "stdafx.h"

#include "GridCellClickedEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

GridCellClickedEventArgs::GridCellClickedEventArgs(MapLayerCellInfo* l_cell, const Vector2i l_position, const Mouse::Button l_button)
: EventArgs()
, m_cell(l_cell)
, m_position(l_position)
, m_button(l_button)
{
}

ReferenceType::RuntimeType GridCellClickedEventArgs::GetRuntimeType() const
{
	return "ToD::Events::GridCellClickedEventArgs";
}

MapLayerCellInfo* GridCellClickedEventArgs::GetCell() const
{
	return m_cell;
}

Vector2i GridCellClickedEventArgs::GetPosition() const
{
	return m_position;
}

Mouse::Button GridCellClickedEventArgs::GetButton() const
{
	return m_button;
}
