#ifndef NOU_MATH_COLOR_HPP
#define NOU_MATH_COLOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Utils.hpp"

namespace NOU::NOU_MATH
{
	class NOU_CLASS ColorStorageLayoutImpl final
	{
	private:
		sizeType m_indices[4];

	public:
		constexpr ColorStorageLayoutImpl(sizeType redIndex, sizeType greenIndex, sizeType blueIndex,
			sizeType alphaIndex);

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

	namespace ColorStorageLayout
	{
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

#define NOU_GENERATE_COLOR_CONFIG(name, type, min, max, layout, cmpEpsi)		 \
	struct NOU_CLASS name										 		         \
	{														 	 		         \
		using ChannelType = type;							 	 		         \
		constexpr static ChannelType CHANNEL_MIN = min;		 	 		         \
		constexpr static ChannelType CHANNEL_MAX = max;		 	 		         \
		constexpr static ColorStorageLayoutImpl DEFAULT_STORAGE_LAYOUT = layout; \
		constexpr static ChannelType COMPARE_EPSILON = cmpEpsi;                  \
	};																	         \
																		         \
	constexpr name::ChannelType      name::CHANNEL_MIN;					         \
	constexpr name::ChannelType      name::CHANNEL_MAX;					         \
	constexpr ColorStorageLayoutImpl name::DEFAULT_STORAGE_LAYOUT;				 \
	constexpr name::ChannelType name::COMPARE_EPSILON;

	NOU_GENERATE_COLOR_CONFIG(ColorConfigFloat, float32, 0.0f, 1.0f, ColorStorageLayout::RGBA, 0.0001f);
	NOU_GENERATE_COLOR_CONFIG(ColorConfigByte, uint8, 0, 255, ColorStorageLayout::RGBA, 0);

	template<typename T>
	class NOU_CLASS Color final
	{
	public:
		using Configuration = T;
		using ChannelType = typename Configuration::ChannelType;

		constexpr static ChannelType CHANNEL_MIN = Configuration::CHANNEL_MIN;
		constexpr static ChannelType CHANNEL_MAX = Configuration::CHANNEL_MAX;
		constexpr static ColorStorageLayoutImpl DEFAULT_STORAGE_LAYOUT = 
																	Configuration::DEFAULT_STORAGE_LAYOUT;
		constexpr static ChannelType COMPARE_EPSILON = Configuration::COMPARE_EPSILON;

	private:
		ColorStorageLayoutImpl m_storageLayout;
		ChannelType m_channels[4];

		constexpr static const ChannelType& clampChannel(const ChannelType &channel);

