#include "SonicMania.h"

ObjectActClear *ActClear;

void ActClear_Update(void) {}

void ActClear_LateUpdate(void)
{
    RSDK_THIS(ActClear);
    StateMachine_Run(entity->state);
}

void ActClear_StaticUpdate(void) {}

void ActClear_Draw(void)
{
    Vector2 drawPos;
    Vector2 verts[4];
    int32 millisecsPtr = 0;
    int32 secsPtr      = 0;
    int32 minsPtr      = 0;
    int32 offset       = 0;
    RSDK_THIS(ActClear);

    drawPos.x  = entity->posUnknown3.x;
    drawPos.y  = entity->posUnknown3.y;
    verts[0].y = drawPos.y - 0x140000;
    verts[1].y = drawPos.y - 0x140000;
    verts[2].y = drawPos.y - 0x40000;
    verts[3].y = drawPos.y - 0x40000;
    if ((globals->playerID & 0xFF) == ID_KNUCKLES) {
        int32 center = (ScreenInfo->centerX << 16) + 0x100000;
        drawPos.x    = center + 2 * entity->posUnknown3.x;
        verts[0].x   = drawPos.x - 0x910000;
        verts[1].x   = drawPos.x + 0x340000;
        verts[2].x   = drawPos.x + 0x440000;
        verts[3].x   = drawPos.x - 0x810000;
        RSDK.DrawQuad(verts, 4, 0, 0, 0, 255, INK_NONE);

        drawPos.x  = entity->posUnknown.x;
        drawPos.y  = entity->posUnknown.y;
        drawPos.x  = center + 2 * drawPos.x;
        verts[0].x = drawPos.x - 0x7C0000;
        verts[0].y = drawPos.y + 0x1C0000;
        verts[1].x = 0x500000 + drawPos.x;
        verts[2].x = 0x600000 + drawPos.x;
        verts[3].x = drawPos.x - 0x6C0000;
        verts[1].y = drawPos.y + 0x1C0000;
        verts[2].y = drawPos.y + 0x2C0000;
        verts[3].y = drawPos.y + 0x2C0000;
        RSDK.DrawQuad(verts, 4, 0, 0, 0, 255, INK_NONE);

        drawPos.x = entity->posUnknown.x;
        drawPos.y = entity->posUnknown.y;
        drawPos.x += center;
        RSDK.DrawSprite(&entity->playerNameAnimator, &drawPos, true);
        entity->gotThroughAnimator.frameID = 2;
        RSDK.DrawSprite(&entity->gotThroughAnimator, &drawPos, true);
        drawPos.x = entity->posUnknown3.x;
        drawPos.y = entity->posUnknown3.y;
        drawPos.x += center;
        entity->gotThroughAnimator.frameID = 3;
        RSDK.DrawSprite(&entity->gotThroughAnimator, &drawPos, true);
        RSDK.DrawSprite(&entity->actNumAnimator, &drawPos, true);

        offset = center - 0xA0000;
    }
    else {
        int32 center = (ScreenInfo->centerX << 16) + 0x100000;
        drawPos.x    = center + 2 * entity->posUnknown3.x;
        verts[0].x   = drawPos.x - 0x6D0000;
        verts[1].x   = drawPos.x + 0x340000;
        verts[2].x   = drawPos.x + 0x440000;
        verts[3].x   = drawPos.x - 0x5D0000;
        RSDK.DrawQuad(verts, 4, 0, 0, 0, 255, INK_NONE);

        drawPos.x  = entity->posUnknown.x;
        drawPos.y  = entity->posUnknown.y;
        drawPos.x  = center + 2 * drawPos.x;
        verts[0].x = drawPos.x - 0x580000;
        verts[0].y = drawPos.y + 0x1C0000;
        verts[1].x = 0x500000 + drawPos.x;
        verts[2].x = 0x600000 + drawPos.x + 2;
        verts[3].x = drawPos.x - 0x480000;
        verts[1].y = drawPos.y + 0x1C0000;
        verts[2].y = drawPos.y + 0x2C0000;
        verts[3].y = drawPos.y + 0x2C0000;
        RSDK.DrawQuad(verts, 4, 0, 0, 0, 255, INK_NONE);

        drawPos.x = entity->posUnknown.x;
        drawPos.y = entity->posUnknown.y;
        drawPos.x += center;
        RSDK.DrawSprite(&entity->playerNameAnimator, &drawPos, true);

#if RETRO_USE_PLUS
        if ((globals->playerID & 0xFF) == ID_MIGHTY)
            entity->gotThroughAnimator.frameID = 2;
        else
#endif
            entity->gotThroughAnimator.frameID = 0;
        RSDK.DrawSprite(&entity->gotThroughAnimator, &drawPos, true);
        drawPos.x = entity->posUnknown3.x;
        drawPos.y = entity->posUnknown3.y;
        drawPos.x += center;
        entity->gotThroughAnimator.frameID = 1;
        RSDK.DrawSprite(&entity->gotThroughAnimator, &drawPos, true);
        RSDK.DrawSprite(&entity->actNumAnimator, &drawPos, true);

        offset = center + 0x60000;
    }

    drawPos.x                 = offset + entity->posUnknown2.x - 0x5C0000;
    drawPos.y                 = entity->posUnknown2.y;
    entity->hudElementsAnimator.frameID = 1;
    RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);
    drawPos.x += 0x320000;
