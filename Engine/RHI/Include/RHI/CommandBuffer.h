//
// Created by johnk on 21/2/2022.
//

#ifndef EXPLOSION_RHI_COMMAND_BUFFER_H
#define EXPLOSION_RHI_COMMAND_BUFFER_H

#include <Common/Utility.h>

namespace RHI {
    class CommandEncoder;

    struct CommandBufferCreateInfo {
        // TODO
    };

    class CommandBuffer {
    public:
        NON_COPYABLE(CommandBuffer)
        virtual ~CommandBuffer();

        virtual CommandEncoder* Begin() = 0;
        virtual void Destroy() = 0;

    protected:
        explicit CommandBuffer(const CommandBufferCreateInfo* createInfo);
    };
}

#endif//EXPLOSION_RHI_COMMAND_BUFFER_H
