#include "stdafx.h"

#include "Animation.h"

Animation::Animation(Texture * l_texture)
: ReferenceType()
, m_frames()
, m_texture(l_texture)
{
}

ReferenceType::RuntimeType Animation::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType Animation::RuntimeType()
{
	return "ToD::Components::Animation";
}

void Animation::AddFrame(const IntRect l_frame)
{
	m_frames.push_back(l_frame);
}

const IntRect Animation::GetFrame(const size_t l_frameNr) const
{
	if (l_frameNr < m_frames.size())
	{
		return m_frames[l_frameNr];
	}

	LOG(INFO) << "Invalid Frame number";
	return m_frames[0];
}

size_t Animation::GetFrameCount() const
{
	return m_frames.size();
}

const Texture* Animation::GetTexture() const
{
	return m_texture;
}