#if RETRO_USE_PLUS
    if (globals->gameMode != MODE_TIMEATTACK) {
#endif
        entity->hudElementsAnimator.frameID = 8;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);
#if RETRO_USE_PLUS
    }
#endif
    entity->hudElementsAnimator.frameID = 10;
    drawPos.x += 0x340000;
    RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

    int32 dx = 0x430000 + drawPos.x;
    int32 dy = drawPos.y + 0xE0000;
    drawPos.x += 0x430000;
    drawPos.y += 0xE0000;

#if RETRO_USE_PLUS
    if (globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = dx - 0x620000;
        drawPos.y = dy - 0xE0000;
        ActClear_DrawTime(&drawPos, SceneInfo->minutes, SceneInfo->seconds, SceneInfo->milliseconds);
    }
    else {
#endif
        ActClear_DrawNumbers(&drawPos, entity->scoreBonus, 0);
#if RETRO_USE_PLUS
    }
#endif

    drawPos.x = offset + entity->posUnknown4.x - 0x5C0000;
    drawPos.y = entity->posUnknown4.y;
#if RETRO_USE_PLUS
    if (globals->gameMode == MODE_TIMEATTACK)
        entity->hudElementsAnimator.frameID = 17;
    else
#endif
        entity->hudElementsAnimator.frameID = 5;
    RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

    dx = drawPos.x + 0x320000;
    drawPos.x += 0x320000;
#if RETRO_USE_PLUS
    if (globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x                 = dx - 0xA0000;
        entity->hudElementsAnimator.frameID = 1;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);
        drawPos.x += 0xA0000;
    }
    else {
#endif
        entity->hudElementsAnimator.frameID = 8;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);
#if RETRO_USE_PLUS
    }
#endif

    entity->hudElementsAnimator.frameID = 10;
    drawPos.x += 0x340000;
    RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

    drawPos.x += 0x430000;
    drawPos.y += 0xE0000;
#if RETRO_USE_PLUS
    if (globals->gameMode == MODE_TIMEATTACK) {
        TimeAttackData_GetTimeFromValue(entity->time, &minsPtr, &secsPtr, &millisecsPtr);
        drawPos.x -= 0x620000;
        drawPos.y -= 0xE0000;
        if (!entity->isNewRecord || (entity->isNewRecord && (Zone->timer & 8)))
            ActClear_DrawTime(&drawPos, minsPtr, secsPtr, millisecsPtr);
    }
    else {
#endif
        ActClear_DrawNumbers(&drawPos, entity->ringBonus, 0);
#if RETRO_USE_PLUS
    }
#endif

    if (entity->field_84 == 1) {
        drawPos.x = entity->posUnknown5.x;
        drawPos.y = entity->posUnknown5.y;
        drawPos.x = offset + drawPos.x - 0x5C0000;
#if RETRO_USE_PLUS
        if (globals->gameMode == MODE_TIMEATTACK)
            entity->hudElementsAnimator.frameID = 18;
        else
#endif
            entity->hudElementsAnimator.frameID = 15;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        drawPos.x += 0x320000;
#if RETRO_USE_PLUS
        if (globals->gameMode != MODE_TIMEATTACK) {
#endif
            entity->hudElementsAnimator.frameID = 8;
            RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);
#if RETRO_USE_PLUS
        }
#endif

        entity->hudElementsAnimator.frameID = 10;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        drawPos.x += 0x430000;
        drawPos.y += 0xE0000;
