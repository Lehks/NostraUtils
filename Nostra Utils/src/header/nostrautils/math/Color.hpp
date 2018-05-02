#ifndef NOU_MATH_COLOR_HPP
#define NOU_MATH_COLOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/StringView.hpp"

namespace NOU::NOU_MATH
{
	class ColorStorageLayout;

	class NOU_CLASS ColorStorageLayoutImpl final
	{
		friend class ColorStorageLayout;

	private:
		sizeType m_indices[4];

		constexpr ColorStorageLayoutImpl(sizeType redIndex, sizeType greenIndex, sizeType blueIndex, 
			sizeType alphaIndex);

	public:
		constexpr ColorStorageLayoutImpl();

		constexpr sizeType getRedIndex() const;
		constexpr sizeType getGreenIndex() const;
		constexpr sizeType getBlueIndex() const;
		constexpr sizeType getAlphaIndex() const;

		constexpr boolean operator == (const ColorStorageLayoutImpl &other) const;
		constexpr boolean operator != (const ColorStorageLayoutImpl &other) const;
	};

//======================== Implementation required here, to construct instances in ColorStorageLayout
	constexpr ColorStorageLayoutImpl::ColorStorageLayoutImpl(sizeType redIndex, sizeType greenIndex, 
		sizeType blueIndex, sizeType alphaIndex) :
		m_indices{ redIndex, greenIndex, blueIndex, alphaIndex }
	{}

	constexpr sizeType ColorStorageLayoutImpl::getRedIndex() const
	{
		return m_indices[0];
	}

	constexpr sizeType ColorStorageLayoutImpl::getGreenIndex() const
	{
		return m_indices[1];
	}

	constexpr sizeType ColorStorageLayoutImpl::getBlueIndex() const
	{
		return m_indices[2];
	}

	constexpr sizeType ColorStorageLayoutImpl::getAlphaIndex() const
	{
		return m_indices[3];
	}

	constexpr boolean ColorStorageLayoutImpl::operator == (const ColorStorageLayoutImpl &other) const
	{
		return (this == &other) || 
			(   getRedIndex() == other.getRedIndex() &&
				getGreenIndex() == other.getGreenIndex() &&
				getBlueIndex() == other.getBlueIndex() &&
				getAlphaIndex() == other.getAlphaIndex());
	}

	constexpr boolean ColorStorageLayoutImpl::operator != (const ColorStorageLayoutImpl &other) const
	{
		return !(*this == other);
	}
//========================

	class NOU_CLASS ColorStorageLayout final
	{
	private:
		ColorStorageLayout() = default;

	public:
		constexpr static ColorStorageLayoutImpl RGBA = ColorStorageLayoutImpl(0, 1, 2, 3);
		constexpr static ColorStorageLayoutImpl RGAB = ColorStorageLayoutImpl(0, 1, 3, 2);
		constexpr static ColorStorageLayoutImpl RBGA = ColorStorageLayoutImpl(0, 2, 1, 3);
		constexpr static ColorStorageLayoutImpl RBAG = ColorStorageLayoutImpl(0, 2, 3, 1);
		constexpr static ColorStorageLayoutImpl RAGB = ColorStorageLayoutImpl(0, 3, 1, 2);
		constexpr static ColorStorageLayoutImpl RABG = ColorStorageLayoutImpl(0, 3, 2, 1);
		constexpr static ColorStorageLayoutImpl GRBA = ColorStorageLayoutImpl(1, 0, 2, 3);
		constexpr static ColorStorageLayoutImpl GRAB = ColorStorageLayoutImpl(1, 0, 3, 2);
		constexpr static ColorStorageLayoutImpl GBRA = ColorStorageLayoutImpl(1, 2, 0, 3);
		constexpr static ColorStorageLayoutImpl GBAR = ColorStorageLayoutImpl(1, 2, 3, 0);
		constexpr static ColorStorageLayoutImpl GARB = ColorStorageLayoutImpl(1, 3, 0, 2);
		constexpr static ColorStorageLayoutImpl GABR = ColorStorageLayoutImpl(1, 3, 2, 0);
		constexpr static ColorStorageLayoutImpl BRGA = ColorStorageLayoutImpl(2, 0, 1, 3);
		constexpr static ColorStorageLayoutImpl BRAG = ColorStorageLayoutImpl(2, 0, 3, 1);
		constexpr static ColorStorageLayoutImpl BGRA = ColorStorageLayoutImpl(2, 1, 0, 3);
		constexpr static ColorStorageLayoutImpl BGAR = ColorStorageLayoutImpl(2, 1, 3, 0);
		constexpr static ColorStorageLayoutImpl BARG = ColorStorageLayoutImpl(2, 3, 0, 1);
		constexpr static ColorStorageLayoutImpl BAGR = ColorStorageLayoutImpl(2, 3, 1, 0);
		constexpr static ColorStorageLayoutImpl ARGB = ColorStorageLayoutImpl(3, 0, 1, 2);
		constexpr static ColorStorageLayoutImpl ARBG = ColorStorageLayoutImpl(3, 0, 2, 1);
		constexpr static ColorStorageLayoutImpl AGRB = ColorStorageLayoutImpl(3, 1, 0, 2);
		constexpr static ColorStorageLayoutImpl AGBR = ColorStorageLayoutImpl(3, 1, 2, 0);
		constexpr static ColorStorageLayoutImpl ABRG = ColorStorageLayoutImpl(3, 2, 0, 1);
		constexpr static ColorStorageLayoutImpl ABGR = ColorStorageLayoutImpl(3, 2, 1, 0);
	};

