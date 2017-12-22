#ifndef	NOU_CORE_VERSION_HPP
#define	NOU_CORE_VERSION_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

namespace NOU::NOU_CORE
{
	struct NOU_CLASS Version final
	{
	public:
		using VersionType = decltype(NOU_MAKE_VERISON(0, 0, 0));

	private:
		VersionType m_version;

	public:
		constexpr Version(VersionType version);
		constexpr Version(VersionType major, VersionType minor, VersionType patch);

		constexpr VersionType getRaw() const;
		constexpr VersionType getMajor() const;
		constexpr VersionType getMinor() const;
		constexpr VersionType getPatch() const;
	};

	constexpr Version::Version(VersionType version) :
		m_version(version)
	{}

	constexpr Version::Version(VersionType major, VersionType minor, VersionType patch) :
		m_version(NOU_MAKE_VERISON(clamp(major, static_cast<VersionType>(0), NOU_VERSION_MAJOR_MAX),
			clamp(minor, static_cast<VersionType>(0), NOU_VERSION_MINOR_MAX),
			clamp(patch, static_cast<VersionType>(0), NOU_VERSION_PATCH_MAX)))
	{}

	constexpr typename Version::VersionType Version::getRaw() const
	{
		return m_version;
	}

	constexpr typename Version::VersionType Version::getMajor() const
	{
		return NOU_VERSION_MAJOR(m_version);
	}

	constexpr typename Version::VersionType Version::getMinor() const
	{
		return NOU_VERSION_MINOR(m_version);
	}

	constexpr typename Version::VersionType Version::getPatch() const
	{
		return NOU_VERSION_PATCH(m_version);
	}
}

#endif