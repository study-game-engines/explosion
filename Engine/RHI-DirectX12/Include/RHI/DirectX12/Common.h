//
// Created by johnk on 10/1/2022.
//

#pragma once

#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <format>
#include <functional>

#include <dxgi1_4.h>
#include <d3d12.h>

#include <Common/Debug.h>
#include <RHI/Common.h>

// duplicated code because static variable and namespace
namespace RHI::DirectX12 {
    template <typename A, typename B>
    static const std::unordered_map<A, B> DX12_ENUM_MAP;

    template <typename A, typename B>
    B DX12EnumCast(const A& value)
    {
        auto iter = DX12_ENUM_MAP<A, B>.find(value);
        Assert((iter != DX12_ENUM_MAP<A, B>.end()));
        return static_cast<B>(iter->second);
    }

#define DX12_ENUM_MAP_BEGIN(A, B) template <> static const std::unordered_map<A, B> DX12_ENUM_MAP<A, B> = {
#define DX12_ENUM_MAP_ITEM(A, B) { A, B },
#define DX12_ENUM_MAP_END() };

    template <typename E>
    using BitsTypeForEachFunc = std::function<void(E e)>;

    template <typename E>
    void ForEachBitsType(BitsTypeForEachFunc<E>&& func)
    {
        using UBitsType = std::underlying_type_t<E>;
        for (UBitsType i = 0x1; i < static_cast<UBitsType>(E::MAX); i = i << 1) {
            func(static_cast<E>(i));
        }
    }
}

// hard code convert
namespace RHI::DirectX12 {
    GpuType GetGpuTypeByAdapterFlag(UINT flag);
}

