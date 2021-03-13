#ifndef OBJ_FIREWORK_H
#define OBJ_FIREWORK_H

#include "../SonicMania.h"

// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectFirework;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityFirework;

// Object Struct
extern ObjectFirework *Firework;

// Standard Entity Events
void Firework_Update();
void Firework_LateUpdate();
void Firework_StaticUpdate();
void Firework_Draw();
void Firework_Create(void* data);
void Firework_StageLoad();
void Firework_EditorDraw();
void Firework_EditorLoad();
void Firework_Serialize();

// Extra Entity Functions


#endif //!OBJ_FIREWORK_H