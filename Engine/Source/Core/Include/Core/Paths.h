//
// Created by johnk on 2023/7/31.
//

#pragma once

#include <filesystem>
#include <string>

#include <Core/Api.h>

namespace Core {
    class CORE_API Paths {
    public:
        Paths() = delete;

        static std::filesystem::path WorkingDir();
        static std::filesystem::path EngineRoot();
        static std::filesystem::path EngineShaderPath();
        static std::filesystem::path EngineAssetPath();
        static std::filesystem::path EngineBinariesPath();
        static std::filesystem::path EnginePluginPath();
        static std::filesystem::path EnginePluginAssetPath(const std::string& pluginName);
        static std::filesystem::path ProjectFile();
        static void SetCurrentProjectFile(std::filesystem::path inFile);
        static std::filesystem::path ProjectRoot();
        static std::filesystem::path ProjectAssetPath();
        static std::filesystem::path ProjectBinariesPath();
        static std::filesystem::path ProjectPluginPath();
        static std::filesystem::path ProjectPluginAssetPath(const std::string& pluginName);

    private:
        static std::filesystem::path workdingDir;
        static std::filesystem::path currentProjectFile;
    };
}
