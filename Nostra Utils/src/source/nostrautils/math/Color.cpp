#include "nostrautils/math/Color.hpp"

namespace NOU::NOU_MATH
{

	void Color::setStorageLayout(const ColorStorageLayoutImpl &storageLayout)
	{
		ChannelType tmp[4] = { getRed(), getBlue(), getGreen(), getAlpha() };

		m_storageLayout = storageLayout;

		setRed(tmp[m_storageLayout.getRedIndex()]);
		setGreen(tmp[m_storageLayout.getGreenIndex()]);
		setBlue(tmp[m_storageLayout.getBlueIndex()]);
		setAlpha(tmp[m_storageLayout.getAlphaIndex()]);
	}

	void Color::setRed(ChannelType value)
	{
		m_channels[m_storageLayout.getRedIndex()] = clampChannel(value);
	}

	void Color::setBlue(ChannelType value)
	{
		m_channels[m_storageLayout.getBlueIndex()] = clampChannel(value);
	}

	void Color::setAlpha(ChannelType value)
	{
		m_channels[m_storageLayout.getAlphaIndex()] = clampChannel(value);
	}

	Color& Color::invert()
	{
		setRed(CHANNEL_MAX - getRed());
		setGreen(CHANNEL_MAX - getGreen());
		setBlue(CHANNEL_MAX - getBlue());

		return *this;
	}

	Color& Color::addAssign(const Color &other)
	{
		setRed(clampChannel(getRed() + other.getRed()));
		setGreen(clampChannel(getGreen() + other.getGreen()));
		setBlue(clampChannel(getBlue() + other.getBlue()));
		setAlpha(clampChannel(getAlpha() + other.getAlpha()));

		return *this;
	}

	Color& Color::subAssign(const Color &other)
	{
		setRed(clampChannel(getRed() - other.getRed()));
		setGreen(clampChannel(getGreen() - other.getGreen()));
		setBlue(clampChannel(getBlue() - other.getBlue()));
		setAlpha(clampChannel(getAlpha() - other.getAlpha()));

		return *this;
	}

	Color& Color::multAssign(const Color &other)
	{
		setRed(clampChannel(getRed() * other.getRed()));
		setGreen(clampChannel(getGreen() * other.getGreen()));
		setBlue(clampChannel(getBlue() * other.getBlue()));
		setAlpha(clampChannel(getAlpha() * other.getAlpha()));

		return *this;
	}

	typename Color::ChannelType* Color::data()
	{
		return m_channels;
	}

	Color& Color::operator += (const Color &other)
	{
		return addAssign(other);
	}

	Color& Color::operator -= (const Color &other)
	{
		return subAssign(other);
	}

	Color& Color::operator *= (const Color &other)
	{
		return multAssign(other);
	}
}