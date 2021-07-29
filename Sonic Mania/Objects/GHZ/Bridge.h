#ifndef OBJ_BRIDGE_H
#define OBJ_BRIDGE_H

#include "SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    ushort aniFrames;
} ObjectBridge;

// Entity Class
typedef struct {
    RSDK_ENTITY
    byte length;
    bool32 burnable;
    byte field_60;
    byte activePlayerCount;
    byte timer;
    int stoodPos;
    int field_68;
    int field_6C;
    Entity *playerPtr;
    int startPos;
    int endPos;
    Animator animator;
    int dword94;
} EntityBridge;

// Object Struct
extern ObjectBridge *Bridge;

// Standard Entity Events
void Bridge_Update(void);
void Bridge_LateUpdate(void);
void Bridge_StaticUpdate(void);
void Bridge_Draw(void);
void Bridge_Create(void* data);
void Bridge_StageLoad(void);
void Bridge_EditorDraw(void);
void Bridge_EditorLoad(void);
void Bridge_Serialize(void);

// Extra Entity Functions
void Bridge_Burn(int offset);


#endif //!OBJ_BRIDGE_H