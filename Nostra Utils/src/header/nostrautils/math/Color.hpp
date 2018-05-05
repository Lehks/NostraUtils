#ifndef NOU_MATH_COLOR_HPP
#define NOU_MATH_COLOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Utils.hpp"

/** \file math/Color.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides a class that represents a RGBA color.
*/

namespace NOU::NOU_MATH
{
	/**
	\brief This class defines the layout of the single channels in the memory. 

	\details
	This class defines the layout of the single channels in the memory.

	This class is usually not instantiated by a user. Instead, the predefined constants in the namespace 
	\link nostra::utils::math::ColorStorageLayout ColorStorageLayout\endlink are used.

	\link subsec_configure_storageLayout This chapter\endlink in the color tutorial will hold further 
	information how and why different storage layouts may be used.
	*/
	class NOU_CLASS ColorStorageLayoutImpl final
	{
	private:
		/**
		\brief The indices of the colors in the array of the color class.

		\details
		The indices of the colors in the array of the color class.

		The indices are stored like this:
		
		Index in this Array | Color
		------------------- | -----
		0					| Red
		1					| Green
		2					| Blue
		3					| Alpha
		*/
		sizeType m_indices[4];

	public:
		/**
		\param redIndex   The index of the red channel.
		\param greenIndex The index of the green channel.
		\param blueIndex  The index of the blue channel.
		\param alphaIndex The index of the alpha channel.

		\brief Constructs a new instance from the passed parameters.

		\warning
		This constructor will not check whether two channels have the same index - nevertheless, doing so this 
		will cause bugs.
		*/
		constexpr ColorStorageLayoutImpl(sizeType redIndex, sizeType greenIndex, sizeType blueIndex,
			sizeType alphaIndex);

		/**
		\return The red index.

		\brief Returns the red index.
		*/
		constexpr sizeType getRedIndex() const;

		/**
		\return The green index.

		\brief Returns the green index.
		*/
		constexpr sizeType getGreenIndex() const;

		/**
		\return The blue index.

		\brief Returns the blue index.
		*/
		constexpr sizeType getBlueIndex() const;

		/**
		\return The alpha index.

		\brief Returns the alpha index.
		*/
		constexpr sizeType getAlphaIndex() const;

		/**
		\returns True, if the layouts are equal, false if not.

		\brief Checks whether two storage layouts are the same. They are the same, if all four indices are 
		       the same.
		*/
		constexpr boolean operator == (const ColorStorageLayoutImpl &other) const;

		/**
		\returns False, if the layouts are equal, true if not.

		\brief Checks whether two storage layouts are the same. They are the same, if all four indices are
		the same.
		*/
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

	/**
	\brief A namespace that holds all of the possible color storage layouts as constants.

	\details
	A namespace that holds all of the possible color storage layouts as constants.

	\link subsec_configure_storageLayout This chapter\endlink in the color tutorial will hold further
	information how and why different storage layouts may be used.
	*/
	namespace ColorStorageLayout
	{
		/**
		\brief The color storage layout RGBA.
		*/
		constexpr static ColorStorageLayoutImpl RGBA = ColorStorageLayoutImpl(0, 1, 2, 3);

		/**
		\brief The color storage layout RGAB.
		*/
		constexpr static ColorStorageLayoutImpl RGAB = ColorStorageLayoutImpl(0, 1, 3, 2);

		/**
		\brief The color storage layout RBGA.
		*/
		constexpr static ColorStorageLayoutImpl RBGA = ColorStorageLayoutImpl(0, 2, 1, 3);

		/**
		\brief The color storage layout RBAG.
		*/
		constexpr static ColorStorageLayoutImpl RBAG = ColorStorageLayoutImpl(0, 2, 3, 1);

		/**
		\brief The color storage layout RAGB.
		*/
		constexpr static ColorStorageLayoutImpl RAGB = ColorStorageLayoutImpl(0, 3, 1, 2);

		/**
		\brief The color storage layout RABG.
		*/
		constexpr static ColorStorageLayoutImpl RABG = ColorStorageLayoutImpl(0, 3, 2, 1);

		/**
		\brief The color storage layout GRBA.
		*/
		constexpr static ColorStorageLayoutImpl GRBA = ColorStorageLayoutImpl(1, 0, 2, 3);

		/**
		\brief The color storage layout GRAB.
		*/
		constexpr static ColorStorageLayoutImpl GRAB = ColorStorageLayoutImpl(1, 0, 3, 2);

		/**
		\brief The color storage layout GBRA.
		*/
		constexpr static ColorStorageLayoutImpl GBRA = ColorStorageLayoutImpl(1, 2, 0, 3);

		/**
		\brief The color storage layout GBAR.
		*/
		constexpr static ColorStorageLayoutImpl GBAR = ColorStorageLayoutImpl(1, 2, 3, 0);