// enum cast impl
namespace RHI::DirectX12 {
    DX12_ENUM_MAP_BEGIN(QueueType, D3D12_COMMAND_LIST_TYPE)
        DX12_ENUM_MAP_ITEM(QueueType::GRAPHICS, D3D12_COMMAND_LIST_TYPE_DIRECT)
        DX12_ENUM_MAP_ITEM(QueueType::COMPUTE, D3D12_COMMAND_LIST_TYPE_COMPUTE)
        DX12_ENUM_MAP_ITEM(QueueType::TRANSFER, D3D12_COMMAND_LIST_TYPE_COPY)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(PixelFormat, DXGI_FORMAT)
        // 8-Bits
        DX12_ENUM_MAP_ITEM(PixelFormat::R8_UNORM, DXGI_FORMAT_R8_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::R8_SNORM, DXGI_FORMAT_R8_SNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::R8_UINT, DXGI_FORMAT_R8_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::R8_SINT, DXGI_FORMAT_R8_SINT)
        // 16-Bits
        DX12_ENUM_MAP_ITEM(PixelFormat::R16_UINT, DXGI_FORMAT_R16_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::R16_SINT, DXGI_FORMAT_R16_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::R16_FLOAT, DXGI_FORMAT_R16_FLOAT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG8_UNORM, DXGI_FORMAT_R8G8_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG8_SNORM, DXGI_FORMAT_R8G8_SNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG8_UINT, DXGI_FORMAT_R8G8_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG8_SINT, DXGI_FORMAT_R8G8_SINT)
        // 32-Bits
        DX12_ENUM_MAP_ITEM(PixelFormat::R32_UINT, DXGI_FORMAT_R32_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::R32_SINT, DXGI_FORMAT_R32_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::R32_FLOAT, DXGI_FORMAT_R32_FLOAT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG16_UINT, DXGI_FORMAT_R16G16_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG16_SINT, DXGI_FORMAT_R16G16_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG16_FLOAT, DXGI_FORMAT_R16G16_FLOAT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA8_UNORM_SRGB, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA8_SNORM, DXGI_FORMAT_R8G8B8A8_SNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA8_UINT, DXGI_FORMAT_R8G8B8A8_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA8_SINT, DXGI_FORMAT_R8G8B8A8_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::BGRA8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::BGRA8_UNORM_SRGB, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGB9_E5_FLOAT, DXGI_FORMAT_R9G9B9E5_SHAREDEXP)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGB10A2_UNORM, DXGI_FORMAT_R10G10B10A2_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG11B10_FLOAT, DXGI_FORMAT_R11G11B10_FLOAT)
        // 64-Bits
        DX12_ENUM_MAP_ITEM(PixelFormat::RG32_UINT, DXGI_FORMAT_R32G32_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG32_SINT, DXGI_FORMAT_R32G32_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RG32_FLOAT, DXGI_FORMAT_R32G32_FLOAT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA16_UINT, DXGI_FORMAT_R16G16B16A16_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA16_SINT, DXGI_FORMAT_R16G16B16A16_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT)
        // 128-Bits
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA32_UINT, DXGI_FORMAT_R32G32B32A32_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA32_SINT, DXGI_FORMAT_R32G32B32A32_SINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::RGBA32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT)
        // Depth-Stencil
        DX12_ENUM_MAP_ITEM(PixelFormat::D16_UNORM, DXGI_FORMAT_D16_UNORM)
        DX12_ENUM_MAP_ITEM(PixelFormat::D24_UNORM_S8_UINT, DXGI_FORMAT_D24_UNORM_S8_UINT)
        DX12_ENUM_MAP_ITEM(PixelFormat::D32_FLOAT, DXGI_FORMAT_D32_FLOAT)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(VertexFormat, DXGI_FORMAT)
        // 8-Bits Channel
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT8_X2, DXGI_FORMAT_R8G8_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT8_X4, DXGI_FORMAT_R8G8B8A8_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT8_X2, DXGI_FORMAT_R8G8_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT8_X4, DXGI_FORMAT_R8G8B8A8_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UNORM8_X2, DXGI_FORMAT_R8G8_UNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::UNORM8_X4, DXGI_FORMAT_R8G8B8A8_UNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::SNORM8_X2, DXGI_FORMAT_R8G8_SNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::SNORM8_X4, DXGI_FORMAT_R8G8B8A8_SNORM)
        // 16-Bits Channel
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT16_X2, DXGI_FORMAT_R16G16_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT16_X4, DXGI_FORMAT_R16G16B16A16_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT16_X2, DXGI_FORMAT_R16G16_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT16_X4, DXGI_FORMAT_R16G16B16A16_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UNORM16_X2, DXGI_FORMAT_R16G16_UNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::UNORM16_X4, DXGI_FORMAT_R16G16B16A16_UNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::SNORM16_X2, DXGI_FORMAT_R16G16_SNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::SNORM16_X4, DXGI_FORMAT_R16G16B16A16_SNORM)
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT16_X2, DXGI_FORMAT_R16G16_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT16_X4, DXGI_FORMAT_R16G16B16A16_FLOAT)
        // 32-Bits Channel
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT32_X1, DXGI_FORMAT_R32_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT32_X2, DXGI_FORMAT_R32G32_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT32_X3, DXGI_FORMAT_R32G32B32_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::FLOAT32_X4, DXGI_FORMAT_R32G32B32A32_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT32_X1, DXGI_FORMAT_R32_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT32_X2, DXGI_FORMAT_R32G32_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT32_X3, DXGI_FORMAT_R32G32B32_FLOAT)
        DX12_ENUM_MAP_ITEM(VertexFormat::UINT32_X4, DXGI_FORMAT_R32G32B32A32_UINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT32_X1, DXGI_FORMAT_R32_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT32_X2, DXGI_FORMAT_R32G32_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT32_X3, DXGI_FORMAT_R32G32B32_SINT)
        DX12_ENUM_MAP_ITEM(VertexFormat::SINT32_X4, DXGI_FORMAT_R32G32B32A32_SINT)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(TextureViewDimension, D3D12_SRV_DIMENSION)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_1D, D3D12_SRV_DIMENSION_TEXTURE1D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D, D3D12_SRV_DIMENSION_TEXTURE2D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D_ARRAY, D3D12_SRV_DIMENSION_TEXTURE2DARRAY)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_CUBE, D3D12_SRV_DIMENSION_TEXTURECUBE)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_CUBE_ARRAY, D3D12_SRV_DIMENSION_TEXTURECUBEARRAY)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_3D, D3D12_SRV_DIMENSION_TEXTURE3D)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(TextureViewDimension, D3D12_UAV_DIMENSION)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_1D, D3D12_UAV_DIMENSION_TEXTURE1D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D, D3D12_UAV_DIMENSION_TEXTURE2D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D_ARRAY, D3D12_UAV_DIMENSION_TEXTURE2DARRAY)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_3D, D3D12_UAV_DIMENSION_TEXTURE3D)
        // not support cube and cube array when texture is used as a UAV
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(TextureViewDimension, D3D12_RTV_DIMENSION)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_1D, D3D12_RTV_DIMENSION_TEXTURE1D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D, D3D12_RTV_DIMENSION_TEXTURE2D)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_2D_ARRAY, D3D12_RTV_DIMENSION_TEXTURE2DARRAY)
        DX12_ENUM_MAP_ITEM(TextureViewDimension::TV_3D, D3D12_RTV_DIMENSION_TEXTURE3D)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(AddressMode, D3D12_TEXTURE_ADDRESS_MODE)
        DX12_ENUM_MAP_ITEM(AddressMode::CLAMP_TO_EDGE, D3D12_TEXTURE_ADDRESS_MODE_CLAMP)
        DX12_ENUM_MAP_ITEM(AddressMode::REPEAT, D3D12_TEXTURE_ADDRESS_MODE_WRAP)
        DX12_ENUM_MAP_ITEM(AddressMode::MIRROR_REPEAT, D3D12_TEXTURE_ADDRESS_MODE_MIRROR)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(ComparisonFunc, D3D12_COMPARISON_FUNC)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::NEVER, D3D12_COMPARISON_FUNC_NEVER)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::LESS, D3D12_COMPARISON_FUNC_LESS)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::EQUAL, D3D12_COMPARISON_FUNC_EQUAL)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::LESS_EQUAL, D3D12_COMPARISON_FUNC_LESS_EQUAL)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::GREATER, D3D12_COMPARISON_FUNC_GREATER)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::NOT_EQUAL, D3D12_COMPARISON_FUNC_NOT_EQUAL)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::GREATER_EQUAL, D3D12_COMPARISON_FUNC_GREATER_EQUAL)
        DX12_ENUM_MAP_ITEM(ComparisonFunc::ALWAYS, D3D12_COMPARISON_FUNC_ALWAYS)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(BindingType, D3D12_DESCRIPTOR_RANGE_TYPE)
        DX12_ENUM_MAP_ITEM(BindingType::UNIFORM_BUFFER, D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
        DX12_ENUM_MAP_ITEM(BindingType::STORAGE_BUFFER, D3D12_DESCRIPTOR_RANGE_TYPE_UAV)
        DX12_ENUM_MAP_ITEM(BindingType::SAMPLER, D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER)
        DX12_ENUM_MAP_ITEM(BindingType::TEXTURE, D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
        DX12_ENUM_MAP_ITEM(BindingType::STORAGE_TEXTURE, D3D12_DESCRIPTOR_RANGE_TYPE_UAV)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(ShaderStageBits, D3D12_SHADER_VISIBILITY)
        DX12_ENUM_MAP_ITEM(ShaderStageBits::VERTEX, D3D12_SHADER_VISIBILITY_VERTEX)
        DX12_ENUM_MAP_ITEM(ShaderStageBits::FRAGMENT, D3D12_SHADER_VISIBILITY_PIXEL)
        DX12_ENUM_MAP_ITEM(ShaderStageBits::COMPUTE, D3D12_SHADER_VISIBILITY_ALL)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(PrimitiveTopologyType, D3D12_PRIMITIVE_TOPOLOGY_TYPE)
        DX12_ENUM_MAP_ITEM(PrimitiveTopologyType::POINT, D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT)
        DX12_ENUM_MAP_ITEM(PrimitiveTopologyType::LINE, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE)
        DX12_ENUM_MAP_ITEM(PrimitiveTopologyType::TRIANGLE, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(PrimitiveTopology, D3D_PRIMITIVE_TOPOLOGY)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::POINT_LIST, D3D_PRIMITIVE_TOPOLOGY_POINTLIST)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::LINE_LIST, D3D_PRIMITIVE_TOPOLOGY_LINELIST)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::LINE_STRIP, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::TRIANGLE_LIST, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::TRIANGLE_STRIP, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::LINE_LIST_ADJ, D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::LINE_STRIP_ADJ, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::TRIANGLE_LIST_ADJ, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ)
        DX12_ENUM_MAP_ITEM(PrimitiveTopology::TRIANGLE_STRIP_ADJ, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(BlendOp, D3D12_BLEND_OP)
        DX12_ENUM_MAP_ITEM(BlendOp::OP_ADD, D3D12_BLEND_OP_ADD)
        DX12_ENUM_MAP_ITEM(BlendOp::OP_SUBTRACT, D3D12_BLEND_OP_SUBTRACT)
        DX12_ENUM_MAP_ITEM(BlendOp::OP_REVERSE_SUBTRACT, D3D12_BLEND_OP_REV_SUBTRACT)
        DX12_ENUM_MAP_ITEM(BlendOp::OP_MIN, D3D12_BLEND_OP_MIN)
        DX12_ENUM_MAP_ITEM(BlendOp::OP_MAX, D3D12_BLEND_OP_MAX)
    DX12_ENUM_MAP_END()

    // TODO check this ?
    DX12_ENUM_MAP_BEGIN(BlendFactor, D3D12_BLEND)
        DX12_ENUM_MAP_ITEM(BlendFactor::ZERO, D3D12_BLEND_ZERO)
        DX12_ENUM_MAP_ITEM(BlendFactor::ONE, D3D12_BLEND_ONE)
        DX12_ENUM_MAP_ITEM(BlendFactor::SRC, D3D12_BLEND_SRC_COLOR)
        DX12_ENUM_MAP_ITEM(BlendFactor::ONE_MINUS_SRC, D3D12_BLEND_INV_SRC_COLOR)
        DX12_ENUM_MAP_ITEM(BlendFactor::SRC_ALPHA, D3D12_BLEND_SRC_ALPHA)
        DX12_ENUM_MAP_ITEM(BlendFactor::ONE_MINUS_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA)
        DX12_ENUM_MAP_ITEM(BlendFactor::DST, D3D12_BLEND_DEST_ALPHA)
        DX12_ENUM_MAP_ITEM(BlendFactor::ONE_MINUS_DST, D3D12_BLEND_INV_DEST_COLOR)
        DX12_ENUM_MAP_ITEM(BlendFactor::DST_ALPHA, D3D12_BLEND_DEST_ALPHA)
        DX12_ENUM_MAP_ITEM(BlendFactor::ONE_MINUS_DST_ALPHA, D3D12_BLEND_INV_DEST_ALPHA)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(CullMode, D3D12_CULL_MODE)
        DX12_ENUM_MAP_ITEM(CullMode::NONE, D3D12_CULL_MODE_NONE)
        DX12_ENUM_MAP_ITEM(CullMode::FRONT, D3D12_CULL_MODE_FRONT)
        DX12_ENUM_MAP_ITEM(CullMode::BACK, D3D12_CULL_MODE_BACK)
    DX12_ENUM_MAP_END()

    // see https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_stencil_op
    DX12_ENUM_MAP_BEGIN(StencilOp, D3D12_STENCIL_OP)
        DX12_ENUM_MAP_ITEM(StencilOp::KEEP, D3D12_STENCIL_OP_KEEP)
        DX12_ENUM_MAP_ITEM(StencilOp::ZERO, D3D12_STENCIL_OP_ZERO)
        DX12_ENUM_MAP_ITEM(StencilOp::REPLACE, D3D12_STENCIL_OP_REPLACE)
        DX12_ENUM_MAP_ITEM(StencilOp::INVERT, D3D12_STENCIL_OP_INVERT)
        DX12_ENUM_MAP_ITEM(StencilOp::INCREMENT_CLAMP, D3D12_STENCIL_OP_INCR_SAT)
        DX12_ENUM_MAP_ITEM(StencilOp::DECREMENT_CLAMP, D3D12_STENCIL_OP_DECR_SAT)
        DX12_ENUM_MAP_ITEM(StencilOp::INCREMENT_WRAP, D3D12_STENCIL_OP_INCR)
        DX12_ENUM_MAP_ITEM(StencilOp::DECREMENT_WRAP, D3D12_STENCIL_OP_DECR)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(IndexFormat, DXGI_FORMAT)
        DX12_ENUM_MAP_ITEM(IndexFormat::UINT16, DXGI_FORMAT_R16_UINT)
        DX12_ENUM_MAP_ITEM(IndexFormat::UINT32, DXGI_FORMAT_R32_UINT)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(PresentMode, DXGI_SWAP_EFFECT)
        DX12_ENUM_MAP_ITEM(PresentMode::IMMEDIATELY, DXGI_SWAP_EFFECT_FLIP_DISCARD)
        DX12_ENUM_MAP_ITEM(PresentMode::VSYNC, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(VertexStepMode, D3D12_INPUT_CLASSIFICATION)
        DX12_ENUM_MAP_ITEM(VertexStepMode::PER_VERTEX, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA)
        DX12_ENUM_MAP_ITEM(VertexStepMode::PER_INSTANCE, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA)
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(BufferState, D3D12_RESOURCE_STATES)
        // TODO
    DX12_ENUM_MAP_END()

    DX12_ENUM_MAP_BEGIN(TextureState, D3D12_RESOURCE_STATES)
        DX12_ENUM_MAP_ITEM(TextureState::RENDER_TARGET, D3D12_RESOURCE_STATE_RENDER_TARGET)
        DX12_ENUM_MAP_ITEM(TextureState::PRESENT, D3D12_RESOURCE_STATE_PRESENT)
    DX12_ENUM_MAP_END()
}