#if RETRO_USE_PLUS
        if (globals->gameMode != MODE_TIMEATTACK) {
#endif
            ActClear_DrawNumbers(&drawPos, entity->coolBonus, 0);
#if RETRO_USE_PLUS
        }
        else {
            if (!TimeAttackData->dbRank) {
                entity->numbersAnimator.frameID = 16;
                RSDK.DrawSprite(&entity->numbersAnimator, &drawPos, true);

                drawPos.x -= 0x90000;
            }
            else if (!entity->achievedRank || (entity->achievedRank && (Zone->timer & 8)))
                ActClear_DrawNumbers(&drawPos, TimeAttackData->dbRank, 0);
        }
#endif
    }

    drawPos.x = entity->posUnknown6.x;
    drawPos.y = entity->posUnknown6.y;

#if RETRO_USE_PLUS
    if (globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x                 = offset + entity->posUnknown6.x - 0x5C0000;
        entity->hudElementsAnimator.frameID = 19;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        drawPos.x += 0x320000;
        entity->hudElementsAnimator.frameID = 18;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        entity->hudElementsAnimator.frameID = 10;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        drawPos.x += 0x430000;
        drawPos.y += 0xE0000;
        if (!TimeAttackData->rank) {
            entity->numbersAnimator.frameID = 16;
            RSDK.DrawSprite(&entity->numbersAnimator, &drawPos, true);
        }
        else {
            ActClear_DrawNumbers(&drawPos, TimeAttackData->rank, 0);
        }
    }
    else {
#endif
        drawPos.x                 = offset + entity->posUnknown6.x - 0x440000;
        entity->hudElementsAnimator.frameID = 9;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        entity->hudElementsAnimator.frameID = 10;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&entity->hudElementsAnimator, &drawPos, true);

        drawPos.x += 0x430000;
        drawPos.y += 0xE0000;
        ActClear_DrawNumbers(&drawPos, entity->totalScore, 0);
#if RETRO_USE_PLUS
    }
#endif
}

void ActClear_Create(void *data)
{
    RSDK_THIS(ActClear);
    if (!SceneInfo->inEditor) {
#if RETRO_USE_PLUS
        ActClear->dword34 = 1;
#endif
        entity->active           = ACTIVE_NORMAL;
        entity->visible          = true;
        entity->drawOrder        = Zone->hudDrawOrder;
        entity->state            = ActClear_Unknown6;
        entity->stageFinishTimer = 0;
        entity->dword78          = 0;
        EntityPlayer *player1    = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        entity->playerPtr        = player1;

        if (Zone_GetZoneID() >= 0) {
            StatInfo stat;
            uint16 time = SceneInfo->milliseconds + 100 * (SceneInfo->seconds + 60 * SceneInfo->minutes);
            switch (globals->playerID & 0xFF) {
                case ID_SONIC: TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 1, time, player1->rings, player1->score); break;
                case ID_TAILS: TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 2, time, player1->rings, player1->score); break;
                case ID_KNUCKLES: TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 3, time, player1->rings, player1->score); break;
#if RETRO_USE_PLUS
                case ID_MIGHTY: TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 4, time, player1->rings, player1->score); break;
#endif
                default:
#if RETRO_USE_PLUS
                    if ((globals->playerID & 0xFF) == ID_RAY)
                        TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 5, time, player1->rings, player1->score);
                    else
#endif
                        TimeAttackData_TrackActClear(Zone->actID, Zone_GetZoneID(), &stat, 1, time, player1->rings, player1->score);
                    break;
            }
#if RETRO_USE_PLUS
            API.TryTrackStat(&stat);
#endif
        }

#if RETRO_USE_PLUS
        if (!ActClear->disableTimeBonus) {
#endif
            switch (SceneInfo->minutes) {
                case 0:
                    if (SceneInfo->seconds >= 30)
                        entity->scoreBonus = SceneInfo->seconds < 45 ? 10000 : 5000;
                    else
                        entity->scoreBonus = 50000;
                    break;
                case 1: entity->scoreBonus = SceneInfo->seconds < 30 ? 4000 : 3000; break;
                case 2: entity->scoreBonus = 2000; break;
                case 3: entity->scoreBonus = 1000; break;
                case 4: entity->scoreBonus = 500; break;
                case 5: entity->scoreBonus = 100; break;
                case 9:
                    if (!SceneInfo->debugMode && globals->gameMode < MODE_TIMEATTACK && SceneInfo->seconds == 59) {
#if RETRO_USE_PLUS
                        if (globals->gameMode != MODE_ENCORE && !(globals->medalMods & getMod(MEDAL_NOTIMEOVER)))
#endif
                            entity->scoreBonus = 100000;
                    }
                    break;
                default: break;
            }
#if RETRO_USE_PLUS
        }
