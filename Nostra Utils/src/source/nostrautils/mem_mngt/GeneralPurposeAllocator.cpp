#include "nostrautils/mem_mngt/GeneralPurposeAllocator.hpp"

namespace NOU::NOU_MEM_MNGT
{
	internal::GeneralPurposeAllocatorFreeChunk::GeneralPurposeAllocatorFreeChunk(byte* addr, sizeType size) :
		m_addr(addr),
		m_size(size)
	{
		//do nothing
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::touches
	(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		if (m_addr + m_size == other.m_addr)
		{
			return true;
		}

		if (other.m_addr + other.m_size == m_addr)
		{
			return true;
		}

		return false;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator>
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr > other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator<
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr < other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator>=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr >= other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator<=
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr <= other.m_addr;
	}

	boolean internal::GeneralPurposeAllocatorFreeChunk::operator==
		(const GeneralPurposeAllocatorFreeChunk& other) const
	{
		return m_addr == other.m_addr;
	}

	GeneralPurposeAllocator::GeneralPurposeAllocator(sizeType size) :
		m_size(size)
	{
		m_data = new byte[m_size];
		m_freeChunks.pushBack(internal::GeneralPurposeAllocatorFreeChunk(m_data, m_size));
	}

	GeneralPurposeAllocator::~GeneralPurposeAllocator()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}
}