#pragma once

#include <string>

#include "vulkan/vulkan.h"

namespace Walnut {

	enum class ImageFormat
	{
		None = 0,
		RGBA,
		RGBA32F
	};

	// HamSlices, 10/06/2025
	enum class ImageFilter
	{
		Linear = 0,
		Nearest
	};

	class Image
	{
	public:
		Image(std::string_view path);
		
		// HamSlices, 10/06/2025
		Image(std::string_view path, ImageFilter filter = ImageFilter::Linear);
		Image(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr, ImageFilter filter = ImageFilter::Linear);
		~Image();

		void SetData(const void* data);

		VkDescriptorSet GetDescriptorSet() const { return m_DescriptorSet; }

		void Resize(uint32_t width, uint32_t height);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		void AllocateMemory(uint64_t size);
		void Release();
	private:
		uint32_t m_Width = 0, m_Height = 0;

		VkImage m_Image = nullptr;
		VkImageView m_ImageView = nullptr;
		VkDeviceMemory m_Memory = nullptr;
		VkSampler m_Sampler = nullptr;

		ImageFormat m_Format = ImageFormat::None;
		
		// HamSlices, 10/06/2025
		ImageFilter m_Filter = ImageFilter::Linear;

		VkBuffer m_StagingBuffer = nullptr;
		VkDeviceMemory m_StagingBufferMemory = nullptr;

		size_t m_AlignedSize = 0;

		VkDescriptorSet m_DescriptorSet = nullptr;

		std::string m_Filepath;
	};

}