	class NOU_CLASS Color final
	{
	public:
		using ChannelType = float32;

		constexpr static ChannelType CHANNEL_MIN = 0.0f;
		constexpr static ChannelType CHANNEL_MAX = 1.0f;

	private:
		ColorStorageLayoutImpl m_storageLayout;
		ChannelType m_channels[4];

		constexpr static const ChannelType& clampChannel(const ChannelType &channel);

	public:
		constexpr static Color black(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color grey(ChannelType scale = CHANNEL_MAX / 2.0f, ChannelType alpha = CHANNEL_MAX);
		constexpr static Color red(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color yellow(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color green(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color cyan(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color blue(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color purple(ChannelType alpha = CHANNEL_MAX);
		constexpr static Color white(ChannelType alpha = CHANNEL_MAX);

		constexpr Color();
		constexpr Color(ChannelType red, ChannelType green, ChannelType blue, ChannelType alpha = CHANNEL_MAX,
			const ColorStorageLayoutImpl &storageLayout = ColorStorageLayout::RGBA);

		void setStorageLayout(const ColorStorageLayoutImpl &storageLayout);
		constexpr const ColorStorageLayoutImpl& getStorageLayout() const;

		void setRed(ChannelType value);
		constexpr const ChannelType& getRed() const;

		void setGreen(ChannelType value);
		constexpr const ChannelType& getGreen() const;

		void setBlue(ChannelType value);
		constexpr const ChannelType& getBlue() const;

		void setAlpha(ChannelType value);
		constexpr const ChannelType& getAlpha() const;

		Color& invert();
		 
		constexpr Color add(const Color &other) const;
		Color& addAssign(const Color &other);
		 
		constexpr Color sub(const Color &other) const;
		Color& subAssign(const Color &other);
		 
		constexpr Color mult(const Color &other) const;
		Color& multAssign(const Color &other);
		 
		constexpr Color copy() const;

		constexpr boolean equal(const Color &other) const;

		constexpr boolean unequal(const Color &other) const;

		 ChannelType* data();
		 constexpr const ChannelType* data() const;
		 
		constexpr Color operator + (const Color &other) const;
		Color& operator += (const Color &other);
		 
		constexpr Color operator - (const Color &other) const;
		Color& operator -= (const Color &other);
		 
		constexpr Color operator * (const Color &other) const;
		Color& operator *= (const Color &other);

		constexpr boolean operator == (const Color &other) const;

		constexpr boolean operator != (const Color &other) const;

	};

	constexpr typename Color::ChannelType Color::CHANNEL_MIN;
	constexpr typename Color::ChannelType Color::CHANNEL_MAX;

	constexpr ColorStorageLayoutImpl::ColorStorageLayoutImpl() :
		m_indices{0, 1, 2, 3}
	{}

	constexpr ColorStorageLayoutImpl ColorStorageLayout::RGBA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::RGAB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::RBGA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::RBAG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::RAGB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::RABG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GRBA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GRAB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GBRA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GBAR;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GARB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::GABR;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BRGA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BRAG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BGRA;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BGAR;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BARG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::BAGR;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::ARGB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::ARBG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::AGRB;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::AGBR;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::ABRG;
	constexpr ColorStorageLayoutImpl ColorStorageLayout::ABGR;



	constexpr Color Color::black(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN, alpha);
	}

	constexpr Color Color::grey(typename Color::ChannelType scale, typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MAX * scale, CHANNEL_MAX * scale, CHANNEL_MAX * scale, alpha);
	}

	constexpr Color Color::red(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MAX, CHANNEL_MIN, CHANNEL_MIN, alpha);
	}

	constexpr Color Color::yellow(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MIN, alpha);
	}

	constexpr Color Color::green(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MIN, CHANNEL_MAX, CHANNEL_MIN, alpha);
	}

	constexpr Color Color::cyan(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MIN, CHANNEL_MAX, CHANNEL_MAX, alpha);
	}

