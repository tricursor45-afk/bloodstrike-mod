#include "include/hpp/imgui.h"
#include <EGL/egl.h>
#include <string>
#include <atomic>
#include <unistd.h>
int Width, Height;
using namespace ImGui;
using namespace std;
#include "xorstr.hpp"
const char* INI_PATH = xorstr_("/data/data/" PACKAGE_NAME "/imgui/.ini");
#include <vector>
#include <jni.h>
#include <android/native_activity.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <android/input.h>
#include <android/keycodes.h>
#include <android/input.h>
#include "curl/json.hpp"
#include "Jni_Stuff.h"
#include <GLES2/gl2.h>
#include "roominfofont.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include "imgui/DreiFont.h"
#include "include/obfuscate.h"
#include "include/hpp/dlfcn.hpp"
#include "include/hpp/imgui/persistence.h"
#include "include/hpp/imgui/touch.h"
#include "include/sync_with_py.h"
#include "include/sync_entities.h"
#include "include/helpers.h"
#include "variables.h"
#include "RGB.h"
#include "Toggle.h"
#include "imgui/stb_image.h"
#include "Starcool.h"
#include "Chams.h"
#include "imgui/DreiFont.h"
#include "imgui/imgui_additional.h"
#include "Oxorany/oxorany.h"
#include "imgui/Icon.h"
#include "xorstr.hpp"
#include "imgui/Iconcpp.h"
#include "imgui/SabFont.h"
#include "Font/Custom.h"
#include "Font/flamee.h"
#include "Font/Japan.h"
#include "Font/lexend_bold.h"
#include "Font/Pubg_Font.h"
#include "Font/ubuntu_medium.h"
#include "imgui/font_awesome.h"
#include "IconsFontAwesome7.h"

#include <ctime>     // Added for expiration check
#include <cstdlib>   // Added for exit(0)
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdio>
#endif
#define ARGB(a, r, g, b) r << 0 | g << 8 | b << 16 | a << 24
#define ReadPointer(type, address) (*(type*)(address))
#define GetFunction(type, address, ...) ((type(*)(__VA_ARGS__))(address))
bool Zaijan = true;
#define CREATE_COLOR(r, g, b, a) new float[4]{(float)r, (float)g, (float)b, (float)a};


#include <string>
#include <cstdlib>


static GLuint menuIconTexture = 0;
static int iconW = 0, iconH = 0;

bool showMenu = false;
ImFont *flamee = nullptr;
ImFont *Japan = nullptr;
ImFont *font1 = nullptr;
ImFont *font2 = nullptr;
ImFont *ubu_0 = nullptr;
ImFont *pubg_font = nullptr;
ImFont* verdana;
namespace font {
    inline ImFont* lexend_bold;
    inline ImFont* lexend_regular;
    inline ImFont* icomoon;
    inline ImFont* icomoon_widget;
    inline ImFont* icomoon_widget2;
	inline ImFont* lexend_general_bold;
    inline ImFont* icomoon_tabs;
}





void DrawCenterText(const char* text, float fontSize)
{
    ImDrawList* draw = ImGui::GetBackgroundDrawList();

    ImVec2 screen = ImGui::GetIO().DisplaySize;

    ImVec2 textSize = ImGui::CalcTextSize(text);
    float scale = fontSize / ImGui::GetFontSize();

    ImVec2 pos(
        (screen.x - textSize.x * scale) * 0.5f,
        (screen.y - textSize.y * scale) * 0.5f
    );

    draw->AddText(
        ImGui::GetFont(),
        fontSize,            
        pos,                  
        IM_COL32(255, 0, 0, 255), 
        text
    );
}

GLuint LoadTextureFromArray(unsigned char* data, int size, int* out_width, int* out_height) {
    int channels;
    unsigned char* image_data = stbi_load_from_memory(data, size, out_width, out_height, &channels, 4);
    if (!image_data) return 0;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *out_width, *out_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image_data);
    return tex;
}