#endif

        entity->ringBonus      = 100 * player1->rings;
        entity->coolBonus      = globals->coolBonus[0];
        globals->initCoolBonus = false;
#if RETRO_USE_PLUS
        if (globals->gameMode == MODE_TIMEATTACK) {
            EntityMenuParam *param = (EntityMenuParam *)globals->menuParam;
            entity->time = TimeAttackData_GetScore(param->zoneID, param->characterID, param->actID, SceneInfo->filter == SCN_FILTER_ENCORE, 1);
            entity->achievedRank = false;
            entity->isNewRecord  = false;
        }
#endif
        entity->field_84      = 1;
        entity->posUnknown.x  = 0xE00000;
        entity->posUnknown.y  = 0x580000;
        entity->posUnknown3.x = -0xE00000;
        entity->posUnknown3.y = 0x700000;
        entity->posUnknown2.x = 0x1E80000;
        entity->posUnknown2.y = 0x780000;
        entity->posUnknown4.x = 0x3080000;
        entity->posUnknown4.y = 0x880000;
        entity->posUnknown5.x = 0x4280000;
        entity->posUnknown5.y = 0x980000;
        entity->posUnknown6.x = -0x5480000;
        entity->posUnknown6.y = 0xC00000;
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 0, &entity->hudElementsAnimator, true, 0);
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 1, &entity->numbersAnimator, true, 0);
#if RETRO_USE_PLUS
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 0, &entity->timeElementsAnimator, true, 12);
#endif
        switch (globals->playerID & 0xFF) {
            case ID_TAILS: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &entity->playerNameAnimator, true, 1); break;
            case ID_KNUCKLES: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &entity->playerNameAnimator, true, 2); break;
#if RETRO_USE_PLUS
            case ID_MIGHTY: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &entity->playerNameAnimator, true, 3); break;
            case ID_RAY: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &entity->playerNameAnimator, true, 4); break;
#endif
            default: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &entity->playerNameAnimator, true, 0); break;
        }
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 4, &entity->gotThroughAnimator, true, 0);

        if (ActClear->actID <= 0)
            RSDK.SetSpriteAnimation(ActClear->aniFrames, 5, &entity->actNumAnimator, true, Zone->actID);
        else
            RSDK.SetSpriteAnimation(ActClear->aniFrames, 5, &entity->actNumAnimator, true, ActClear->actID - 1);
    }
}

void ActClear_StageLoad(void)
{
    ActClear->aniFrames    = RSDK.LoadSpriteAnimation("Global/HUD.bin", SCOPE_STAGE);
    ActClear->sfxScoreAdd   = RSDK.GetSFX("Global/ScoreAdd.wav");
    ActClear->sfxScoreTotal = RSDK.GetSFX("Global/ScoreTotal.wav");
#if RETRO_USE_PLUS
    ActClear->dword34     = 0;
    ActClear->sfxEvent   = RSDK.GetSFX("Special/Event.wav");
    ActClear->forceNoSave = false;
#endif
}

#if RETRO_USE_PLUS
void ActClear_DrawTime(Vector2 *pos, int32 mins, int32 secs, int32 millisecs)
{
    Vector2 drawPos;
    RSDK_THIS(ActClear);
    if (!mins && !secs && !millisecs) {
        millisecs = -1;
        secs      = -1;
        mins      = -1;
    }

    drawPos.x = pos->x + 0x320000;
    drawPos.y = pos->y - 0x20000;
    RSDK.DrawSprite(&entity->timeElementsAnimator, &drawPos, true);

    drawPos.x = 0x610000 + pos->x + 2;
    drawPos.y = pos->y + 0xE0000;
    ActClear_DrawNumbers(&drawPos, millisecs, 2);

    drawPos.x -= 0x90000;
    if (!mins && !secs && !millisecs)
        secs = -1;
    ActClear_DrawNumbers(&drawPos, secs, 2);

    drawPos.x -= 0x90000;
    if (!mins && !secs && !millisecs)
        mins = -1;
    ActClear_DrawNumbers(&drawPos, mins, 1);
}
#endif