	constexpr Color Color::blue(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MAX, alpha);
	}

	constexpr Color Color::purple(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MAX, CHANNEL_MIN, CHANNEL_MAX, alpha);
	}

	constexpr Color Color::white(typename Color::ChannelType alpha)
	{
		return Color(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MAX, alpha);
	}

	constexpr const Color::ChannelType& Color::clampChannel(const ChannelType &channel)
	{
		return NOU_CORE::clamp(channel, CHANNEL_MIN, CHANNEL_MAX);
	}

	constexpr Color::Color() :
		m_storageLayout(ColorStorageLayout::RGBA),
		m_channels{ CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN }
	{}

	constexpr Color::Color(typename Color::ChannelType red, typename Color::ChannelType green, 
		typename Color::ChannelType blue, typename Color::ChannelType alpha, 
		const ColorStorageLayoutImpl &storageLayout) :
		m_storageLayout(storageLayout),
		m_channels
		{ 
			(storageLayout.getRedIndex() == 0 ? clampChannel(red) : storageLayout.getGreenIndex() == 0 ? 
				clampChannel(green) : storageLayout.getBlueIndex() == 0 ? clampChannel(blue) : 
				clampChannel(alpha)),
			(storageLayout.getRedIndex() == 1 ? clampChannel(red) : storageLayout.getGreenIndex() == 1 ? 
				clampChannel(green) : storageLayout.getBlueIndex() == 1 ? clampChannel(blue) : 
				clampChannel(alpha)),
			(storageLayout.getRedIndex() == 2 ? clampChannel(red) : storageLayout.getGreenIndex() == 2 ? 
				clampChannel(green) : storageLayout.getBlueIndex() == 2 ? clampChannel(blue) : 
				clampChannel(alpha)),
			(storageLayout.getRedIndex() == 3 ? clampChannel(red) : storageLayout.getGreenIndex() == 3 ? 
				clampChannel(green) : storageLayout.getBlueIndex() == 3 ? clampChannel(blue) : 
				clampChannel(alpha))
		}
	{}

	constexpr const ColorStorageLayoutImpl& Color::getStorageLayout() const
	{
		return m_storageLayout;
	}

	constexpr const typename Color::ChannelType& Color::getRed() const
	{
		return m_channels[m_storageLayout.getRedIndex()];
	}

	void Color::setGreen(ChannelType value)
	{
		m_channels[m_storageLayout.getGreenIndex()] = clampChannel(value);
	}

	constexpr const typename Color::ChannelType& Color::getGreen() const
	{
		return m_channels[m_storageLayout.getGreenIndex()];
	}

	constexpr const typename Color::ChannelType& Color::getBlue() const
	{
		return m_channels[m_storageLayout.getBlueIndex()];
	}

	constexpr const typename Color::ChannelType& Color::getAlpha() const
	{
		return m_channels[m_storageLayout.getAlphaIndex()];
	}

	constexpr Color Color::add(const Color &other) const
	{
		return Color(clampChannel(getRed() + other.getRed()),
			clampChannel(getGreen() + other.getGreen()),
			clampChannel(getBlue() + other.getBlue()),
			clampChannel(getAlpha() + other.getAlpha()),
			m_storageLayout);
	}

	constexpr Color Color::sub(const Color &other) const
	{
		return Color(clampChannel(getRed() - other.getRed()),
			clampChannel(getGreen() - other.getGreen()),
			clampChannel(getBlue() - other.getBlue()),
			clampChannel(getAlpha() - other.getAlpha()),
			m_storageLayout);
	}

	constexpr Color Color::mult(const Color &other) const
	{
		return Color(clampChannel(getRed() * other.getRed()),
			clampChannel(getGreen() * other.getGreen()),
			clampChannel(getBlue() * other.getBlue()),
			clampChannel(getAlpha() * other.getAlpha()),
			m_storageLayout);
	}

	constexpr Color Color::copy() const
	{
		return *this;
	}

	constexpr boolean Color::equal(const Color &other) const
	{
		return (this == &other) ||
			(getRed() == other.getRed() &&
			 getGreen() == other.getGreen() &&
			 getBlue() == other.getBlue() &&
			 getAlpha() == other.getAlpha());
	}

	constexpr boolean Color::unequal(const Color &other) const
	{
		return !equal(other);
	}

	constexpr const typename Color::ChannelType* Color::data() const
	{
		return m_channels;
	}

	constexpr Color Color::operator + (const Color &other) const
	{
		return add(other);
	}

	constexpr Color Color::operator - (const Color &other) const
	{
		return sub(other);
	}

	constexpr Color Color::operator * (const Color &other) const
	{
		return mult(other);
	}

	constexpr boolean Color::operator == (const Color &other) const
	{
		return equal(other);
	}

	constexpr boolean Color::operator != (const Color &other) const
	{
		return unequal(other);
	}
}

#endif