		/**
		\brief The color storage layout GARB.
		*/
		constexpr static ColorStorageLayoutImpl GARB = ColorStorageLayoutImpl(1, 3, 0, 2);

		/**
		\brief The color storage layout GABR.
		*/
		constexpr static ColorStorageLayoutImpl GABR = ColorStorageLayoutImpl(1, 3, 2, 0);

		/**
		\brief The color storage layout BRGA.
		*/
		constexpr static ColorStorageLayoutImpl BRGA = ColorStorageLayoutImpl(2, 0, 1, 3);

		/**
		\brief The color storage layout BRAG.
		*/
		constexpr static ColorStorageLayoutImpl BRAG = ColorStorageLayoutImpl(2, 0, 3, 1);

		/**
		\brief The color storage layout BGRA.
		*/
		constexpr static ColorStorageLayoutImpl BGRA = ColorStorageLayoutImpl(2, 1, 0, 3);

		/**
		\brief The color storage layout BGAR.
		*/
		constexpr static ColorStorageLayoutImpl BGAR = ColorStorageLayoutImpl(2, 1, 3, 0);

		/**
		\brief The color storage layout BARG.
		*/
		constexpr static ColorStorageLayoutImpl BARG = ColorStorageLayoutImpl(2, 3, 0, 1);

		/**
		\brief The color storage layout BAGR.
		*/
		constexpr static ColorStorageLayoutImpl BAGR = ColorStorageLayoutImpl(2, 3, 1, 0);

		/**
		\brief The color storage layout ARGB.
		*/
		constexpr static ColorStorageLayoutImpl ARGB = ColorStorageLayoutImpl(3, 0, 1, 2);

		/**
		\brief The color storage layout ARBG.
		*/
		constexpr static ColorStorageLayoutImpl ARBG = ColorStorageLayoutImpl(3, 0, 2, 1);

		/**
		\brief The color storage layout AGRB.
		*/
		constexpr static ColorStorageLayoutImpl AGRB = ColorStorageLayoutImpl(3, 1, 0, 2);

		/**
		\brief The color storage layout AGBR.
		*/
		constexpr static ColorStorageLayoutImpl AGBR = ColorStorageLayoutImpl(3, 1, 2, 0);

		/**
		\brief The color storage layout RABRGGBA.
		*/
		constexpr static ColorStorageLayoutImpl ABRG = ColorStorageLayoutImpl(3, 2, 0, 1);

		/**
		\brief The color storage layout ABGR.
		*/
		constexpr static ColorStorageLayoutImpl ABGR = ColorStorageLayoutImpl(3, 2, 1, 0);
	};

	/**
	\brief A macro that expands to a color configuration class.

	\details
	A macro that expands to a color configuration class.

	\link subsec_configure_typeAndValues This chapter\endlink in the color tutorial will hold further
	information how and why different color configurations may be used.

	\attention
	NOU_GENERATE_COLOR_CONFIG needs to be outside a function body (it may be in a namespace). This is because 
	the macro will expand to a class and definitions for the members in that class.
	*/
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

	///\cond
	NOU_GENERATE_COLOR_CONFIG(ColorConfigFloat, float32, 0.0f, 1.0f, ColorStorageLayout::RGBA, 0.0001f);
	NOU_GENERATE_COLOR_CONFIG(ColorConfigByte, uint8, 0, 255, ColorStorageLayout::RGBA, 0);
	///\endcond

	/**
	\tparam The type of the color configuration that should be used by this color.

	\brief A class that represents a RGBA color.

	\details
	A class that represents a RGBA color.

	\link Color_tut This page\endlink holds a full tutorial about the usage of this class.
	*/
	template<typename T>
	class NOU_CLASS Color final
	{
	public:
		/**
		\brief The type of the configuration.
		*/
		using Configuration = T;
		/**
		\brief The type of the single channels.
		*/
		using ChannelType = typename Configuration::ChannelType;

		/**
		\brief The minimum value for each channel.
		*/
		constexpr static ChannelType CHANNEL_MIN = Configuration::CHANNEL_MIN;

		/**
		\brief The maximum value for each channel.
		*/
		constexpr static ChannelType CHANNEL_MAX = Configuration::CHANNEL_MAX;

		/**
		\brief The storage layout that is used as default parameters.
		*/
		constexpr static ColorStorageLayoutImpl DEFAULT_STORAGE_LAYOUT = 
																	Configuration::DEFAULT_STORAGE_LAYOUT;
		constexpr static ChannelType COMPARE_EPSILON = Configuration::COMPARE_EPSILON;

	private:
		/**
		\brief The current storage layout.
		*/
		ColorStorageLayoutImpl m_storageLayout;

		/**
		\brief The four channels. Their order is defined by the storage layout.
		*/
		ChannelType m_channels[4];

