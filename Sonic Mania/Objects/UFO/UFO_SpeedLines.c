#include "SonicMania.h"

ObjectUFO_SpeedLines *UFO_SpeedLines;

void UFO_SpeedLines_Update(void) {}

void UFO_SpeedLines_LateUpdate(void)
{
    RSDK_THIS(UFO_SpeedLines);
    EntityUFO_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, UFO_Player);
    if (UFO_Setup->machLevel > 1 && player->groundVel > 0xC0000) {
        entity->visible = true;
        for (int32 i = 0; i < 0x20; ++i) {
            if (entity->lineAlpha[i] < 0x100)
                entity->lineAlpha[i] += 0x20;

            if (entity->lineX[i] >= player->position.x - 0x800000) {
                if (entity->lineX[i] > 0x800000 + player->position.x) {
                    entity->lineX[i] -= 0x1000000;
                    entity->lineAlpha[i] = 0;
                }
            }
            else {
                entity->lineX[i] += 0x1000000;
                entity->lineAlpha[i] = 0;
            }

            if (entity->lineZ[i] < player->position.y - 0x800000) {
                entity->lineZ[i] += 0x1000000;
                entity->lineAlpha[i] = 0;
            }
            else if (entity->lineZ[i] > 0x800000 + player->position.y) {
                entity->lineZ[i] -= 0x1000000;
                entity->lineAlpha[i] = 0;
            }
        }
    }
    else {
        for (int32 i = 0; i < 0x20; ++i) {
            if (entity->lineAlpha[i] <= 0)
                entity->visible = false;
            else
                entity->lineAlpha[i] -= 8;
        }
    }
}

void UFO_SpeedLines_StaticUpdate(void) {}

void UFO_SpeedLines_Draw(void)
{
    RSDK_THIS(UFO_SpeedLines);

    Matrix *mat = &UFO_Camera->matWorld;
    for (int32 i = 0; i < 0x20; ++i) {
        int32 x     = entity->lineX[i] >> 8;
        int32 y     = entity->lineY[i] >> 8;
        int32 z     = entity->lineZ[i] >> 8;

        int32 depth = mat->values[2][3] + (y * mat->values[2][1] >> 8) + (z * mat->values[2][2] >> 8) + (x * mat->values[2][0] >> 8);
        if (depth >= 0x400) {
            int32 drawY = mat->values[1][3] + (y * mat->values[1][1] >> 8) + (z * mat->values[1][2] >> 8) + (x * mat->values[1][0] >> 8);
            int32 drawX = mat->values[0][3] + (y * mat->values[0][1] >> 8) + (z * mat->values[0][2] >> 8) + (x * mat->values[0][0] >> 8);

            RSDK.DrawLine(ScreenInfo->centerX + (drawX << 8) / depth, ScreenInfo->centerY - (drawY << 8) / depth,
                          ScreenInfo->centerX + (drawX << 8) / (depth + 0x2000), ScreenInfo->centerY - (drawY << 8) / (depth + 0x2000), 0xD0E0F0,
                          entity->lineAlpha[i], INK_ALPHA, true);
        }
    }
}

void UFO_SpeedLines_Create(void *data)
{
    RSDK_THIS(UFO_SpeedLines);
    if (!SceneInfo->inEditor) {
        entity->visible          = true;
        entity->drawFX           = FX_SCALE | FX_FLIP;
        entity->drawOrder        = 5;
        entity->active           = ACTIVE_NORMAL;
        EntityUFO_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, UFO_Player);

        for (int32 i = 0; i < 0x20; ++i) {
            entity->lineX[i] = player->position.x + RSDK.Rand(-0x800000, 0x800000);
            entity->lineY[i] = RSDK.Rand(0x100000, 0x1000000);
            entity->lineZ[i] = player->position.y + RSDK.Rand(-0x800000, 0x800000);
        }
    }
}

void UFO_SpeedLines_StageLoad(void) { RSDK.ResetEntitySlot(SLOT_UFO_SPEEDLINES, UFO_SpeedLines->objectID, NULL); }

#if RETRO_INCLUDE_EDITOR
void UFO_SpeedLines_EditorDraw(void) {}

void UFO_SpeedLines_EditorLoad(void) {}
#endif

void UFO_SpeedLines_Serialize(void) {}
