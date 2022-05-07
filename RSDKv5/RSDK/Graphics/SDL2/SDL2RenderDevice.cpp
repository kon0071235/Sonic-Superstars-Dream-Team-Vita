SDL_Window *RenderDevice::window     = nullptr;
SDL_Renderer *RenderDevice::renderer = nullptr;
SDL_Texture *RenderDevice::screenTexture[SCREEN_MAX];

SDL_Texture *RenderDevice::imageTexture = nullptr;

uint32 RenderDevice::displayModeIndex = 0;
int32 RenderDevice::displayModeCount  = 0;

unsigned long long RenderDevice::targetFreq = 0;
unsigned long long RenderDevice::curTicks   = 0;
unsigned long long RenderDevice::prevTicks  = 0;


bool RenderDevice::Init()
{

    const char *gameTitle = RSDK::gameVerInfo.gameName;

    SDL_Init(SDL_INIT_EVERYTHING);

    byte flags = 0;

#if RETRO_PLATFORM == RETRO_ANDROID || RETRO_PLATFORM == RETRO_SWITCH
    RSDK::gameSettings.windowed = false;
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    float hdp = 0, vdp = 0;

    bool landscape = dm.h < dm.w;
    int h          = landscape ? dm.w : dm.h;
    int w          = landscape ? dm.h : dm.w;

    RSDK::gameSettings.windowWidth = pixWidth = ((float)SCREEN_YSIZE * h / w);
#endif

#if RETRO_PLATFORM == RETRO_SWITCH
    RSDK::gameSettings.windowWidth  = 1920;
    RSDK::gameSettings.windowHeight = 1080;
    flags |= SDL_WINDOW_FULLSCREEN;
#endif

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, RSDK::gameSettings.vsync ? "1" : "0");

    window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RSDK::gameSettings.windowWidth,
                              RSDK::gameSettings.windowHeight, SDL_WINDOW_ALLOW_HIGHDPI | flags);

    if (!window) {
        PrintLog(PRINT_NORMAL, "ERROR: failed to create window!");
        return false;
    }

    if (!RSDK::gameSettings.windowed) {
        SDL_RestoreWindow(window);
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_ShowCursor(SDL_FALSE);
    }

    if (!RSDK::gameSettings.bordered) {
        SDL_RestoreWindow(window);
        SDL_SetWindowBordered(window, SDL_FALSE);
    }

    PrintLog(PRINT_NORMAL, "w: %d h: %d windowed: %d\n", RSDK::gameSettings.windowWidth, RSDK::gameSettings.windowHeight,
             RSDK::gameSettings.windowed);

    if (!SetupRendering() || !InitAudioDevice())
        return false;

    InitInputDevices();
    return true;
}

void RenderDevice::CopyFrameBuffer()
{
    int32 pitch    = 0;
    uint16 *pixels = NULL;

    for (int32 s = 0; s < RSDK::gameSettings.screenCount; ++s) {
        SDL_LockTexture(screenTexture[s], NULL, (void **)&pixels, &pitch);

        uint16 *frameBufferPtr = screens[s].frameBuffer;
        for (int32 y = 0; y < SCREEN_YSIZE; ++y) {
            memcpy(pixels, frameBufferPtr, screens[s].size.x * sizeof(uint16));
            frameBufferPtr += screens[s].pitch;
            pixels += pitch / sizeof(uint16);
        }

        SDL_UnlockTexture(screenTexture[s]);
    }
}

