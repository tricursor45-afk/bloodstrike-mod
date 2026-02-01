#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "xorstr.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include "includes.h"


#define FIFO_PATH xorstr_("/data/data/" PACKAGE_NAME "/imgui/sync")

static std::map<std::string, bool> sync_bool = {
    {xorstr_("bAIM"), false},
    {xorstr_("bAIM_IgnoreBots"), false},
    {xorstr_("bAIM_CheckVisibility"), false},
    {xorstr_("bAIM_IgnoreKnocked"), false},
    {xorstr_("bAIM_SnapLine"), false},
    {xorstr_("bAIM_DrawFov"), false},
    {xorstr_("bAIM_NoTargetHideFov"), false},

    {xorstr_("bESP"), false},
    {xorstr_("bESP_Line"), false},
    {xorstr_("bESP_LineBots"), false},
    {xorstr_("bESP_Skeleton"), false},
    {xorstr_("bESP_Box"), false},
    {xorstr_("bESP_Health"), false},
    {xorstr_("bESP_Name"), false},
    {xorstr_("bWall"), true},

    {xorstr_("bBulletTrack"), false},
    // {xorstr_("bBulletTrack_IgnoreKnocked"), false},
    // {xorstr_("bBulletTrack_IgnoreBots"), false},

    {xorstr_("bXray"), false},
    {xorstr_("bSkinHack"), false},
    {xorstr_("bSpeed"), false},
    {xorstr_("bSlide"), false},
    {xorstr_("bNoRecoil"), false},
    {xorstr_("bNoSpread"), false},
    {xorstr_("bLessRecoil"), true},


};

static std::map<std::string, float> sync_float = {
    {xorstr_("fAIM_Fov"), 100.0f},
    {xorstr_("fSpeed"), 1.0f},
	{xorstr_("fAIM_FovOffsetY"), 1.0f},
    {xorstr_("fESP_LineThickness"), 2.0f},
    {xorstr_("fAIM_SnapStrength"), 0.1f},
    {xorstr_("fBulletTrack_Probability"), 70.0f},
    {xorstr_("fHeight"), 0.0f},
    {xorstr_("fWidth"), 0.0f}
};

static std::map<std::string, int> sync_int = {
    {xorstr_("iAIM_TargetBone"), 1},
    {xorstr_("iAIM_Trigger"), 0},
    {xorstr_("iESP_Point"), 2},
    {xorstr_("iBulletTrack_TargetBone"), 0},
};


static const char* targetBone[] = { "Head", "Chest", "L Hand", "R Hand", "L Foot", "R Foot", "Pelvis" };
static const char* aimbotTrigger[] = { "Aim+Shoot", "Aim", "Shoot", "Always" };
static const char* espPoint[] = { "Bottom", "Center", "Top" };

static void sync_with_py() {
    json j = json::object();
    
    for (const auto& pair : sync_bool)  j[pair.first] = pair.second;
    for (const auto& pair : sync_float) j[pair.first] = pair.second;
    for (const auto& pair : sync_int)   j[pair.first] = pair.second;
    
    std::string serialized = j.dump();
    
    int fd = open(FIFO_PATH, O_WRONLY | O_NONBLOCK);
    if (fd >= 0) {
        write(fd, serialized.c_str(), serialized.length());
        write(fd, "\n", 1);
        close(fd);
    }
}