struct My_Patches {
    MemoryPatch Recoil,Magic,Assist,Smooth;
} hexPatches;
static bool recoil = false;
static bool magic = false;
static bool assist = false;
static bool smooth = false;
static bool isPlayerBotEnabled = false;




   
void noMore(ImDrawList* draw) {
    if (!sync_bool["bESP"]) return;

    auto all_entities = get_entities();
    std::vector<Entity> valid_entities = all_entities;

    std::sort(valid_entities.begin(), valid_entities.end(),
        [](const Entity& a, const Entity& b) {
            float za = a.bones.count("head") ? a.bones.at("head")[2] : 0.0f;
            float zb = b.bones.count("head") ? b.bones.at("head")[2] : 0.0f;
            return za < zb;
        }
    );

    int max_entities = 20;
    if (valid_entities.size() > max_entities)
        valid_entities.resize(max_entities);

    
  
    int players = 0, bots = 0;
    for (const Entity& e : valid_entities) {
        if (!e.bones.count("head") || !e.bones.count("spine")) continue;
        if (e.is_bot) bots++; else players++;

        ImVec2 From;
        switch (sync_int["iESP_Point"]) {
            case 0: From = ImVec2(Width / 2, Height); break;
            case 1: From = ImVec2(Width / 2, Height / 2); break;
            case 2: From = ImVec2(Width / 2, 0); break;
        }

        if (sync_bool["bESP_Skeleton"]) {
            auto head = ToImVec2(e.bones.at("head"));
            auto spine = ToImVec2(e.bones.at("spine"));
            auto limbs_r_upperarm = ToImVec2(e.bones.at("limbs_r_upperarm"));
            auto limbs_r_forearm = ToImVec2(e.bones.at("limbs_r_forearm"));
            auto limbs_r_hand = ToImVec2(e.bones.at("limbs_r_hand"));
            auto limbs_r_thigh = ToImVec2(e.bones.at("limbs_r_thigh"));
            auto limbs_r_calf = ToImVec2(e.bones.at("limbs_r_calf"));
            auto limbs_r_foot = ToImVec2(e.bones.at("limbs_r_foot"));
            auto limbs_l_upperarm = ToImVec2(e.bones.at("limbs_l_upperarm"));
            auto limbs_l_forearm = ToImVec2(e.bones.at("limbs_l_forearm"));
            auto limbs_l_hand = ToImVec2(e.bones.at("limbs_l_hand"));
            auto limbs_l_thigh = ToImVec2(e.bones.at("limbs_l_thigh"));
            auto limbs_l_calf = ToImVec2(e.bones.at("limbs_l_calf"));
            auto limbs_l_foot = ToImVec2(e.bones.at("limbs_l_foot"));
            auto limbs_r_toe = ToImVec2(e.bones.at("limbs_r_toe"));
            auto limbs_l_toe = ToImVec2(e.bones.at("limbs_l_toe"));
            auto chest = ImVec2((limbs_r_upperarm.x + limbs_l_upperarm.x) / 2, (limbs_r_upperarm.y + limbs_l_upperarm.y) / 2);

            auto linecolor = e.is_visible ? colors["cESP_Skeleton"] : colors["cESP_SkeletonHidden"];
            auto thickness = sync_float["fESP_LineThickness"];

            draw->AddLine(head, chest, linecolor, thickness);
            draw->AddLine(chest, spine, linecolor, thickness);
            draw->AddLine(chest, limbs_r_upperarm, linecolor, thickness);
            draw->AddLine(chest, limbs_l_upperarm, linecolor, thickness);
            draw->AddLine(limbs_r_upperarm, limbs_r_forearm, linecolor, thickness);
            draw->AddLine(limbs_l_upperarm, limbs_l_forearm, linecolor, thickness);
            draw->AddLine(limbs_r_forearm, limbs_r_hand, linecolor, thickness);
            draw->AddLine(limbs_l_forearm, limbs_l_hand, linecolor, thickness);
            draw->AddLine(spine, limbs_l_thigh, linecolor, thickness);
            draw->AddLine(spine, limbs_r_thigh, linecolor, thickness);
            draw->AddLine(limbs_l_thigh, limbs_l_calf, linecolor, thickness);
            draw->AddLine(limbs_r_thigh, limbs_r_calf, linecolor, thickness);
            draw->AddLine(limbs_r_calf, limbs_r_foot, linecolor, thickness);
            draw->AddLine(limbs_l_calf, limbs_l_foot, linecolor, thickness);
            draw->AddLine(limbs_r_foot, limbs_r_toe, linecolor, thickness);
            draw->AddLine(limbs_l_foot, limbs_l_toe, linecolor, thickness);
        }

        ImVec2 To = ToImVec2(e.bones.at("head"));
        if (e.is_bot) {
            if (sync_bool["bESP_LineBots"]) draw->AddLine(From, To, e.is_visible ? colors["cESP_LineBots"] : colors["cESP_LineBotsHidden"], sync_float["fESP_LineThickness"]);
        } else {
            if (sync_bool["bESP_Line"]) draw->AddLine(From, To, e.is_visible ? colors["cESP_Line"] : colors["cESP_LineHidden"], sync_float["fESP_LineThickness"]);
        }

                if ((sync_bool["bESP_TeamID"] || sync_bool["bESP_Name"] ||
     sync_bool["bESP_Distance"] || sync_bool["bESP_Health"]) && !e.bones.empty())
{
    ImVec2 head   = ToImVec2(e.bones.at("head"));
    ImVec2 foot_l = ToImVec2(e.bones.at("limbs_l_calf"));
    ImVec2 foot_r = ToImVec2(e.bones.at("limbs_r_calf"));
    ImVec2 feet   = (foot_l.y > foot_r.y) ? foot_l : foot_r;


ImVec2 l    = ToImVec2(e.bones.at("limbs_l_calf"));
ImVec2 r    = ToImVec2(e.bones.at("limbs_r_calf"));
ImVec2 foot = ImVec2((l.x + r.x) / 2, (l.y + r.y) / 2);

float height = fabsf(foot.y - head.y) * 2.0f;
float width  = height / 2.0f;

ImVec2 topLeft(
    head.x - width / 2,
    head.y - height * 0.2f
);

ImVec2 bottomRight(
    head.x + width / 2,
    topLeft.y + height
);
	
	
    float boxHeight = feet.y - head.y;
    if (boxHeight <= 0) return;

    float boxWidth = boxHeight * 0.55f;
    float boxX = head.x - boxWidth / 2.0f;
    float boxY = head.y;
    float barWidth   = 7.0f;
    float barSpacing = 8.0f;   

    if (sync_bool["bESP_Distance"])
    {
        float distance = 1000.0f / boxHeight;
        if (distance > 300) distance = 300;

        std::string distanceText = std::to_string((int)distance) + "m";
        ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
        draw->AddText(
            ImVec2(feet.x - textSize.x / 2, feet.y + 5.0f),
            IM_COL32(0, 255, 0, 255),
            distanceText.c_str()
        );
    }

if (sync_bool["bESP_Health"])
{
    float healthPerc = (e.max_health > 0.0f)
        ? std::clamp(e.is_health / e.max_health, 0.0f, 1.0f)
        : 0.0f;

    float barH = bottomRight.y - topLeft.y;
    float barX = topLeft.x - barWidth - barSpacing;
    float barY = topLeft.y;

    ImU32 hpColor = e.is_knocked
        ? IM_COL32(255, 0, 0, 255)
        : (healthPerc > 0.5f
            ? IM_COL32(0, 255, 0, 255)
            : IM_COL32(255, 0, 0, 255));

    draw->AddRectFilled(
        {barX, barY},
        {barX + barWidth, barY + barH},
        IM_COL32(0, 0, 0, 180)
    );

    draw->AddRectFilled(
        {barX, barY + barH * (1.0f - healthPerc)},
        {barX + barWidth, barY + barH},
        hpColor
    );
}

if (sync_bool["bESP_Health"])
{
    float armorPerc = (e.max_armor > 0.0f)
        ? std::clamp(e.is_armor / e.max_armor, 0.0f, 1.0f)
        : 0.0f;

    float barH = bottomRight.y - topLeft.y;
    float barX = bottomRight.x + barSpacing;
    float barY = topLeft.y;

    ImU32 armorColor = armorPerc > 0.7f
        ? IM_COL32(255, 255, 0, 255)
        : (armorPerc > 0.3f
            ? IM_COL32(80, 160, 255, 255)
            : IM_COL32(255, 0, 0, 255));

    draw->AddRectFilled(
        {barX, barY},
        {barX + barWidth, barY + barH},
        IM_COL32(0, 0, 0, 180)
    );

    draw->AddRectFilled(
        {barX, barY + barH * (1.0f - armorPerc)},
        {barX + barWidth, barY + barH},
        armorColor
    );
}


    if (sync_bool["bESP_TeamID"] || sync_bool["bESP_Name"])
    {
        std::string text;
        if (sync_bool["bESP_TeamID"]) text += std::to_string(e.team_id);
        if (sync_bool["bESP_TeamID"] && sync_bool["bESP_Name"]) text += " | ";
        if (sync_bool["bESP_Name"]) text += e.entity_name;

        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
        draw->AddText(
            ImVec2(head.x - textSize.x / 2.0f, head.y - textSize.y - 4.0f),
            e.is_knocked ? IM_COL32(255, 0, 0, 255) : IM_COL32(255, 255, 255, 255),
            text.c_str()
        );
    }
}

        if (sync_bool["bESP_Box"])
{
    if (!e.bones.count("limbs_l_calf") || !e.bones.count("limbs_r_calf"))
        continue;

    ImVec2 head = ToImVec2(e.bones.at("head"));
    ImVec2 l = ToImVec2(e.bones.at("limbs_l_calf"));
    ImVec2 r = ToImVec2(e.bones.at("limbs_r_calf"));
    ImVec2 foot = ImVec2((l.x + r.x) / 2, (l.y + r.y) / 2);

    float height = fabsf(foot.y - head.y) * 2.0f;
    float width  = height / 2.0f;

    ImVec2 topLeft(head.x - width / 2, head.y - height * 0.2f);
    ImVec2 bottomRight(head.x + width / 2, topLeft.y + height);

    ImDrawList* fg = ImGui::GetForegroundDrawList();

    ImU32 color = e.is_visible ? colors["cESP_Box"] : colors["cESP_BoxHidden"];
    float thickness = sync_float["fESP_LineThickness"];

    fg->AddRect(
        topLeft,
        bottomRight,
        color,
        0.0f,               
        0,                 
        thickness
    );
}

        if (sync_bool["bESP_DangerCircle"] && e.is_visible < 15.0f) {
            draw->AddCircle(To, 30.0f, IM_COL32(255, 0, 0, 180), 32, 2.0f);
            draw->AddText(ImVec2(To.x - 20, To.y + 25), IM_COL32(255, 0, 0, 255), "DANGER!");
        }
    }

    if (isPlayerBotEnabled) {
        float glWidth  = sync_float["fWidth"];
        int totalPlayers = players, totalBots = bots;
        ImDrawList* fg = ImGui::GetForegroundDrawList();
        if (totalPlayers + totalBots == 0) {
            fg->AddRectFilled({glWidth/2 - 67.5f, 35}, {glWidth/2 + 60, 75}, ImColor(0,0,0,120), 20);
            std::string txt = "CLEAR";
            ImVec2 size = ImGui::CalcTextSize(txt.c_str());
            fg->AddText(NULL, 35, { glWidth/2 - size.x/2 - 6, 35 + (40-size.y)/2 }, ImColor(255,255,255), txt.c_str());
        } else {
            fg->AddRectFilled({glWidth/2 - 69, 35}, {glWidth/2 + 60, 75}, ImColor(0,0,0,120), 20);
            ImVec2 boxPlayerMin = ImVec2(glWidth/2 - 60, 40);
            ImVec2 boxPlayerMax = ImVec2(glWidth/2 - 8, 70);
            ImVec2 boxBotMin    = ImVec2(glWidth/2 + 0, 40);
            ImVec2 boxBotMax    = ImVec2(glWidth/2 + 50, 70);
            fg->AddRectFilled(boxPlayerMin, boxPlayerMax, ImColor(255,0,0,200), 20);
            fg->AddRectFilled(boxBotMin, boxBotMax, ImColor(0,255,0,200), 20);
            std::string P = std::to_string(totalPlayers);
            std::string B = std::to_string(totalBots);
            ImVec2 pSize = ImGui::CalcTextSize(P.c_str());
            ImVec2 bSize = ImGui::CalcTextSize(B.c_str());
            float pCenterX = (boxPlayerMin.x + boxPlayerMax.x) / 2;
            float bCenterX = (boxBotMin.x + boxBotMax.x) / 2;
            float pCenterY = (boxPlayerMin.y + boxPlayerMax.y) / 2 - 2;
            float bCenterY = (boxBotMin.y + boxBotMax.y) / 2 - 2;
            fg->AddText(NULL, 35, { pCenterX - pSize.x/2 - 3, pCenterY - pSize.y/2 }, ImColor(255,255,255), P.c_str());
            fg->AddText(NULL, 35, { bCenterX - bSize.x/2 - 3, bCenterY - bSize.y/2 }, ImColor(255,255,255), B.c_str());
        }
    }

    update_aim_target();

    if (sync_bool["bAIM"] && aim_target_valid && aim_target_visible) {
        draw->AddLine(ImVec2(Width * 0.5f, Height * 0.5f), aim_target_screen, IM_COL32(255, 0, 0, 255), 2.0f);
    }

    if (!sync_bool["bAIM_NoTargetHideFov"] || (players || bots)) {
        if (sync_bool["bAIM_DrawFov"]) {
            draw->AddCircle(ImVec2(Width / 2, Height / 2), sync_float["fAIM_Fov"], IM_COL32(255, 0, 0, 255), 0, sync_float["fESP_LineThickness"]);
        }
    }
}

	
	
	