	public:
		constexpr static Color black(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color grey(ChannelType scale = CHANNEL_MAX / static_cast<ChannelType>(2), 
			ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color red(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color yellow(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color green(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color cyan(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color blue(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color purple(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		constexpr static Color white(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);

		constexpr Color();
		constexpr Color(ChannelType red, ChannelType green, ChannelType blue, ChannelType alpha = CHANNEL_MAX,
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);

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

		Color& invert(boolean invertAlpha = false);
		 
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
		 
		template<typename COL>
		constexpr Color<typename COL::Configuration> convert() const;

		constexpr Color operator + (const Color &other) const;
		Color& operator += (const Color &other);
		 
		constexpr Color operator - (const Color &other) const;
		Color& operator -= (const Color &other);
		 
		constexpr Color operator * (const Color &other) const;
		Color& operator *= (const Color &other);

		constexpr boolean operator == (const Color &other) const;

		constexpr boolean operator != (const Color &other) const;

		template<typename CONF>
		constexpr explicit operator Color<CONF>() const;
	};

	using Color32f = Color<ColorConfigFloat>;
	using Colori8  = Color<ColorConfigByte>;

	template<typename T>
	constexpr typename Color<T>::ChannelType Color<T>::CHANNEL_MIN;

	template<typename T>
	constexpr typename Color<T>::ChannelType Color<T>::CHANNEL_MAX;

	template<typename T>
	constexpr ColorStorageLayoutImpl Color<T>::DEFAULT_STORAGE_LAYOUT;

	template<typename T>
	constexpr typename Color<T>::ChannelType Color<T>::COMPARE_EPSILON;

	template<typename T>
	constexpr Color<T> Color<T>::black(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::grey(typename Color<T>::ChannelType scale, 
		typename Color<T>::ChannelType alpha, const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MAX * scale, CHANNEL_MAX * scale, CHANNEL_MAX * scale, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::red(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MAX, CHANNEL_MIN, CHANNEL_MIN, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::yellow(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MIN, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::green(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MIN, CHANNEL_MAX, CHANNEL_MIN, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::cyan(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MIN, CHANNEL_MAX, CHANNEL_MAX, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::blue(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MAX, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::purple(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MAX, CHANNEL_MIN, CHANNEL_MAX, alpha, storageLayout);
	}

	template<typename T>
	constexpr Color<T> Color<T>::white(typename Color<T>::ChannelType alpha,
		const ColorStorageLayoutImpl &storageLayout)
	{
		return Color<T>(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MAX, alpha, storageLayout);
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType& Color<T>::clampChannel(
		const ChannelType &channel)
	{
		return NOU_CORE::clamp(channel, CHANNEL_MIN, CHANNEL_MAX);
	}

	template<typename T>
	constexpr Color<T>::Color<T>() :
		m_storageLayout(DEFAULT_STORAGE_LAYOUT),
		m_channels{ CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN }
	{}

	template<typename T>
	constexpr Color<T>::Color<T>(typename Color<T>::ChannelType red, 
		typename Color<T>::ChannelType green, typename Color<T>::ChannelType blue, 
		typename Color<T>::ChannelType alpha, const ColorStorageLayoutImpl &storageLayout) :
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

	template<typename T>
	void Color<T>::setStorageLayout(const ColorStorageLayoutImpl &storageLayout)
	{
		ChannelType tmp[4] = { getRed(), getGreen(), getBlue(), getAlpha() };

		m_storageLayout = storageLayout;

		setRed(tmp[0]);
		setGreen(tmp[1]);
		setBlue(tmp[2]);
		setAlpha(tmp[3]);
	}

	template<typename T>
	constexpr const ColorStorageLayoutImpl& Color<T>::getStorageLayout() const
	{
		return m_storageLayout;
	}

	template<typename T>
	void Color<T>::setRed(ChannelType value)
	{
		m_channels[m_storageLayout.getRedIndex()] = clampChannel(value);
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType& Color<T>::getRed() const
	{
		return m_channels[m_storageLayout.getRedIndex()];
	}

	template<typename T>
	void Color<T>::setGreen(ChannelType value)
	{
		m_channels[m_storageLayout.getGreenIndex()] = clampChannel(value);
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType& Color<T>::getGreen() const
	{
		return m_channels[m_storageLayout.getGreenIndex()];
	}

	template<typename T>
	void Color<T>::setBlue(ChannelType value)
	{
		m_channels[m_storageLayout.getBlueIndex()] = clampChannel(value);
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType& Color<T>::getBlue() const
	{
		return m_channels[m_storageLayout.getBlueIndex()];
	}

	template<typename T>
	void Color<T>::setAlpha(ChannelType value)
	{
		m_channels[m_storageLayout.getAlphaIndex()] = clampChannel(value);
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType& Color<T>::getAlpha() const
	{
		return m_channels[m_storageLayout.getAlphaIndex()];
	}

	template<typename T>
	Color<T>& Color<T>::invert(boolean invertAlpha)
	{
		setRed(CHANNEL_MAX - getRed());
		setGreen(CHANNEL_MAX - getGreen());
		setBlue(CHANNEL_MAX - getBlue());

		if (invertAlpha)
			setAlpha(CHANNEL_MAX - getAlpha());

		return *this;
	}

	template<typename T>
	constexpr Color<T> Color<T>::add(const Color<T> &other) const
	{
		return Color<T>(clampChannel(getRed() + other.getRed()),
			clampChannel(getGreen() + other.getGreen()),
			clampChannel(getBlue() + other.getBlue()),
			clampChannel(getAlpha() + other.getAlpha()),
			m_storageLayout);
	}

	template<typename T>
	Color<T>& Color<T>::addAssign(const Color<T> &other)
	{
		setRed(clampChannel(getRed() + other.getRed()));
		setGreen(clampChannel(getGreen() + other.getGreen()));
		setBlue(clampChannel(getBlue() + other.getBlue()));
		setAlpha(clampChannel(getAlpha() + other.getAlpha()));

		return *this;
	}

	template<typename T>
	constexpr Color<T> Color<T>::sub(const Color<T> &other) const
	{
		return Color<T>(clampChannel(getRed() - other.getRed()),
			clampChannel(getGreen() - other.getGreen()),
			clampChannel(getBlue() - other.getBlue()),
			clampChannel(getAlpha() - other.getAlpha()),
			m_storageLayout);
	}

	template<typename T>
	Color<T>& Color<T>::subAssign(const Color<T> &other)
	{
		setRed(clampChannel(getRed() - other.getRed()));
		setGreen(clampChannel(getGreen() - other.getGreen()));
		setBlue(clampChannel(getBlue() - other.getBlue()));
		setAlpha(clampChannel(getAlpha() - other.getAlpha()));

		return *this;
	}

	template<typename T>
	constexpr Color<T> Color<T>::mult(const Color<T> &other) const
	{
		return Color<T>(clampChannel(getRed() * other.getRed()),
			clampChannel(getGreen() * other.getGreen()),
			clampChannel(getBlue() * other.getBlue()),
			clampChannel(getAlpha() * other.getAlpha()),
			m_storageLayout);
	}

	template<typename T>
	Color<T>& Color<T>::multAssign(const Color<T> &other)
	{
		setRed(clampChannel(getRed() * other.getRed()));
		setGreen(clampChannel(getGreen() * other.getGreen()));
		setBlue(clampChannel(getBlue() * other.getBlue()));
		setAlpha(clampChannel(getAlpha() * other.getAlpha()));

		return *this;
	}

	template<typename T>
	constexpr Color<T> Color<T>::copy() const
	{
		return *this;
	}

	template<typename T>
	constexpr boolean Color<T>::equal(const Color<T> &other) const
	{
		return (this == &other) ||
			((NOU_DAT_ALG::epsilonCompare(getRed(), other.getRed(), COMPARE_EPSILON) == 0) &&
			 (NOU_DAT_ALG::epsilonCompare(getGreen(), other.getGreen(), COMPARE_EPSILON) == 0) &&
			 (NOU_DAT_ALG::epsilonCompare(getBlue(), other.getBlue(), COMPARE_EPSILON) == 0) &&
			 (NOU_DAT_ALG::epsilonCompare(getAlpha(), other.getAlpha(), COMPARE_EPSILON) == 0));
	}

	template<typename T>
	constexpr boolean Color<T>::unequal(const Color<T> &other) const
	{
		return !equal(other);
	}

	template<typename T>
	typename Color<T>::ChannelType* Color<T>::data()
	{
		return m_channels;
	}

	template<typename T>
	constexpr const typename Color<T>::ChannelType* Color<T>::data() const
	{
		return m_channels;
	}

	template<typename T>
	template<typename COL>
	constexpr Color<typename COL::Configuration> Color<T>::convert() const
	{
		using ReturnType = Color<typename COL::Configuration>;

		return ReturnType(getRed() * ReturnType::CHANNEL_MAX, getGreen() * ReturnType::CHANNEL_MAX,
			getBlue() * ReturnType::CHANNEL_MAX, getAlpha() * ReturnType::CHANNEL_MAX, getStorageLayout());
	}

	template<typename T>
	constexpr Color<T> Color<T>::operator + (const Color<T> &other) const
	{
		return add(other);
	}

	template<typename T>
	Color<T>& Color<T>::operator += (const Color<T> &other)
	{
		return addAssign(other);
	}

	template<typename T>
	constexpr Color<T> Color<T>::operator - (const Color<T> &other) const
	{
		return sub(other);
	}

	template<typename T>
	Color<T>& Color<T>::operator -= (const Color<T> &other)
	{
		return subAssign(other);
	}

	template<typename T>
	constexpr Color<T> Color<T>::operator * (const Color<T> &other) const
	{
		return mult(other);
	}

	template<typename T>
	Color<T>& Color<T>::operator *= (const Color<T> &other)
	{
		return multAssign(other);
	}

	template<typename T>
	constexpr boolean Color<T>::operator == (const Color<T> &other) const
	{
		return equal(other);
	}

	template<typename T>
	constexpr boolean Color<T>::operator != (const Color<T> &other) const
	{
		return unequal(other);
	}

	template<typename T>
	template<typename CONF>
	constexpr Color<T>::operator Color<CONF>() const
	{
		return convert<Color<CONF>>();
	}
}

#endif