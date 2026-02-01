#pragma once

#include "../imgui.h"
#include "xorstr.hpp"
#include "../../json.hpp"
using json = nlohmann::json;

#include <fstream>

const char* STYLE_PATH = xorstr_("/data/data/" PACKAGE_NAME "/imgui/style.json");
const char* COLOR_PATH = xorstr_("/data/data/" PACKAGE_NAME "/imgui/color.json");
const char* FEATURE_PATH = xorstr_("/data/data/" PACKAGE_NAME "/imgui/feature.json");

static int current_theme = 0;
static float Rounding = 14.0f;



#define CRED ImColor(1.0f, 0.0f, 0.0f, 1.0f)
#define CGREEN ImColor(0.0f, 1.0f, 0.0f, 1.0f)
#define CBLUE ImColor(0.0f, 0.0f, 1.0f, 1.0f)
#define CWHITE ImColor(1.0f, 1.0f, 1.0f, 1.0f)
#define CPINKDARK ImColor(0.78f, 0.08f, 0.52f, 1.0f) // Pink tua

static std::map<std::string, ImColor> colors = {
   {xorstr_("cESP_Line"), CRED},
    {xorstr_("cESP_LineHidden"), CRED},
    {xorstr_("cESP_LineBots"), CWHITE},
    {xorstr_("cESP_LineBotsHidden"), CGREEN},
    {xorstr_("cESP_Skeleton"), CWHITE},
    {xorstr_("cESP_SkeletonHidden"), CGREEN},
    {xorstr_("cESP_Box"), CWHITE},
    {xorstr_("cESP_BoxHidden"), CGREEN},
    {xorstr_("cESP_Health"), CRED},
    {xorstr_("cESP_HealthHidden"), CGREEN},
    {xorstr_("cESP_Name"), CWHITE},
    {xorstr_("cESP_NameHidden"), CWHITE},
    {xorstr_("cESP_Distance"), CWHITE},
    {xorstr_("cESP_DistanceHidden"), CWHITE}
};

static void save_colors() {
    json j;

    for (const auto& pair : colors) j[pair.first] = {pair.second.Value.x, pair.second.Value.y, pair.second.Value.z, pair.second.Value.w};

    std::ofstream out(COLOR_PATH);
    out << j.dump(2);
    out.close();
}

static void load_colors() {
    json j = json::object();

    std::ifstream in(COLOR_PATH);
    if (in.is_open()) {
        try { in >> j; }
        catch(...) {}
        in.close();
    }

    for (auto& pair : colors) {
        if (j.contains(pair.first) && j[pair.first].is_array() && j[pair.first].size() == 4) {
            pair.second.Value.x = j[pair.first][0];
            pair.second.Value.y = j[pair.first][1];
            pair.second.Value.z = j[pair.first][2];
            pair.second.Value.w = j[pair.first][3];
        }
    }
}
static std::map<std::string, bool> _features = {
    {xorstr_("bBetterTouch"), true}
};

static std::map<std::string, bool> features = {
    {xorstr_("bImguiAutoSave"), true},
};

static std::map<std::string, float> features_float = {
    {xorstr_("fFontScale"), 25.0f},
};

static std::map<std::string, std::string> features_string = {
    {xorstr_("key"), xorstr_("")},
};

static void save_features() {
    json j;

    for (const auto& pair : features) j[pair.first] = pair.second;
    for (const auto& pair : features_float) j[pair.first] = pair.second;
    for (const auto& pair : features_string) j[pair.first] = pair.second;

    std::ofstream out(FEATURE_PATH);
    out << j.dump(2);
    out.close();
}

static void load_features() {
    json j = json::object();

    std::ifstream in(FEATURE_PATH);
    if (in.is_open()) {
        try { in >> j; }
        catch(...) {}
        in.close();
    }

    for (auto& pair : features) if (j.contains(pair.first)) pair.second = j[pair.first];
    for (auto& pair : features_float) if (j.contains(pair.first)) pair.second = j[pair.first];
    for (auto& pair : features_string) if (j.contains(pair.first)) pair.second = j[pair.first];
}

static void save_imgui_style(ImGuiStyle* _style = nullptr) {
    json j;

    ImGuiStyle& style = _style ? *_style : ImGui::GetStyle();
    j[xorstr_("BorderSize")] = style.FrameBorderSize;
    j[xorstr_("ScrollbarSize")] = style.ScrollbarSize;
    j[xorstr_("Rounding")] = Rounding;
    j[xorstr_("Alpha")] = style.Alpha;
    j[xorstr_("ThemeIndex")] = current_theme;

    std::ofstream out(STYLE_PATH);
    out << j.dump(2);
    out.close();
}