GLuint my_logo_texture = 0;

void InitLogo() {
    int w, h;
    my_logo_texture = LoadTextureFromArray(Pic_png, Pic_png_len, &w, &h);
}

   void DrawMenu(ImGuiIO &io) {
	   
    bool need_sync = false, tab_changed = false;
	sync_with_py();
    sync_float[xorstr_("fHeight")] = Height;
    sync_float[xorstr_("fWidth")] = Width;

    static bool color_changed = false;
       

static bool isLogin = false;
static bool xxxxx = false;
static std::string err;

if (!isLogin) {
    if (ImGui::Begin(xorstr_("LOGIN PAGE"), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
        ImGui::Text(xorstr_(ICON_FA_USER_SECRET " CONTACT SELLER TO BUY KEY"));
        
        static char s[150] = {0};
        ImGui::InputText(xorstr_("##key"), s, sizeof(s));

        if (ImGui::Button(xorstr_("PASTE"), ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
            auto key = getClipboard();
            strncpy(s, key.c_str(), sizeof(s));
        }

        if (ImGui::Button(xorstr_("LOGIN"), ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
            err = Login(s);
            if (err == "OK" && (bValid && g_Auth == g_Token)) {
                isLogin = true;
                xxxxx = true;  
            }
        }

        if (!err.empty() && err != std::string(xorstr_("OK"))) {
            ImGui::Text(xorstr_("WRONG KEY!!: %s"), err.c_str());
        }

        ImGui::End();
    }
} else {
   
      


ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::SetNextWindowSizeConstraints(ImVec2(820, 0), ImVec2(840, FLT_MAX));

        ImGui::Begin(xorstr_("                          Bloodstrike-1.003.650013-@Yourr name),
             nullptr, window_flags);
{
	


if (ImGui::BeginTabBar(xorstr_("Tab"), ImGuiTabBarFlags_FittingPolicyScroll))
{
	
	
	
	if (ImGui::BeginTabItem(xorstr_("INFORMATION")))
{

        ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "MOD INFORMATION");
        ImGui::Separator();

        ImGui::Text("Mod Name   : 1.003.650013");
        ImGui::Text("Version    : 1.003.650013");
        ImGui::Text("Status     : Undetected");
        ImGui::Text("Build      : Release");
        ImGui::Spacing();

        ImGui::Text("Device     : Android");
        ImGui::Text("Arch       : arm64-v8a");
        ImGui::Text("Android : %d", __ANDROID_API__);
        ImGui::Spacing();

        ImGui::Text("FPS        : %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Screen     : %.0fx%.0f",
            ImGui::GetIO().DisplaySize.x,
            ImGui::GetIO().DisplaySize.y);

        ImGui::Spacing();
        ImGui::Separator();

       
        ImGui::Spacing();
        ImGui::Separator();

        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.2f, 1.0f),
            "Note: Use at your own risk");
    

    ImGui::EndTabItem();
}
	

    if (ImGui::BeginTabItem(xorstr_("VISUAL")))
    {
        ImGui::BeginGroupPanel(xorstr_("DRAW ESP "), ImVec2(0.0f, 0.0f));
        {
            ImGui::Checkbox(xorstr_("Enable "), &sync_bool[xorstr_("bESP")]);
            ImGui::Checkbox(xorstr_("Esp Line"), &sync_bool[xorstr_("bESP_Line")]);
            ImGui::Checkbox(xorstr_("Esp Bot"), &sync_bool[xorstr_("bESP_LineBots")]);
            ImGui::Checkbox(xorstr_("Esp Box"), &sync_bool[xorstr_("bESP_Box")]);         ImGui::Spacing();
        }
        ImGui::EndGroupPanel();

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            ImGui::BeginGroupPanel(xorstr_("MORE ESP"), ImVec2(-1.0f, 0.0f));
            {
                ImGui::Checkbox(xorstr_("Esp Name"), &sync_bool[xorstr_("bESP_Name")]);
                ImGui::Checkbox(xorstr_("Esp Health"), &sync_bool[xorstr_("bESP_Health")]);
                ImGui::Checkbox(xorstr_("Esp Skeleton"), &sync_bool[xorstr_("bESP_Skeleton")]);       ImGui::Spacing();
            }
            ImGui::EndGroupPanel();

            ImGui::BeginGroupPanel(xorstr_("ESP II"), ImVec2(-1.0f, 0.0f));
            {
                ImGui::Checkbox(xorstr_("Esp Count"), &isPlayerBotEnabled);
                ImGui::Checkbox(xorstr_("Esp Distance"), &sync_bool[xorstr_("bESP_Distance")]);  ImGui::Spacing();
            }
            ImGui::EndGroupPanel();
        }
        ImGui::EndGroup();

        ImGui::BeginGroupPanel(xorstr_("SETTING ESP:"), ImVec2(-1.0f, 0.0f));
        {
            need_sync |= ImGui::Combo(xorstr_("Line Position"), &sync_int[xorstr_("iESP_Point")], espPoint, IM_ARRAYSIZE(espPoint));
            need_sync |= ImGui::SliderFloat(xorstr_("Size Line"), &sync_float[xorstr_("fESP_LineThickness")], 1.0f, 10.0f, xorstr_("%.2f"));
            ImGui::Spacing();
        }
        ImGui::EndGroupPanel();

        ImGui::EndTabItem();
    }


    if (ImGui::BeginTabItem(xorstr_("AIMBOT")))
    {
        ImGui::BeginGroupPanel(xorstr_("AIMBOT MEMORY "), ImVec2(0.0f, 0.0f));
        {
            ImGui::Checkbox(xorstr_("Enable Aimbot"), &sync_bool[xorstr_("bAIM")]);
            ImGui::Checkbox(xorstr_("Check Visibility"), &sync_bool[xorstr_("bAIM_CheckVisibility")]);
            ImGui::Checkbox(xorstr_("Knocked"), &sync_bool[xorstr_("bAIM_IgnoreKnocked")]);
            ImGui::Checkbox(xorstr_("Bot"), &sync_bool[xorstr_("bAIM_IgnoreBots")]);     ImGui::Spacing();
        }
        ImGui::EndGroupPanel();

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            ImGui::BeginGroupPanel(xorstr_("BULLET TRACK"), ImVec2(-1.0f, 0.0f));
            {
                ImGui::Checkbox(xorstr_("Enable Bt"), &sync_bool[xorstr_("bBulletTrack")]);
                ImGui::Checkbox(xorstr_("Ignore Knock"), &sync_bool[xorstr_("bBulletTrack_IgnoreKnocked")]);
                ImGui::Spacing();
            }
            ImGui::EndGroupPanel();

            ImGui::BeginGroupPanel(xorstr_("FOV MENU"), ImVec2(-1.0f, 0.0f));
            {
                ImGui::Checkbox(xorstr_("Enable Fov"), &sync_bool[xorstr_("bAIM_DrawFov")]);
                ImGui::Checkbox(xorstr_("Hide Fov"), &sync_bool[xorstr_("bAIM_NoTargetHideFov")]);
                ImGui::Spacing();
            }
            ImGui::EndGroupPanel();
        }
        ImGui::EndGroup();

        ImGui::BeginGroupPanel(xorstr_("SETTING AIM:"), ImVec2(-1.0f, 0.0f));
        {
            need_sync |= ImGui::Combo(xorstr_("Trigger"), &sync_int[xorstr_("iAIM_Trigger")], aimbotTrigger, IM_ARRAYSIZE(aimbotTrigger));
            need_sync |= ImGui::Combo(xorstr_("Target"), &sync_int[xorstr_("iAIM_TargetBone")], targetBone, IM_ARRAYSIZE(targetBone));
            need_sync |= ImGui::SliderFloat(xorstr_("Strenght"), &sync_float[xorstr_("fAIM_SnapStrength")], 0.001f, 3.0f, xorstr_("%.2f"));
            need_sync |= ImGui::SliderFloat(xorstr_("Fov"), &sync_float[xorstr_("fAIM_Fov")], 30.0f, 1500.0f, xorstr_("%.2f"));
            need_sync |= ImGui::SliderFloat(xorstr_("Probality"), &sync_float[xorstr_("fBulletTrack_Probability")], 30.0f, 100.0f, xorstr_("%.2f"));   }
        ImGui::EndGroupPanel();

        
        ImGui::EndTabItem();
    }

	
	if (ImGui::BeginTabItem(xorstr_("MEMORY"))) {
    ImGui::BeginGroupPanel(xorstr_("MEMORY HACK"), ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox(xorstr_("Red Wallhack"), &sync_bool[xorstr_("bXray")]);
        ImGui::Checkbox(xorstr_("Speed Hack"), &sync_bool[xorstr_("bSpeed")]);
        ImGui::Checkbox(xorstr_("Skin Hack"), &sync_bool[xorstr_("bSkinHack")]);    ImGui::Spacing();
    }
    ImGui::EndGroupPanel();

    ImGui::SameLine();

    ImGui::BeginGroup();
    {
        ImGui::BeginGroupPanel(xorstr_("AIM HACK"), ImVec2(-1.0f, 0.0f));
        {
            ImGui::Checkbox(xorstr_("No Recoil"), &sync_bool[xorstr_("bNoRecoil")]);
            ImGui::Checkbox(xorstr_("No Spread"), &sync_bool[xorstr_("bNoSpread")]);
            ImGui::Checkbox(xorstr_("No Shake"), &sync_bool[xorstr_("bSwitch")]);          ImGui::Spacing();
        }
        ImGui::EndGroupPanel();
    }
    ImGui::EndGroup();

    ImGui::BeginGroupPanel(xorstr_("Speed Hack"), ImVec2(-1.0f, 0.0f));
    {
        need_sync |= ImGui::SliderFloat(xorstr_("Speed"), &sync_float[xorstr_("fSpeed")], 1.0f, 15.0f, xorstr_("%.2f"));
        ImGui::Spacing();
    }
    ImGui::EndGroupPanel();

    ImGui::EndTabItem();
}
ImGui::EndTabBar();
    }

    ImGui::End();
}
}
}