void RenderDevice::FlipScreen()
{
    if (RSDK::gameSettings.dimTimer < RSDK::gameSettings.dimLimit) {
        if (RSDK::gameSettings.dimPercent < 1.0) {
            RSDK::gameSettings.dimPercent += 0.05;
            if (RSDK::gameSettings.dimPercent > 1.0)
                RSDK::gameSettings.dimPercent = 1.0;
        }
    }
    else if (RSDK::gameSettings.dimPercent > 0.25) {
        RSDK::gameSettings.dimPercent *= 0.9;
    }

    if (windowRefreshDelay > 0) {
        windowRefreshDelay--;
        if (!windowRefreshDelay)
            UpdateGameWindow();
        return;
    }

    float dimAmount = RSDK::gameSettings.dimMax * RSDK::gameSettings.dimPercent;

    // Clear the screen. This is needed to keep the
    // pillarboxes in fullscreen from displaying garbage data.
    SDL_RenderClear(renderer);

    int32 startVert = 0;
    switch (RSDK::gameSettings.screenCount) {
        default:
        case 0:
#if RETRO_REV02
            startVert = 54;
#else
            startVert = 18;
#endif
            SDL_RenderGeometryRaw(renderer, imageTexture, &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);
            break;

        case 1:
            startVert = 0;
            SDL_RenderGeometryRaw(renderer, screenTexture[0], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);
            break;

        case 2:
#if RETRO_REV02
            startVert = startVertex_2P[0];
#else
            startVert = 6;
#endif
            SDL_RenderGeometryRaw(renderer, screenTexture[0], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

#if RETRO_REV02
            startVert = startVertex_2P[1];
#else
            startVert = 12;
#endif
            SDL_RenderGeometryRaw(renderer, screenTexture[1], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);
            break;

#if RETRO_REV02
        case 3:
            startVert = startVertex_3P[0];
            SDL_RenderGeometryRaw(renderer, screenTexture[0], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

            startVert = startVertex_3P[1];
            SDL_RenderGeometryRaw(renderer, screenTexture[1], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

            startVert = startVertex_3P[2];
            SDL_RenderGeometryRaw(renderer, screenTexture[2], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);
            break;

        case 4:
            startVert = 30;
            SDL_RenderGeometryRaw(renderer, screenTexture[0], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

            startVert = 36;
            SDL_RenderGeometryRaw(renderer, screenTexture[1], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

            startVert = 42;
            SDL_RenderGeometryRaw(renderer, screenTexture[2], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);

            startVert = 48;
            SDL_RenderGeometryRaw(renderer, screenTexture[3], &vertexBuffer[startVert].pos.x, sizeof(RenderVertex),
                                  (SDL_Color *)&vertexBuffer[startVert].color, sizeof(RenderVertex), &vertexBuffer[startVert].tex.x,
                                  sizeof(RenderVertex), 6, NULL, 0, 0);
            break;
#endif
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF - (dimAmount * 0xFF));
    if (dimAmount < 1.0)
        SDL_RenderFillRect(renderer, NULL);
    // no change here
    SDL_RenderPresent(renderer);
}

void RenderDevice::Release(bool32 isRefresh)
{

    for (int32 s = 0; s < SCREEN_MAX; ++s) {
        if (screenTexture[s])
            SDL_DestroyTexture(screenTexture[s]);
        screenTexture[s] = NULL;
    }

    if (imageTexture)
        SDL_DestroyTexture(imageTexture);
    imageTexture = NULL;

    if (!isRefresh && renderer)
        SDL_DestroyRenderer(renderer);

    if (!isRefresh && window)
        SDL_DestroyWindow(window);

    if (!isRefresh)
        SDL_Quit();

    if (!isRefresh) {
        if (scanlines)
            free(scanlines);
        scanlines = NULL;
    }
}

void RenderDevice::RefreshWindow()
{
    RSDK::gameSettings.windowState = WINDOWSTATE_UNINITIALIZED;

    RenderDevice::Release(true);

    SDL_HideWindow(RenderDevice::window);

    if (RSDK::gameSettings.windowed && RSDK::gameSettings.bordered)
        SDL_SetWindowBordered(window, SDL_TRUE);
    else
        SDL_SetWindowBordered(window, SDL_FALSE);

    GetDisplays();

    SDL_Rect winRect;
    winRect.x = SDL_WINDOWPOS_CENTERED;
    winRect.y = SDL_WINDOWPOS_CENTERED;
    if (RSDK::gameSettings.windowed || !RSDK::gameSettings.exclusiveFS) {
        int32 currentWindowDisplay = SDL_GetWindowDisplayIndex(window);
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(currentWindowDisplay, &displayMode);

        if (RSDK::gameSettings.windowed) {
            if (RSDK::gameSettings.windowWidth >= displayMode.w || RSDK::gameSettings.windowHeight >= displayMode.h) {
                RSDK::gameSettings.windowWidth  = (displayMode.h / 480 * RSDK::gameSettings.pixWidth);
                RSDK::gameSettings.windowHeight = displayMode.h / 480 * RSDK::gameSettings.pixHeight;
            }

            winRect.w = RSDK::gameSettings.windowWidth;
            winRect.h = RSDK::gameSettings.windowHeight;
            SDL_SetWindowFullscreen(window, SDL_FALSE);
            SDL_ShowCursor(SDL_FALSE);
        }
        else {
            winRect.w = displayMode.w;
            winRect.h = displayMode.h;
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_ShowCursor(SDL_TRUE);
        }

        SDL_SetWindowSize(RenderDevice::window, winRect.w, winRect.h);
        SDL_SetWindowPosition(RenderDevice::window, winRect.x, winRect.y);
    }

    SDL_ShowWindow(RenderDevice::window);

    if (!InitGraphicsAPI() || !InitShaders())
        return;

    RSDK::gameSettings.windowState = WINDOWSTATE_ACTIVE;
}

void RenderDevice::InitFPSCap()
{
    targetFreq = SDL_GetPerformanceFrequency() / RSDK::gameSettings.refreshRate;
    curTicks   = 0;
    prevTicks  = 0;
}
bool RenderDevice::CheckFPSCap()
{
    curTicks = SDL_GetPerformanceCounter();
    if (curTicks >= prevTicks + targetFreq)
        return true;

    return false;
}
void RenderDevice::UpdateFPSCap()
{
    prevTicks = curTicks;
}

void RenderDevice::InitVertexBuffer()
{
    //TODO: can we share this amongst the renderdevices
// clang-format off
#if RETRO_REV02
RenderVertex vertBuffer[60] = {
    // 1 Screen (0)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 2 Screens - Bordered (Top Screen) (6)
    { { -0.5,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -0.5,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.5,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 2 Screens - Bordered (Bottom Screen) (12)
    { { -0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -0.5, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  0.5, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.5,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  0.5, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 2 Screens - Stretched (Top Screen)  (18)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 2 Screens - Stretched (Bottom Screen) (24)
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 4 Screens (Top-Left) (30)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 4 Screens (Top-Right) (36)
    { {  0.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { {  0.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 4 Screens (Bottom-Right) (48)
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  0.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  0.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // 4 Screens (Bottom-Left) (42)
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  0.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { {  0.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    
    // Image/Video (54)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  1.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  1.0 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  1.0 } }
};
#else
RenderVertex vertexList[24] =
{
    // 1 Screen (0)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },

  // 2 Screens - Stretched (Top Screen) (6)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
  
  // 2 Screens - Stretched (Bottom Screen) (12)
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.9375 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
    { { -1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  0.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.625,  0.9375 } },
  
    // Image/Video (18)
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { { -1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  1.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  1.0 } },
    { { -1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  0.0,  0.0 } },
    { {  1.0,  1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  0.0 } },
    { {  1.0, -1.0,  1.0 }, 0xFFFFFFFF, {  1.0,  1.0 } }
};
#endif
    // clang-format on

    for (int v = 0; v < (!RETRO_REV02 ? 24 : 60); ++v) {
        RenderVertex *vertex = &vertBuffer[v];
        vertex->pos.x        = NORMALIZE(vertex->pos.x, -1.0, 1.0) * RSDK::gameSettings.pixWidth;
        vertex->pos.y        = (1.0 - NORMALIZE(vertex->pos.y, -1.0, 1.0)) * SCREEN_YSIZE;

        if (vertex->tex.x)
            vertex->tex.x = screens[0].size.x * (1.0 / textureSize.x);

        if (vertex->tex.y)
            vertex->tex.y = screens[0].size.y * (1.0 / textureSize.y);
    }

    memcpy(vertexBuffer, vertBuffer, sizeof(vertBuffer));
}

bool RenderDevice::InitGraphicsAPI()
{
    RSDK::gameSettings.shaderSupport = false;

    viewSize.x = 0;
    viewSize.y = 0;

    if (RSDK::gameSettings.windowed || !RSDK::gameSettings.exclusiveFS) {
        if (RSDK::gameSettings.windowed) {
            viewSize.x = RSDK::gameSettings.windowWidth;
            viewSize.y = RSDK::gameSettings.windowHeight;
        }
        else {
            viewSize.x = displayWidth[displayModeIndex];
            viewSize.y = displayHeight[displayModeIndex];
        }
    }
    else {
        int32 bufferWidth  = RSDK::gameSettings.fsWidth;
        int32 bufferHeight = RSDK::gameSettings.fsWidth;
        if (RSDK::gameSettings.fsWidth <= 0 || RSDK::gameSettings.fsHeight <= 0) {
            bufferWidth  = displayWidth[displayModeIndex];
            bufferHeight = displayHeight[displayModeIndex];
        }

        viewSize.x = bufferWidth;
        viewSize.y = bufferHeight;
    }

    SDL_SetWindowSize(RenderDevice::window, viewSize.x, viewSize.y);
    SDL_SetWindowPosition(RenderDevice::window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    int32 maxPixHeight = 0;
    for (int32 s = 0; s < 4; ++s) {
        if (RSDK::gameSettings.pixHeight > maxPixHeight)
            maxPixHeight = RSDK::gameSettings.pixHeight;

        screens[s].size.y = RSDK::gameSettings.pixHeight;

        float viewAspect  = viewSize.x / viewSize.y;
        int32 screenWidth = (int)((viewAspect * RSDK::gameSettings.pixHeight) + 3) & 0xFFFFFFFC;
        if (screenWidth < RSDK::gameSettings.pixWidth)
            screenWidth = RSDK::gameSettings.pixWidth;

        // if (screenWidth > 424)
        //     screenWidth = 424;

        memset(&screens[s].frameBuffer, 0, sizeof(screens[s].frameBuffer));
        SetScreenSize(s, screenWidth, screens[s].size.y);
    }

    pixelSize.x     = screens[0].size.x;
    pixelSize.y     = screens[0].size.y;
    float pixAspect = pixelSize.x / pixelSize.y;

    SDL_RenderSetLogicalSize(renderer, RSDK::gameSettings.pixWidth, SCREEN_YSIZE);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (maxPixHeight <= 256) {
        textureSize.x = 512.0;
        textureSize.y = 256.0;
    }
    else {
        textureSize.x = 1024.0;
        textureSize.y = 512.0;
    }

    for (int32 s = 0; s < SCREEN_MAX; ++s) {
        screenTexture[s] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, textureSize.x, textureSize.y);

        if (!screenTexture[s]) {
            PrintLog(PRINT_NORMAL, "ERROR: failed to create screen buffer!\nerror msg: %s", SDL_GetError());
            return 0;
        }
    }

    imageTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1024, 512);
    if (!imageTexture)
        return false;

    lastShaderID = -1;
    InitVertexBuffer();
    RSDK::gameSettings.viewportX = 0;
    RSDK::gameSettings.viewportY = 0;
    RSDK::gameSettings.viewportW = 1.0 / viewSize.x;
    RSDK::gameSettings.viewportH = 1.0 / viewSize.y;

    return true;
}

void RenderDevice::LoadShader(const char *fileName, bool32 linear)
{
    char buffer[0x100];
    FileInfo info;

    for (int i = 0; i < shaderCount; ++i) {
        if (strcmp(shaderList[i].name, fileName) == 0)
            return;
    }

    if (shaderCount == SHADER_MAX)
        return;

    ShaderEntry *shader = &shaderList[shaderCount];
    shader->linear      = linear;
    sprintf(shader->name, "%s", fileName);

    const char *shaderFolder    = "Dummy"; // nothing should ever be in "Data/Shaders/Dummy" so it works out to never load anything
    const char *vertexShaderExt = "txt";
    const char *pixelShaderExt  = "txt";

    const char *bytecodeFolder    = "CSO-Dummy"; // nothing should ever be in "Data/Shaders/CSO-Dummy" so it works out to never load anything
    const char *vertexBytecodeExt = "bin";
    const char *pixelBytecodeExt  = "bin";


#if !RETRO_USE_ORIGINAL_CODE
    sprintf(buffer, "Data/Shaders/%s/%s.%s", shaderFolder, fileName, vertexShaderExt);
    InitFileInfo(&info);
    if (LoadFile(&info, buffer, FMODE_RB)) {
        byte *fileData = NULL;
        RSDK::AllocateStorage(info.fileSize, (void **)&fileData, RSDK::DATASET_TMP, false);
        ReadBytes(&info, fileData, info.fileSize);
        CloseFile(&info);

        fileData = NULL;
    }
    else {
#endif

        sprintf(buffer, "Data/Shaders/%s/%s.%s", bytecodeFolder, fileName, vertexBytecodeExt);
        InitFileInfo(&info);
        if (LoadFile(&info, buffer, FMODE_RB)) {
            byte *fileData = NULL;
            RSDK::AllocateStorage(info.fileSize, (void **)&fileData, RSDK::DATASET_TMP, false);
            ReadBytes(&info, fileData, info.fileSize);
            CloseFile(&info);

            fileData = NULL;
        }

#if !RETRO_USE_ORIGINAL_CODE
    }
#endif

#if !RETRO_USE_ORIGINAL_CODE
    sprintf(buffer, "Data/Shaders/%s/%s.%s", shaderFolder, fileName, pixelShaderExt);
    InitFileInfo(&info);
    if (LoadFile(&info, buffer, FMODE_RB)) {
        byte *fileData = NULL;
        RSDK::AllocateStorage(info.fileSize, (void **)&fileData, RSDK::DATASET_TMP, false);
        ReadBytes(&info, fileData, info.fileSize);
        CloseFile(&info);

        fileData = NULL;
    }
    else {
#endif
        sprintf(buffer, "Data/Shaders/%s/%s.%s", bytecodeFolder, fileName, pixelBytecodeExt);
        InitFileInfo(&info);
        if (LoadFile(&info, buffer, FMODE_RB)) {
            byte *fileData = NULL;
            RSDK::AllocateStorage(info.fileSize, (void **)&fileData, RSDK::DATASET_TMP, false);
            ReadBytes(&info, fileData, info.fileSize);
            CloseFile(&info);

            fileData = NULL;
        }

#if !RETRO_USE_ORIGINAL_CODE
    }
#endif

    shaderCount++;
}

bool RenderDevice::InitShaders()
{
    int32 maxShaders = 0;
    if (RSDK::gameSettings.shaderSupport) {
        LoadShader("None", false);
        LoadShader("Clean", true);
        LoadShader("CRT-Yeetron", true);
        LoadShader("CRT-Yee64", true);

#if RETRO_USE_MOD_LOADER
        // a place for mods to load custom shaders
        RSDK::RunModCallbacks(RSDK::MODCB_ONSHADERLOAD, NULL);
        userShaderCount = shaderCount;
#endif

        LoadShader("YUV-420", true);
        LoadShader("YUV-422", true);
        LoadShader("YUV-444", true);
        LoadShader("RGB-Image", true);
        maxShaders = shaderCount;
    }
    else {
        for (int s = 0; s < SHADER_MAX; ++s) shaderList[s].linear = true;

        shaderList[0].linear = RSDK::gameSettings.windowed ? false : shaderList[0].linear;
        maxShaders           = 1;
        shaderCount          = 1;
    }

    RSDK::gameSettings.shaderID = RSDK::gameSettings.shaderID >= maxShaders ? 0 : RSDK::gameSettings.shaderID;

    return true;
}

bool RenderDevice::SetupRendering()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        PrintLog(PRINT_NORMAL, "ERROR: failed to create renderer!");
        return false;
    }

    RenderDevice::GetDisplays();

    if (!InitGraphicsAPI() || !InitShaders())
        return false;

    int size  = RSDK::gameSettings.pixWidth >= SCREEN_YSIZE ? RSDK::gameSettings.pixWidth : SCREEN_YSIZE;
    scanlines = (ScanlineInfo *)malloc(size * sizeof(ScanlineInfo));
    memset(scanlines, 0, size * sizeof(ScanlineInfo));

    RSDK::gameSettings.windowState = WINDOWSTATE_ACTIVE;
    RSDK::gameSettings.dimMax      = 1.0;
    RSDK::gameSettings.dimPercent  = 1.0;

    return true;
}

void RenderDevice::GetDisplays()
{
    int currentWindowDisplay = SDL_GetWindowDisplayIndex(window);

    int dispCount = SDL_GetNumVideoDisplays();

    uint32 prevDisplayMode = displayModeIndex;

    SDL_DisplayMode currentDisplay;
    SDL_GetCurrentDisplayMode(currentWindowDisplay, &currentDisplay);

    displayModeIndex = 0;
    for (int a = 0; a < dispCount; ++a) {
        SDL_DisplayMode displayMode;

        SDL_GetCurrentDisplayMode(currentWindowDisplay, &displayMode);
        displayWidth[a]  = displayMode.w;
        displayHeight[a] = displayMode.h;

        if (memcmp(&currentDisplay, &displayMode, sizeof(displayMode)) == 0) {
            displayModeIndex = a;
        }
    }

    displayCount = SDL_GetNumDisplayModes(currentWindowDisplay);
    if (displayInfo.displays)
        free(displayInfo.displays);

    displayInfo.displays        = (decltype(displayInfo.displays))malloc(sizeof(SDL_DisplayMode) * displayCount);
    int newDisplayCount         = 0;
    bool foundFullScreenDisplay = false;

    for (int d = 0; d < displayCount; ++d) {
        SDL_GetDisplayMode(currentWindowDisplay, d, &displayInfo.displays[newDisplayCount].internal);

        int refreshRate = displayInfo.displays[newDisplayCount].refresh_rate;
        if (refreshRate >= 59 && (refreshRate <= 60 || refreshRate >= 120) && displayInfo.displays[newDisplayCount].height >= (SCREEN_YSIZE * 2)) {
            if (d && refreshRate == 60 && displayInfo.displays[newDisplayCount - 1].refresh_rate == 59)
                --newDisplayCount;

            if (RSDK::gameSettings.fsWidth == displayInfo.displays[newDisplayCount].width
                && RSDK::gameSettings.fsHeight == displayInfo.displays[newDisplayCount].height)
                foundFullScreenDisplay = true;

            ++newDisplayCount;
        }
    }

    displayCount = newDisplayCount;
    if (!foundFullScreenDisplay) {
        RSDK::gameSettings.fsWidth     = 0;
        RSDK::gameSettings.fsHeight    = 0;
        RSDK::gameSettings.refreshRate = 60; // 0;
    }
}

void RenderDevice::ProcessEvent(SDL_Event event)
{
    switch (event.type) {
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_MAXIMIZED: {
                    SDL_RestoreWindow(window);
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    SDL_ShowCursor(SDL_FALSE);
                    RSDK::gameSettings.windowed = false;
                    break;
                }

                case SDL_WINDOWEVENT_CLOSE: isRunning = false; break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
#if RETRO_REV02
                    RSDK::SKU::userCore->focusState = 0;
#endif
                    break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
#if RETRO_REV02
                    RSDK::SKU::userCore->focusState = 1;
#endif
                    break;
            }
            break;

        case SDL_CONTROLLERDEVICEADDED: {
            uint32 id;
            char buffer[0x20];
            sprintf(buffer, "%s%d", "SDLDevice", event.cdevice.which);
            GenerateCRC(&id, buffer);

            InitSDL2InputDevice(id, event.cdevice.which);
            break;
        }

        case SDL_CONTROLLERDEVICEREMOVED: {
            uint32 id;
            char buffer[0x20];
            sprintf(buffer, "%s%d", "SDLDevice", event.cdevice.which);
            GenerateCRC(&id, buffer);

            RemoveInputDevice(InputDeviceFromID(id));
            break;
        }

        case SDL_APP_WILLENTERFOREGROUND:
#if RETRO_REV02
            RSDK::SKU::userCore->focusState = 0;
#endif
            break;

        case SDL_APP_WILLENTERBACKGROUND:
#if RETRO_REV02
            RSDK::SKU::userCore->focusState = 1;
#endif
            break;

        case SDL_APP_TERMINATING: isRunning = false; break;

        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: touchMouseData.down[0] = true; touchMouseData.count = 1;
#if !RETRO_REV02
                    if (buttonDownCount > 0)
                        buttonDownCount--;
#endif
                    break;

                case SDL_BUTTON_RIGHT:
#if !RETRO_REV02
                    specialKeyStates[3] = true;
                    buttonDownCount++;
#endif
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: touchMouseData.down[0] = false; touchMouseData.count = 0;
#if !RETRO_REV02
                    if (buttonDownCount > 0)
                        buttonDownCount--;
#endif
                    break;

                case SDL_BUTTON_RIGHT:
#if !RETRO_REV02
                    specialKeyStates[3] = false;
                    buttonDownCount--;
#endif
                    break;
            }
            break;

        case SDL_FINGERMOTION:
        case SDL_FINGERDOWN:
        case SDL_FINGERUP: {
            int32 count          = SDL_GetNumTouchFingers(event.tfinger.touchId);
            touchMouseData.count = 0;
            for (int32 i = 0; i < count; i++) {
                SDL_Finger *finger = SDL_GetTouchFinger(event.tfinger.touchId, i);
                if (finger) {
                    touchMouseData.down[touchMouseData.count] = true;
                    touchMouseData.x[touchMouseData.count]    = finger->x;
                    touchMouseData.y[touchMouseData.count]    = finger->y;
                    touchMouseData.count++;
                }
            }
            break;
        }

        case SDL_KEYDOWN:
#if !RETRO_REV02
            ++buttonDownCount;
#endif
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    if (event.key.keysym.mod == KMOD_LALT) {
                        RSDK::gameSettings.windowed ^= 1;
                        UpdateGameWindow();
                        RSDK::settingsChanged = false;
                        break;
                    }
                // [fallthrough]

                default: UpdateKeyState(event.key.keysym.scancode); break;

                case SDL_SCANCODE_ESCAPE:
                    if (engine.devMenu) {
                        if (sceneInfo.state == ENGINESTATE_DEVMENU) {
                            sceneInfo.state = devMenu.stateStore;
                            if (devMenu.stateStore == ENGINESTATE_VIDEOPLAYBACK)
                                RSDK::gameSettings.screenCount = 0;

                            ResumeSound();
                        }
                        else {
                            devMenu.stateStore = sceneInfo.state;
                            if (sceneInfo.state == ENGINESTATE_VIDEOPLAYBACK)
                                RSDK::gameSettings.screenCount = 1;

                            devMenu.state   = DevMenu_MainMenu;
                            devMenu.option  = 0;
                            devMenu.scroll  = 0;
                            devMenu.timer   = 0;
                            sceneInfo.state = ENGINESTATE_DEVMENU;
                            PauseSound();
                        }
                    }
                    else {
                        UpdateKeyState(event.key.keysym.scancode);
                    }
#if !RETRO_REV02
                    specialKeyStates[0] = true;
#endif
                    break;

#if !RETRO_REV02
                case SDL_SCANCODE_RETURN: specialKeyStates[1] = true; break;
#endif

#if !RETRO_USE_ORIGINAL_CODE
                case SDL_SCANCODE_F1:
                    sceneInfo.listPos--;
                    if (sceneInfo.listPos < sceneInfo.listCategory[sceneInfo.activeCategory].sceneOffsetStart) {
                        sceneInfo.activeCategory--;
                        if (sceneInfo.activeCategory >= sceneInfo.categoryCount) {
                            sceneInfo.activeCategory = sceneInfo.categoryCount - 1;
                        }
                        sceneInfo.listPos = sceneInfo.listCategory[sceneInfo.activeCategory].sceneOffsetEnd;
                    }

                    InitSceneLoad();
                    break;

                case SDL_SCANCODE_F2:
                    sceneInfo.listPos++;
                    if (sceneInfo.listPos > sceneInfo.listCategory[sceneInfo.activeCategory].sceneOffsetEnd) {
                        sceneInfo.activeCategory++;
                        if (sceneInfo.activeCategory >= sceneInfo.categoryCount) {
                            sceneInfo.activeCategory = 0;
                        }
                        sceneInfo.listPos = sceneInfo.listCategory[sceneInfo.activeCategory].sceneOffsetStart;
                    }

                    InitSceneLoad();
                    break;
#endif

                case SDL_SCANCODE_F3: RSDK::gameSettings.shaderID = (RSDK::gameSettings.shaderID + 1) % userShaderCount; break;

#if !RETRO_USE_ORIGINAL_CODE
                case SDL_SCANCODE_F5:
                    // Quick-Reload
                    InitSceneLoad();
                    break;

                case SDL_SCANCODE_F6:
                    if (engine.devMenu && RSDK::gameSettings.screenCount > 1)
                        RSDK::gameSettings.screenCount--;
                    break;

                case SDL_SCANCODE_F7:
                    if (engine.devMenu && RSDK::gameSettings.screenCount < SCREEN_MAX)
                        RSDK::gameSettings.screenCount++;
                    break;

                case SDL_SCANCODE_F9:
                    if (engine.devMenu)
                        showHitboxes ^= 1;
                    break;

                case SDL_SCANCODE_F10:
                    if (engine.devMenu)
                        engine.showPaletteOverlay ^= 1;
                    break;
#endif
                case SDL_SCANCODE_BACKSPACE:
                    if (engine.devMenu)
                        engine.gameSpeed = engine.fastForwardSpeed;
                    break;

                case SDL_SCANCODE_F11:
                case SDL_SCANCODE_INSERT:
                    if ((sceneInfo.state & ENGINESTATE_STEPOVER) == ENGINESTATE_STEPOVER)
                        engine.frameStep = true;
                    break;

                case SDL_SCANCODE_F12:
                case SDL_SCANCODE_PAUSE:
                    if (engine.devMenu) {
                        sceneInfo.state ^= ENGINESTATE_STEPOVER;
                    }
                    break;
            }
            break;

        case SDL_KEYUP:
#if !RETRO_REV02
            --buttonDownCount;
#endif
            switch (event.key.keysym.scancode) {
                default: ClearKeyState(event.key.keysym.scancode); break;
#if !RETRO_REV02
                case SDL_SCANCODE_ESCAPE: specialKeyStates[0] = false; break;
                case SDL_SCANCODE_RETURN: specialKeyStates[1] = false; break;
#endif
                case SDL_SCANCODE_BACKSPACE: engine.gameSpeed = 1; break;
            }
            break;

        case SDL_QUIT: isRunning = false; break;
    }
}

bool RenderDevice::ProcessEvents()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        RenderDevice::ProcessEvent(sdlEvent);

        if (!isRunning)
            return false;
    }
    return true;
}

void RenderDevice::SetupImageTexture(int32 width, int32 height, uint8 *imagePixels)
{
    if (RenderDevice::imageTexture)
        SDL_DestroyTexture(RenderDevice::imageTexture);

    int32 format               = imagePixels ? SDL_PIXELFORMAT_ARGB8888 : SDL_PIXELFORMAT_YV12;
    RenderDevice::imageTexture = SDL_CreateTexture(RenderDevice::renderer, format, SDL_TEXTUREACCESS_STREAMING, width, height);

    if (imagePixels) {
        int texPitch   = 0;
        uint32 *pixels = NULL;
        SDL_LockTexture(RenderDevice::imageTexture, NULL, (void **)&pixels, &texPitch);

        int32 pitch    = (texPitch >> 2) - width;
        uint32 *imagePixels32 = (uint32 *)imagePixels;
        for (int32 y = 0; y < height; ++y) {
            for (int32 x = 0; x < width; ++x) {
                *pixels++ = *imagePixels32++;
            }

            pixels += pitch;
        }

        SDL_UnlockTexture(RenderDevice::imageTexture);
    }
}
