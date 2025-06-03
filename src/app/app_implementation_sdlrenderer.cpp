#include "app/app_implementation_sdlrenderer.hpp"
#include "image/image.hpp"
#include "image/image_sdlrenderer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include "image/image_resource.hpp"

AppImplementationSDLRenderer::AppImplementationSDLRenderer(std::string name, int width, int height):
    IAppImplementation(name, width, height)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        exit(-1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error: %s\n", IMG_GetError());
        exit(-1);
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(-1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        exit(-1);
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);
}

AppImplementationSDLRenderer::~AppImplementationSDLRenderer() {
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void AppImplementationSDLRenderer::setup() {}

void AppImplementationSDLRenderer::update() {
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
        SDL_Delay(10);
        return;
    }
}

void AppImplementationSDLRenderer::create_frame() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void AppImplementationSDLRenderer::clear_renderer() {
    ImGuiIO& io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    static ImVec4 clear_color = ImVec4(0.129412f, 0.345098f, 0.345098f, 1.00f);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);
}

void AppImplementationSDLRenderer::render() {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

void AppImplementationSDLRenderer::draw_rect(int x, int y, int width, int height, int r, int g, int b, int a, bool fill) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect;
    if (fill) {
        rect = { x, y, width, height };
        SDL_RenderFillRect(renderer, &rect);
        return;
    } else {
        rect = { x, y+1, 1, height-2 };
        SDL_RenderDrawRect(renderer, &rect);
        rect = { x+width, y+1, 1, height-2 };
        SDL_RenderDrawRect(renderer, &rect);
        rect = { x, y, width, 1 };
        SDL_RenderDrawRect(renderer, &rect);
        rect = { x, y+height, width, 1 };
        SDL_RenderDrawRect(renderer, &rect);
    }
}

std::shared_ptr<Image> AppImplementationSDLRenderer::load_image(const std::string& file_path) {
    SDL_Surface* temp_surface = IMG_Load(file_path.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image: " << file_path << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (!texture) {
        std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(temp_surface);
    std::shared_ptr<Image> image = std::make_shared<ImageSDLRenderer>(texture);

    return image;
}

void AppImplementationSDLRenderer::draw_image(const std::string& image_id, int x, int y, float scale_x, float scale_y, bool flip_x, bool flip_y, int src_x, int src_y, int src_w, int src_h) {
    auto& image_resource = ImageResource::get_instance();
    auto image = image_resource.get_image(image_id);
    if (!image) {
        return;
    }
    auto texture = static_cast<SDL_Texture*>(image->get_native_image());

    if (src_w == 0 || src_h == 0) {
        int img_w, img_h;
        SDL_QueryTexture(texture, nullptr, nullptr, &img_w, &img_h);

        if (src_w == 0) { src_w = img_w; }
        if (src_h == 0) { src_h = img_h; }
    }

    SDL_Rect src_rect = {src_x, src_y, src_w, src_h};

    int dst_w = src_w*scale_x;
    int dst_h = src_h*scale_y;
    SDL_Rect dest_rect = {x, y, dst_w, dst_h};

    SDL_RendererFlip flip_flags = static_cast<SDL_RendererFlip>((SDL_FLIP_HORIZONTAL*flip_x) | (SDL_FLIP_VERTICAL*flip_y));

    if (SDL_RenderCopyEx(renderer, texture, &src_rect, &dest_rect, 0.0, nullptr, flip_flags) != 0) {
        std::cerr << "Failed to render texture: " << SDL_GetError() << std::endl;
    }
}

void AppImplementationSDLRenderer::draw_imgui_image(const std::string& image_id, int width, int height) {
    auto& image_resource = ImageResource::get_instance();
    auto image = image_resource.get_image(image_id);
    if (!image) {
        return;
    }
    auto texture = static_cast<SDL_Texture*>(image->get_native_image());
    int image_width, image_height;
    SDL_QueryTexture(texture, nullptr, nullptr, &image_width, &image_height);
    ImTextureID textureID = reinterpret_cast<ImTextureID>(texture);
    ImVec2 size(width, height);
    if (size.x == 0) size.x = image_width;
    if (size.y == 0) size.y = image_height;
    ImGui::Image(textureID, size);
}