void ActClear_DrawNumbers(Vector2 *pos, int32 value, int32 maxVals)
{
    RSDK_THIS(ActClear);
    int32 mult = 1;
    if (value >= 0) {
        if (!maxVals) {
            if (value <= 0) {
                maxVals = 1;
            }
            else {
                int32 i = value;
                do {
                    ++maxVals;
                    i /= 10;
                } while (i > 0);
            }
        }

        if (maxVals > 0) {
            int32 digit = 1;
            do {
                entity->numbersAnimator.frameID = value / mult % 10;
                RSDK.DrawSprite(&entity->numbersAnimator, pos, true);
                pos->x -= 0x90000;
                mult = 10 * digit;
                digit *= 10;
            } while (--maxVals);
        }
    }
    else if (maxVals > 0) {
        do {
            entity->numbersAnimator.frameID = 16;
            RSDK.DrawSprite(&entity->numbersAnimator, pos, true);
            pos->x -= 0x90000;
        } while (--maxVals);
    }
}
void ActClear_CheckPlayerVictory(void)
{
    foreach_active(Player, player)
    {
        if (player->state != Player_State_FlyIn && player->state != Player_State_JumpIn && player->state != Player_State_Victory
            && player->onGround) {
            player->state           = Player_State_Victory;
            player->nextAirState    = 0;
            player->nextGroundState = 0;
            if (Zone->forcePlayerOnScreenFlag)
                player->stateInput = StateMachine_None;
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_VICTORY, &player->playerAnimator, true, 0);
        }
    }
}
void ActClear_SaveGameCallback(int32 success)
{
    UIWaitSpinner_Wait2();
    ActClear->finishedSavingGame = 0;
}

void ActClear_Unknown5(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    if (player2) {
        if (player2->sidekick) {
            if (player2->state != Player_State_FlyIn && player2->state != Player_State_JumpIn) {
                if (player2->position.x <= (ScreenInfo->width + ScreenInfo->position.x) << 16
                    || abs(player2->position.y - player1->position.y) > 0x100000) {
                    Player->jumpInDelay    = 240;
                    Entity *entStore       = SceneInfo->entity;
                    SceneInfo->entity = (Entity *)player2;
                    Player_P2JumpBackIn();
                    SceneInfo->entity = entStore;
                    if (player2->state == Player_State_FlyIn || player2->state == Player_State_JumpIn || player2->state == Player_State_StartJumpIn) {
                        player2->active     = ACTIVE_NORMAL;
                        player2->position.y = ((ScreenInfo->position.y - 16) << 16);
                    }
                }
                else {
                    Player->jumpInDelay = -3600;
                }
            }
        }
    }
}

void ActClear_Unknown6(void)
{
    RSDK_THIS(ActClear);

    if (entity->posUnknown.x > 0)
        entity->posUnknown.x -= 0x100000;

    if (entity->posUnknown3.x < 0)
        entity->posUnknown3.x += 0x100000;
    if (!entity->timer && Zone->forcePlayerOnScreenFlag)
        ActClear_Unknown5();

    if (++entity->timer == 48) {
        entity->timer = 0;
        entity->state = ActClear_Unknown7;
    }
    ActClear_CheckPlayerVictory();
}

void ActClear_Unknown7(void)
{
    RSDK_THIS(ActClear);

    entity->posUnknown.y -= 0x8000;
    entity->posUnknown3.y -= 0x8000;
    if (++entity->timer == 48) {
        entity->timer = 0;
        entity->state = ActClear_State_TAFinish;
    }
    ActClear_CheckPlayerVictory();
}

void ActClear_State_TAFinish(void)
{
    RSDK_THIS(ActClear);

    if (entity->posUnknown2.x > 0)
        entity->posUnknown2.x -= 0x100000;

    if (entity->posUnknown4.x > 0)
        entity->posUnknown4.x -= 0x100000;

    if (entity->posUnknown5.x > 0)
        entity->posUnknown5.x -= 0x100000;

    if (entity->posUnknown6.x >= -0x80000) {
#if RETRO_USE_PLUS
        if (globals->gameMode == MODE_TIMEATTACK) {
            if (ActClear->isTimeAttack) {
                StateMachine_Run(ActClear->bufferMove_CB);
            }
            HUD->showTAPrompt        = true;
            ActClear->hasSavedReplay = false;
            entity->dword78          = 240;
            entity->state            = ActClear_State_TAResults;
            RSDK.SetScene("Presentation", "Menu");
        }
        else {
            entity->state = ActClear_Unknown8;
        }
#else
        entity->state = ActClear_Unknown8;
#endif
    }
    else {
        entity->posUnknown6.x += 0x100000;
    }
    ActClear_CheckPlayerVictory();
}

void ActClear_Unknown8(void)
{
    RSDK_THIS(ActClear);
    if (++entity->timer == 120) {
        entity->timer = 0;
        entity->state = ActClear_TallyScore;
    }
    ActClear_CheckPlayerVictory();
}

