/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "cxxopts.hpp"

#include <iostream>
#include <string>
#include <filesystem>

#include "mesh_converter.hpp"
#include "texture_converter.hpp"

namespace fs = std::filesystem;

enum class AssetType {
    Invalid,
    Texture,
    Mesh
};

auto get_asset_type(const fs::path& path) -> AssetType {
    if (
        path.extension() == ".png" ||
        path.extension() == ".jpg" ||
        path.extension() == ".jpeg"
    ) {
        return AssetType::Texture;
    }
    if (
        path.extension() == ".obj"
    ) {
        return AssetType::Mesh;
    }
    return AssetType::Invalid;
}

auto asset_type_to_str(AssetType type) {
    return type == AssetType::Texture ? "texture" : "mesh";
}

auto main(int argc, char** argv) -> int {
    auto opts = cxxopts::Options {
        "asset_compiler",
        "Converts source assets into engine-optimized formats."
    };

    opts.add_options()
        ("i,input", "Input file (e.g. .png, .obj)", cxxopts::value<std::string>())
        ("o,output", "Output file path", cxxopts::value<std::string>()->default_value(""))
        ("h,help", "Show help");

    auto options = opts.parse(argc, argv);

    if (options.count("help") || argc == 1) {
        std::cout << opts.help() << "\n";
        return 0;
    }

    if (!options.count("input")) {
        std::cerr << "Error: input file required (-i)\n";
        std::cout << opts.help() << "\n";
        return 1;
    }

    auto input = fs::path(options["input"].as<std::string>());
    if (!fs::exists(input)) {
        std::cerr << "Error: input file does not exist: " << input.string() << "\n";
        return 1;
    }

    auto output = fs::path(options["output"].as<std::string>());
    if (output.empty()) {
        output = input;
    }

    auto asset_type = get_asset_type(input);
    auto result = std::expected<void, std::string>{};
    switch (asset_type) {
        case AssetType::Texture:
            output.replace_extension(".tex");
            result = convert_texture(input, output);
            break;
        case AssetType::Mesh:
            output.replace_extension(".msh");
            result = convert_mesh(input, output);
            break;
        default:
            std::cerr << "Error: unsupported asset type for file: " << input.string() << "\n";
            return 1;
    }

    if (!result) {
        std::cerr << "Error: " << result.error() << '\n';
        return 1;
    }

    std::cout << "Generated " << asset_type_to_str(asset_type) << " " + output.string() + "\n";

    return 0;
}