static bool setup = false;

DEFINES(EGLBoolean, Draw, EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &Width);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &Height);

    if (Width <= 0 || Height <= 0)
        return _Draw(dpy, surface);

    if (!setup) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = NULL;

        static const ImWchar icons_ranges[] = {0xf000, 0xf3ff, 0};
    ImFontConfig icons_config;
    static const ImWchar ranges[] = {
        0x0020,
        0x00FF, // Basic Latin + Latin Supplement
        0x0400,
        0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0,
        0x2DFF, // Cyrillic Extended-A
        0xA640,
        0xA69F, // Cyrillic Extended-B
        0xE000,
        0xE226, // icons
        0,
    };
    ImFontConfig font_config;
    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2.5;
    icons_config.OversampleV = 2.5;
    ImFontConfig cfg;
    cfg.FontBuilderFlags = 0;

    io.Fonts->AddFontFromMemoryTTF(
        (void *)SabFont,
        (int)SabFont_size,
        30.f,
        &font_config,
        io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromMemoryTTF(
        fa_solid_900_ttf,
        fa_solid_900_ttf_len,
        24.0f,
        &icons_config,
        icons_ranges);
    flamee = io.Fonts->AddFontFromMemoryTTF((void *)Yaser_data, Mod_size, 28.0f, &icons_config, io.Fonts->GetGlyphRangesCyrillic());
    Japan = io.Fonts->AddFontFromMemoryTTF((void *)Darmen_data, Darmen_size, 28.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

    ubu_0 = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(ubuntu_0), ubuntu_0_size, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());
    pubg_font = io.Fonts->AddFontFromMemoryTTF((void *)default_f, sizeof default_f, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_general_bold = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(lexend_bold), lexend_bold_size, 28.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_bold = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(lexend_regular), lexend_regular_size, 28.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_regular = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(lexend_regular), lexend_regular_size, 28.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(icomoon), icomoon_size, 30.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_tabs = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(icomoon), icomoon_size, 35.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_widget = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(icomoon_widget), icomoon_widget_size, 35.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_widget2 = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char *>(icomoon), icomoon_size, 35.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());	
        ImGui_ImplOpenGL3_Init("#version 300 es");
        ImGui::StyleColorsDark();

        static ImVec4 clear_color = ImVec4(0, 0, 0, 0);

ImGuiStyle &style = ImGui::GetStyle();
style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
style.Colors[ImGuiCol_TitleBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
style.Colors[ImGuiCol_TitleBgActive]    = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
style.Colors[ImGuiCol_Header]        = ImVec4(0.45f, 0.80f, 0.55f, 0.80f);
style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.85f, 0.55f, 0.85f);
style.Colors[ImGuiCol_HeaderActive]  = ImVec4(0.35f, 0.90f, 0.55f, 1.00f);
style.Colors[ImGuiCol_Button]        = ImVec4(0.35f, 0.85f, 0.55f, 0.80f);
style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.85f, 0.55f, 0.85f);
style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.35f, 0.85f, 0.55f, 1.00f);
style.Colors[ImGuiCol_Tab]        = ImVec4(0.20f, 0.60f, 1.00f, 0.70f);
style.Colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.60f, 1.00f, 0.85f);
style.Colors[ImGuiCol_TabActive]  = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);
style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);
style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);
style.Colors[ImGuiCol_SliderGrab]       = ImVec4(0.35f, 0.85f, 0.55f, 1.00f);
style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.85f, 0.55f, 1.00f);
style.Colors[ImGuiCol_CheckMark]        = ImVec4(0.35f, 0.85f, 0.55f, 1.00f);
style.Colors[ImGuiCol_Text]         = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 0.0f, 0.2f);
style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.f, 0.f, 0.f, 0.f);

style.WindowRounding = 8.0f;
    style.FrameRounding = 10.0f;
    style.GrabRounding = 10.0f;


	
        style.ScaleAllSizes(3.0f);

        setup = true;
    }
	
	

    // render setiap frame
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = (float)Width;
    io.DisplaySize.y = (float)Height;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(Width, Height);
    NewFrame();
    ClearImGuiWindowTracking();
    auto draw = GetBackgroundDrawList();
    noMore(draw);
    DrawMenu(io);
    EndFrame();
    Render();
    glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return _Draw(dpy, surface);
}



