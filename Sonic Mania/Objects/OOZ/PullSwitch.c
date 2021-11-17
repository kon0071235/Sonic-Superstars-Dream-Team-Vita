#include "SonicMania.h"

ObjectPullSwitch *PullSwitch;

void PullSwitch_Update(void)
{
    RSDK_THIS(PullSwitch);

    if (!entity->activated) {
        if (entity->field_5C > 0) {
            entity->position.y -= 0x20000;
            entity->field_5C -= 0x20000;
        }
    }
    else if (entity->field_5C < 0x300000) {
        entity->position.y += 0x20000;
        entity->field_5C += 0x20000;
    }
    else {
        if (OOZSetup->fadeTimer > 16 || Smog->field_4) {
            RSDK.PlaySfx(PullSwitch->sfxSmogClear, 0, 255);
        }
        OOZSetup->fadeTimer = 0;
        Smog->field_4       = 0;
    }

    entity->activated = false;
    foreach_active(Player, player)
    {
        int32 playerID       = RSDK.GetEntityID(player);
        Hitbox *playerHitbox = Player_GetHitbox(player);

        if (entity->playerTimers[playerID]) {
            entity->playerTimers[playerID]--;
        }
        else if (((1 << playerID) & entity->activePlayers)) {
            player->position.x = entity->position.x;
            player->position.y = entity->position.y - (playerHitbox->top << 16) + 0x1A0000;
            entity->activated  = true;
            if (player->state == Player_State_None) {
                if (player->jumpPress) {
                    entity->activePlayers &= ~(1 << playerID);
                    entity->playerTimers[playerID] = 60;
                    player->velocity.y             = -0x40000;
                    player->onGround               = false;
                    player->groundedStore          = false;
                    player->jumpAbilityTimer       = 1;
                    RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->playerAnimator, false, 0);
                    player->playerAnimator.animationSpeed = 48;
                    player->state                         = Player_State_Air;
                }
            }
            else {
                entity->activePlayers &= ~(1 << playerID);
                entity->playerTimers[playerID] = 60;
            }
        }
        else {
            if (Player_CheckCollisionTouch(player, entity, &PullSwitch->hitbox)) {
                entity->activePlayers |= 1 << playerID;
                player->state           = Player_State_None;
                player->nextGroundState = StateMachine_None;
                player->nextAirState    = StateMachine_None;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_HANG, &player->playerAnimator, false, 0);
                player->velocity.x  = 0;
                player->velocity.y  = 0;
                player->groundVel   = 0;
                player->controlLock = 0;
                player->position.x  = entity->position.x;
                player->position.y  = entity->position.y - (playerHitbox->top << 16) + 0x1A0000;
                entity->activated   = true;
            }
        }
    }
}

void PullSwitch_LateUpdate(void) {}

void PullSwitch_StaticUpdate(void) {}

void PullSwitch_Draw(void)
{
    RSDK_THIS(PullSwitch);
    SpriteFrame *frame = RSDK.GetFrame(PullSwitch->aniFrames, 0, 1);
    frame->height      = (entity->position.y - entity->drawPos.y) >> 16;
    frame->sprY        = entity->sprY + entity->sprHeight - frame->height;
    RSDK.DrawSprite(&entity->animator3, &entity->drawPos, false);
    RSDK.DrawSprite(&entity->animator1, NULL, false);
    RSDK.DrawSprite(&entity->animator2, &entity->drawPos, false);
}

void PullSwitch_Create(void *data)
{
    RSDK_THIS(PullSwitch);
    entity->drawFX = FX_FLIP;
    if (!SceneInfo->inEditor) {
        entity->active        = ACTIVE_BOUNDS;
        entity->visible       = true;
        entity->drawFX        = FX_FLIP;
        entity->drawOrder     = Zone->drawOrderLow;
        entity->drawPos       = entity->position;
        entity->updateRange.x = 0x800000;
        entity->updateRange.y = 0x800000;
        RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator1, true, 2);
        RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator2, true, 0);
        RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator3, true, 1);
        SpriteFrame *frame = RSDK.GetFrame(PullSwitch->aniFrames, 0, 1);
        entity->sprY       = frame->sprY;
        entity->sprHeight  = frame->height;
    }
}

void PullSwitch_StageLoad(void)
{
    if (RSDK.CheckStageFolder("OOZ1") || RSDK.CheckStageFolder("OOZ2"))
        PullSwitch->aniFrames = RSDK.LoadSpriteAnimation("OOZ/PullSwitch.bin", SCOPE_STAGE);
    PullSwitch->hitbox.left   = -16;
    PullSwitch->hitbox.top    = 20;
    PullSwitch->hitbox.right  = 16;
    PullSwitch->hitbox.bottom = 28;
    PullSwitch->sfxButton     = RSDK.GetSFX("Stage/Button.wav");
    PullSwitch->sfxSmogClear  = RSDK.GetSFX("OOZ/SmogClear.wav");
}

#if RETRO_INCLUDE_EDITOR
void PullSwitch_EditorDraw(void)
{
    RSDK_THIS(PullSwitch);
    entity->drawPos = entity->position;
    RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator1, false, 2);
    RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator2, false, 0);
    RSDK.SetSpriteAnimation(PullSwitch->aniFrames, 0, &entity->animator3, false, 1);

    RSDK.DrawSprite(&entity->animator3, &entity->drawPos, false);
    RSDK.DrawSprite(&entity->animator2, &entity->drawPos, false);

    entity->drawPos.y += 0x300000;
    RSDK.DrawSprite(&entity->animator1, &entity->drawPos, false);
}

void PullSwitch_EditorLoad(void) { PullSwitch->aniFrames = RSDK.LoadSpriteAnimation("OOZ/PullSwitch.bin", SCOPE_STAGE); }
#endif

void PullSwitch_Serialize(void) {}