void ActClear_TallyScore(void)
{
    RSDK_THIS(ActClear);
    EntityPlayer *player = (EntityPlayer *)entity->playerPtr;

    if (entity->scoreBonus > 0) {
        entity->totalScore += 100;
        entity->scoreBonus -= 100;
        Player_GiveScore(player, 100);
    }

    if (entity->ringBonus > 0) {
        entity->totalScore += 100;
        entity->ringBonus -= 100;
        Player_GiveScore(player, 100);
    }

    if (entity->coolBonus > 0) {
        entity->totalScore += 100;
        entity->coolBonus -= 100;
        Player_GiveScore(player, 100);
    }

#if RETRO_USE_TOUCH_CONTROLS
    if (ControllerInfo[player->controllerID].keyA.press || ControllerInfo[player->controllerID].keyStart.press || TouchInfo->count) {
#else
    if (ControllerInfo[player->controllerID].keyA.press || ControllerInfo[player->controllerID].keyStart.press) {
#endif
        Player_GiveScore(player, entity->scoreBonus + entity->ringBonus + entity->coolBonus);
        entity->totalScore += entity->scoreBonus + entity->ringBonus + entity->coolBonus;
        entity->scoreBonus = 0;
        entity->ringBonus  = 0;
        entity->coolBonus  = 0;
    }

    if (entity->scoreBonus + entity->ringBonus + entity->coolBonus <= 0) {
        entity->timer = 0;
        entity->state = ActClear_LoadNextScene;
        RSDK.PlaySfx(ActClear->sfxScoreTotal, 0, 255);
    }
    else if (++entity->timer == 2) {
        entity->timer = 0;
        RSDK.PlaySfx(ActClear->sfxScoreAdd, 0, 255);
    }
    Music->nextTrack = -1;
    ActClear_CheckPlayerVictory();
}

void ActClear_LoadNextScene(void)
{
    RSDK_THIS(ActClear);
    if (++entity->timer == 120) {
        entity->timer          = 0;
        globals->specialRingID = 0;
        if (ActClear->actID <= 0) {
            if (globals->gameMode == MODE_COMPETITION) {
                RSDK.SetScene("Presentation", "Menu");
            }
#if !RETRO_USE_PLUS
            else if (globals->gameMode == MODE_TIMEATTACK) {
                EntityMenuParam *param       = (EntityMenuParam *)globals->menuParam;
                ActClear->finishedSavingGame = true;
                uint8 playerID               = param->characterID;
                uint8 zoneID                 = param->zoneID;
                uint8 actID                  = param->actID;

                int32 time = 6000 * SceneInfo->minutes + 100 * SceneInfo->seconds + SceneInfo->milliseconds;

                uint16 *record = TimeAttackData_GetRecordedTime(zoneID, actID, playerID, 1);
                int32 rank     = 0;
                for (; rank < 3; ++rank) {
                    if (!record[rank] || time < record[rank])
                        break;
                }

                if (rank < 3) {
                    rank++;
                    TimeAttackData_SaveTATime(zoneID, actID, playerID, rank, time);
                    TimeAttackData_TrackTAClear(actID, zoneID, NULL, playerID, MODE_MANIA, time);
                    param->timeScore = rank;
                    SaveGame_SaveFile(ActClear_SaveGameCallback);
                }
                else {
                    ActClear->finishedSavingGame = false;
                }

                RSDK.SetScene("Presentation", "Menu");
            }
#endif
            else {
                globals->enableIntro = true;
                Player_SaveValues();
                SaveGame_ClearRestartData();
                StarPost_ResetStarPosts();
                if (Zone->actID > 0)
                    SaveGame->saveRAM->collectedSpecialRings = 0;
                SaveGame_SaveProgress();
#if RETRO_USE_PLUS
                if (globals->saveSlotID != NO_SAVE_SLOT && !ActClear->forceNoSave) {
#else
                if (globals->gameMode == MODE_MANIA) {
#endif
                    if (Zone_IsAct2())
                        GameProgress_MarkZoneCompleted(Zone_GetZoneID());
                    ActClear->finishedSavingGame = true;
                    SaveGame_SaveFile(ActClear_SaveGameCallback);
                }
                ++SceneInfo->listPos;
                if (!RSDK.CheckValidScene())
                    RSDK.SetScene("Presentation", "Title Screen");
            }
        }
        else {
            Player_SaveValues();
            SaveGame_ClearRestartData();
            StarPost_ResetStarPosts();
            SaveGame_SaveProgress();
#if RETRO_USE_PLUS
            if (globals->saveSlotID != NO_SAVE_SLOT && !ActClear->forceNoSave) {
#else
            if (globals->gameMode == MODE_MANIA) {
#endif
                ActClear->finishedSavingGame = true;
                SaveGame_SaveFile(ActClear_SaveGameCallback);
            }
        }
        if (ActClear->finishedSavingGame)
            UIWaitSpinner_Wait();

        if (ActClear->finishedSavingGame) {
            entity->state = ActClear_Unknown10;
        }
        else {
            if (ActClear->actID > 0 || Zone->stageFinishCallback) {
                entity->state = ActClear_State_ActFinish;
            }
            else {
                entity->state = StateMachine_None;
                Zone_StartFadeOut(10, 0x000000);
            }
        }
    }
}

#if RETRO_USE_PLUS
void ActClear_State_TAResults(void)
{
    RSDK_THIS(ActClear);

    if (entity->dword78 > 0) {
        if (TimeAttackData->dbRank <= 0 || ReplayRecorder->dword13C) {
            --entity->dword78;
        }
        else {
            if (entity->dword78 == 120) {
                if (TimeAttackData->dbRank == 1)
                    entity->isNewRecord = true;
                entity->achievedRank = true;
                RSDK.PlaySfx(ActClear->sfxEvent, 0, 255);
            }

            if (entity->dword78 != 30) {
                --entity->dword78;
            }
            else {
                if (TimeAttackData->dbRank == 1) {
                    RSDK.PlaySfx(Announcer->sfxNewRecordTop, 0, 255);
                    --entity->dword78;
                }
                else {
                    if (TimeAttackData->dbRank > 3) {
                        --entity->dword78;
                    }
                    else {
                        RSDK.PlaySfx(Announcer->sfxNewRecordMid, 0, 255);
                        --entity->dword78;
                    }
                }
            }
        }
    }

    if (!ActClear->finishedSavingGame && !ActClear->disableResultsInput) {
#if RETRO_USE_TOUCH_CONTROLS
        for (int32 t = 0; t < TouchInfo->count; ++t) {
            int32 tx = (TouchInfo->x[t] * ScreenInfo->width);
            int32 ty = (TouchInfo->y[t] * ScreenInfo->height);

            if (TouchInfo->down[t]) {
                if (tx >= ScreenInfo->width - 0x80 && ty >= 0 && tx <= ScreenInfo->width && ty <= 0x40) {
                    ControllerInfo->keyY.press |= 1;
                    break;
                }
            }
        }

        ControllerInfo->keyStart.press |= TouchInfo->count && !ControllerInfo->keyY.press;
#endif

        if (ControllerInfo->keyY.press) {
            if (!ActClear->hasSavedReplay) {
                if (HUD->replaySaveEnabled) {
                    if (!UIDialog->activeDialog) {
                        if (API.CheckDLC(DLC_PLUS)) {
                            StateMachine_Run(ActClear->saveReplay_CB);
                            ActClear->hasSavedReplay      = true;
                            ActClear->disableResultsInput = true;
                            return;
                        }
                    }
                }
            }
        }

        if (ControllerInfo->keyStart.press) {
            RSDK.PlaySfx(UIWidgets->sfxAccept, false, 255);

            RSDK_THIS(ActClear);
            if (ActClear->actID > 0 || Zone->stageFinishCallback) {
                entity->state = ActClear_State_ActFinish;
            }
            else {
                entity->state = StateMachine_None;
                Zone_StartFadeOut(10, 0x000000);
            }
        }
    }
}
#endif

void ActClear_Unknown10(void)
{
    if (ActClear->finishedSavingGame) {
        RSDK_THIS(ActClear);
        if (ActClear->actID > 0 || Zone->stageFinishCallback) {
            entity->state = ActClear_State_ActFinish;
        }
        else {
            entity->state    = StateMachine_None;
            EntityZone *zone = RSDK_GET_ENTITY(SLOT_ZONE, Zone);
            zone->screenID   = 4;
            zone->timer      = 0;
            zone->fadeSpeed  = 10;
            zone->fadeColour = 0;
            zone->state      = Zone_State_Fadeout;
            zone->stateDraw  = Zone_StateDraw_Fadeout;
            zone->visible    = true;
            zone->drawOrder  = 15;
        }
    }
}

void ActClear_State_ActFinish(void)
{
    RSDK_THIS(ActClear);
    entity->posUnknown.x += 0x200000;
    entity->posUnknown3.x -= 0x200000;
    if (entity->posUnknown.x > 0x400000)
        entity->posUnknown2.x += 0x200000;
    if (entity->posUnknown2.x > 0x400000)
        entity->posUnknown4.x += 0x200000;
    if (entity->posUnknown4.x > 0x400000)
        entity->posUnknown5.x += 0x200000;
    if (entity->posUnknown5.x > 0x400000)
        entity->posUnknown6.x -= 0x200000;

    if (entity->posUnknown6.x < -0x2000000) {
        if (ActClear->actID <= 0) {
            if (Zone->stageFinishCallback) {
                if (Zone->forcePlayerOnScreenFlag) {
                    entity->timer = 0;
                    entity->state = ActClear_ForcePlayerOnScreen;
                }
                else {
                    foreach_active(Animals, animal)
                    {
                        if (animal->behaviour == 1)
                            animal->behaviour = 0;
                    }
                    Zone->stageFinishCallback();
                    Zone->stageFinishCallback = NULL;
                }
            }
        }
        else {
            ActClear->finished           = true;
            ActClear->actID              = 0;
            SceneInfo->milliseconds = 0;
            SceneInfo->seconds      = 0;
            SceneInfo->minutes      = 0;
            foreach_active(Player, player)
            {
                player->ringExtraLife = 100;
                player->rings         = 0;
            }
        }
        if (entity->state != ActClear_ForcePlayerOnScreen)
            destroyEntity(entity);
    }
}

void ActClear_ForcePlayerOnScreen(void)
{
    RSDK_THIS(ActClear);
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    bool32 finishedP2     = false;
    bool32 finishedP1     = false;
    int32 screenOffX      = ScreenInfo->width - 16 + ScreenInfo->position.x;
    screenOffX <<= 16;
    player1->up        = false;
    player1->down      = false;
    player1->jumpPress = false;
    player1->jumpHold  = false;

    if (player1->position.x >= screenOffX) {
        player1->stateInput = StateMachine_None;
        player1->state      = Player_State_Ground;
        player1->groundVel  = -0x40000;
        player1->left       = true;
        player1->right      = false;
    }
    else {
        if ((!player1->onGround || player1->groundVel) && player1->position.x < screenOffX - (ScreenInfo->centerX << 15)) {
            player1->right = true;
            if (!player1->skidding) {
                if (!player1->left)
                    player1->right = false;
                else
                    player1->left = false;
            }
        }

        if (player1->onGround && !player1->groundVel)
            finishedP1 = true;
    }

    if (player2->objectID != Player->objectID) {
        finishedP2 = true;
    }
    else {
        player2->up        = false;
        player2->down      = false;
        player2->jumpPress = false;
        player2->jumpHold  = false;
        if (player2->state == Player_State_FlyIn || player2->state == Player_State_JumpIn) {
            if (player2->position.x < screenOffX) {
                if (player2->onGround && !player2->groundVel) {
                    RSDK.SetSpriteAnimation(player2->aniFrames, ANI_IDLE, &player2->playerAnimator, false, 0);
                    player2->direction = FLIP_NONE;
                    finishedP2         = true;
                }
            }
        }
        else if (player2->position.x >= screenOffX) {
            player2->stateInput = Player_ProcessP2Input_AI;
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_RUN, &player2->playerAnimator, false, 0);
            player2->state     = Player_State_Ground;
            player2->groundVel = -0x40000;
            player2->left      = true;
            player2->right     = false;

            if (player2->position.x < screenOffX) {
                if (player2->onGround && !player2->groundVel) {
                    RSDK.SetSpriteAnimation(player2->aniFrames, ANI_IDLE, &player2->playerAnimator, false, 0);
                    player2->direction = FLIP_NONE;
                    finishedP2         = true;
                }
            }
        }
        else {
            if (player2->onGround && !player2->groundVel) {
                RSDK.SetSpriteAnimation(player2->aniFrames, ANI_IDLE, &player2->playerAnimator, false, 0);
                player2->direction = FLIP_NONE;
                finishedP2         = true;
            }
        }
    }

    if (finishedP1) {
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_IDLE, &player1->playerAnimator, false, 0);
        player1->direction = FLIP_NONE;
    }

    ++entity->stageFinishTimer;
    if ((finishedP1 && finishedP2) || entity->stageFinishTimer >= 900) {
        if (entity->timer >= 10) {
            Player->jumpInDelay = 0;
            StateMachine_Run(Zone->stageFinishCallback);
            Zone->stageFinishCallback = StateMachine_None;
            destroyEntity(entity);
        }
        else {
            entity->timer++;
        }
    }
}

#if RETRO_INCLUDE_EDITOR
void ActClear_EditorDraw(void) {}

void ActClear_EditorLoad(void) {}
#endif

void ActClear_Serialize(void) {}
