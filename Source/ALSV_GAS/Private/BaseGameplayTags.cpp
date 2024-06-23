#include "BaseGameplayTags.h"

// Movement
UE_DEFINE_GAMEPLAY_TAG(TAG_Movement, "Ability.Movement");
UE_DEFINE_GAMEPLAY_TAG(TAG_Movement_Jump, "Ability.Movement.Jump");
UE_DEFINE_GAMEPLAY_TAG(TAG_Movement_Sprint, "Ability.Movement.Sprint");
UE_DEFINE_GAMEPLAY_TAG(TAG_Movement_Walk, "Ability.Movement.Walk");
UE_DEFINE_GAMEPLAY_TAG(TAG_Movement_Crouch, "Ability.Movement.Crouch");

// Switch
UE_DEFINE_GAMEPLAY_TAG(TAG_SwitchGun, "Ability.SwitchGun");
UE_DEFINE_GAMEPLAY_TAG(TAG_SwitchGun_Primary, "Ability.SwitchGun.Main");
UE_DEFINE_GAMEPLAY_TAG(TAG_SwitchGun_Sidearm, "Ability.SwitchGun.Second");
UE_DEFINE_GAMEPLAY_TAG(TAG_SwitchGun_Equipping, "Ability.SwitchGun.Equipping");

// Gun
UE_DEFINE_GAMEPLAY_TAG(TAG_Gun_Aim, "Ability.Gun.Aim");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gun_Holster, "Ability.Gun.Holster");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gun_Reload, "Ability.Gun.Reload");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gun_Shoot, "Ability.Gun.Shoot");

// Ability
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Mobility, "Ability.Mobility.Dash");

// Effect: Damage
UE_DEFINE_GAMEPLAY_TAG(TAG_Effect_Damage, "Effect.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Effect_Damage_Gun, "Effect.Damage.Headshot");

// Cues Gun
UE_DEFINE_GAMEPLAY_TAG(TAG_GameplayCue_Gun_Bullet, "GameplayCue.Gun.Bullet");

// Cues Damage
UE_DEFINE_GAMEPLAY_TAG(TAG_GameplayCue_Damage, "GameplayCue.Damage");

// Events
UE_DEFINE_GAMEPLAY_TAG(TAG_Event_Reload, "Event.Reload");
UE_DEFINE_GAMEPLAY_TAG(TAG_Event_Gun_Ready, "Event.Gun.Ready");
UE_DEFINE_GAMEPLAY_TAG(TAG_Event_Gun_Held, "Event.Gun.Held");