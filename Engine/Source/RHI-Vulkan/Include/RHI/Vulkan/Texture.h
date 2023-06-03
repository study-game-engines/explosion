//
// Created by Zach Lee on 2022/3/7.
//


#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>
#include <RHI/Texture.h>

namespace RHI::Vulkan {
    class VKDevice;

    class VKTexture : public Texture {
    public:
        NON_COPYABLE(VKTexture)

        VKTexture(VKDevice& device, const TextureCreateInfo& createInfo, vk::Image image);
        VKTexture(VKDevice& device, const TextureCreateInfo& createInfo);
        ~VKTexture() override;

        void Destroy() override;

        TextureView* CreateTextureView(const TextureViewCreateInfo& createInfo) override;

        vk::Image GetImage() const;
        Extent<3> GetExtent() const;
        PixelFormat GetFormat() const;
        vk::ImageSubresourceRange GetFullRange();

    private:
        void CreateImage(const TextureCreateInfo& createInfo);
        void GetAspect(const TextureCreateInfo& createInfo);
        void TransitionToInitState(const TextureCreateInfo& createInfo);

        // TODO use memory pool.
        void AllocateMemory(const TextureCreateInfo& createInfo);
        void FreeMemory();

        VKDevice& device;
        vk::DeviceMemory vkDeviceMemory;
        vk::Image vkImage;
        vk::ImageAspectFlags aspect = vk::ImageAspectFlagBits::eColor;

        Extent<3> extent;
        PixelFormat format;
        uint8_t mipLevels;
        uint8_t samples;
        bool ownMemory;

        friend class VKTextureView;
        vk::ImageView vkImageView = VK_NULL_HANDLE;
    };
}