		/**
		\param The value to clamp.

		\return The clamped value.

		\brief Clamps the passed value to the interval \f$\left[CHANNEL_MIN, CHANNEL_MAX\right]\f4.
		*/
		constexpr static const ChannelType& clampChannel(const ChannelType &channel);

	public:
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color black.

		\brief Returns a color that represents black.
		*/
		constexpr static Color black(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color grey.

		\brief Returns a color that represents grey.
		*/
		constexpr static Color grey(NOU::float32 scale = 0.5f, 
			ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color red.

		\brief Returns a color that represents red.
		*/
		constexpr static Color red(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color yellow.

		\brief Returns a color that represents yellow.
		*/
		constexpr static Color yellow(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color green.

		\brief Returns a color that represents green.
		*/
		constexpr static Color green(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color cyan.

		\brief Returns a color that represents cyan.
		*/
		constexpr static Color cyan(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color blue.

		\brief Returns a color that represents blue.
		*/
		constexpr static Color blue(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color purple.

		\brief Returns a color that represents purple.
		*/
		constexpr static Color purple(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);
		/**
		\param alpha         The alpha value of the returned color.
		\param storageLayout The storage layout of the returned color.

		\return The color white.

		\brief Returns a color that represents white.
		*/
		constexpr static Color white(ChannelType alpha = CHANNEL_MAX, 
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);

		/**
		\brief Constructs a new color with the default storage layout. That color will be black without 
		       transparency.
		*/
		constexpr Color();

		/**
		\param red           The value for the red channel.
		\param green         The value for the red channel.
		\param blue          The value for the red channel.
		\param alpha         The value for the red channel.
		\param storageLayout The storage layout.

		\brief Constructs a new color from the passed parameters.
		*/
		constexpr Color(ChannelType red, ChannelType green, ChannelType blue, ChannelType alpha = CHANNEL_MAX,
			const ColorStorageLayoutImpl &storageLayout = DEFAULT_STORAGE_LAYOUT);

		/**
		\param storageLayout The new storage layout.

		\brief Sets the storage layout. The colors will be automatically re-arranged.
		*/
		void setStorageLayout(const ColorStorageLayoutImpl &storageLayout);

		/**
		\return The current storage layout.

		\brief Returns the current storage layout.
		*/
		constexpr const ColorStorageLayoutImpl& getStorageLayout() const;

		/**
		\param The new value for the red channel.

		\brief Sets the value of the red channel.
		*/
		void setRed(ChannelType value);

		/**
		\return The current value of the red channel.

		\brief Returns the current value of the red channel.
		*/
		constexpr const ChannelType& getRed() const;

		/**
		\param The new value for the green channel.

		\brief Sets the value of the green channel.
		*/
		void setGreen(ChannelType value);

		/**
		\return The current value of the green channel.

		\brief Returns the current value of the green channel.
		*/
		constexpr const ChannelType& getGreen() const;

		/**
		\param The new value for the blue channel.

		\brief Sets the value of the blue channel.
		*/
		void setBlue(ChannelType value);

		/**
		\return The current value of the blue channel.

		\brief Returns the current value of the blue channel.
		*/
		constexpr const ChannelType& getBlue() const;

		/**
		\param The new value for the alpha channel.

		\brief Sets the value of the alpha channel.
		*/
		void setAlpha(ChannelType value);

		/**
		\return The current value of the alpha channel.

		\brief Returns the current value of the alpha channel.
		*/
		constexpr const ChannelType& getAlpha() const;

		/**
		\param invertAlpha If true, this method will also invert the alpha channel.

		\return A reference to this instance.

		\brief Inverts the color channel (and the alpha channel if \p invertAlpha is true).
		*/
		Color& invert(boolean invertAlpha = false);
		 
		/**
		\param other The color to add.

		\return The color with the added values.

		\brief Returns a new color that has all of the channel values of this color plus the channel values of 
		       \p other.

		\details
		Returns a new color that has all of the channel values of this color plus the channel values of
		\p other.

		The resulting color will have the same storage layout as this instance.
		*/
		constexpr Color add(const Color &other) const;

		/**
		\param other The color to add.

		\return A reference to this instance.

		\brief Adds the channels of this instance and \p other and assigns them to the channels of this
		       instance.
		*/
		Color& addAssign(const Color &other);

		/**
		\param other The color to subtract.

		\return The color with the subtracted values.

		\brief Returns a new color that has all of the channel values of this color minus the channel values 
		       of \p other.

		\details
		Returns a new color that has all of the channel values of this color minus the channel values of 
		\p other.

		The resulting color will have the same storage layout as this instance.
		*/
		constexpr Color sub(const Color &other) const;

		/**
		\param other The color to subtract.

		\return A reference to this instance.

		\brief Subtracts the channels of this instance and \p other and assigns them to the channels of this
		instance.
		*/
		Color& subAssign(const Color &other);

		/**
		\param other The color to multiply.

		\return The color with the multiplied values.

		\brief Returns a new color that has all of the channel values of this color times the channel values 
		       of \p other.

		\details
		Returns a new color that has all of the channel values of this color times the channel values of 
		\p other.

		The resulting color will have the same storage layout as this instance.
		*/
		constexpr Color mult(const Color &other) const;

		/**
		\param other The color to multiply.

		\return A reference to this instance.

		\brief Multiplies the channels of this instance and \p other and assigns them to the channels of this
		instance.
		*/
		Color& multAssign(const Color &other);
		 
		/**
		\return The copy.

		\brief Returns an exact copy of this instance.
		*/
		constexpr Color copy() const;

		/**
		\brief The color to compare to.

		\return True, if the colors are equal, false if not.

		\brief Compares two colors.

		\details
		Compares two colors. Two colors count as equal, as soon as all channels have the same value. The
		storage layout does not need to be equal.
		*/
		constexpr boolean equal(const Color &other) const;


		/**
		\brief The color to compare to.

		\return False, if the colors are equal, true if not.

		\brief Compares two colors.

		\details
		Compares two colors. Two colors count as equal, as soon as all channels have the same value. The
		storage layout does not need to be equal.
		*/
		constexpr boolean unequal(const Color &other) const;

		/**
		\brief The internal array.

		\brief Returns a pointer to the internal array of channels. This array holds four elements.
		*/
		ChannelType* data();

		/**
		\brief The internal array.

		\brief Returns a pointer to the internal array of channels. This array holds four elements.
		*/
		constexpr const ChannelType* data() const;
		 
		/**
		\tparam The color type (NOT configuration type) to convert to.
		
		\return The converted color.

		\brief Converts a color with one color configuration to a color with another color configuration.
		*/
		template<typename COL>
		constexpr Color<typename COL::Configuration> convert() const;

		/**
		\param The color to add.

		\return this->add(other);

		\brief Returns this->add(other);
		*/
		constexpr Color operator + (const Color &other) const;

		/**
		\param The color to add.

		\return this->addAssign(other);

		\brief Returns this->addAssign(other);
		*/
		Color& operator += (const Color &other);

		/**
		\param The color to subtract.

		\return this->sub(other);

		\brief Returns this->sub(other);
		*/
		constexpr Color operator - (const Color &other) const;

		/**
		\param The color to subtract.

		\return this->subAssign(other);

		\brief Returns this->subAssign(other);
		*/
		Color& operator -= (const Color &other);

		/**
		\param The color to multiply.

		\return this->mult(other);

		\brief Returns this->mult(other);
		*/
		constexpr Color operator * (const Color &other) const;

		/**
		\param The color to multiply.

		\return this->multAssign(other);

		\brief Returns this->multAssign(other);
		*/
		Color& operator *= (const Color &other);

		/**
		\param The color to compare to.

		\return this->equal(other);

		\brief Returns this->equal(other);
		*/
		constexpr boolean operator == (const Color &other) const;

		/**
		\param The color to compare to.

		\return this->unequal(other);

		\brief Returns this->unequal(other);
		*/
		constexpr boolean operator != (const Color &other) const;

		/**
		\tparam The color configuration (NOT color type) to convert to.

		\return this->convert<Color<CONF>>();

		\brief Returns this->convert<Color<CONF>>();
		*/
		template<typename CONF>
		constexpr explicit operator Color<CONF>() const;
	};

	/**
	\brief A color type that uses 32 bit floating point numbers.
	*/
	using Color32f = Color<ColorConfigFloat>;

	/**
	\brief A color type that uses 8 bit integer numbers.
	*/
	using Color8i  = Color<ColorConfigByte>;

	///\cond

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
	constexpr Color<T> Color<T>::grey(NOU::float32 scale, typename Color<T>::ChannelType alpha, 
		const ColorStorageLayoutImpl &storageLayout)
	{
		ChannelType value = static_cast<ChannelType>(CHANNEL_MAX * scale);

		return Color<T>(value, value, value, alpha, storageLayout);
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
		m_channels{ CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MIN, CHANNEL_MAX }
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

		return ReturnType(
			static_cast<typename ReturnType::ChannelType>(getRed() * ReturnType::CHANNEL_MAX), 
			static_cast<typename ReturnType::ChannelType>(getGreen() * ReturnType::CHANNEL_MAX),
			static_cast<typename ReturnType::ChannelType>(getBlue() * ReturnType::CHANNEL_MAX), 
			static_cast<typename ReturnType::ChannelType>(getAlpha() * ReturnType::CHANNEL_MAX), 
			getStorageLayout());
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

	///\endcond
}

#endif