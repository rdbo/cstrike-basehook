#ifndef SDK_H
#define SDK_H

#include "BaseTypes.h"
#include "Defines.h"
#include "Types/_generic.h"
#include "Types/AmmoInfo.h"
#include "Types/ItemInfo.h"
#include "Types/ToggleState.h"
#include "Types/FieldType.h"
#include "Types/TypeDescription.h"
#include "Types/link.h"
#include "Types/entvars.h"
#include "Types/edict.h"
#include "Types/EHandle.h"
#include "Types/Vector2D.h"
#include "Types/Vector.h"
#include "Types/UseType.h"
#include "Types/KeyValueData.h"
#include "Types/Activity.h"
#include "Types/TraceResult.h"
#include "Types/TeamName.h"
#include "Types/JoinState.h"
#include "Types/ModelName.h"
#include "Types/Menu.h"
#include "Types/MonsterState.h"
#include "Types/MonsterEvent.h"
#include "Types/RebuyStruct.h"
#include "Types/PlayerAnim.h"
#include "Types/AutoBuyClassType.h"
#include "Types/AutoBuyInfoStruct.h"
#include "Types/resourcetype.h"
#include "Types/resource.h"
#include "Types/usercmd.h"
#include "Types/screenfade.h"
#include "Types/clientdata.h"
#include "Types/entity_state.h"
#include "Types/weapon_data.h"
#include "Types/packet_entities.h"
#include "Types/frame.h"
#include "Types/cmd.h"
#include "Types/local_state.h"
#include "Types/event.h"
#include "Types/modtype.h"
#include "Types/synctype.h"
#include "Types/dmodel.h"
#include "Types/mplane.h"
#include "Types/mnode.h"
#include "Types/position_history.h"
#include "Types/mouth.h"
#include "Types/latchedvars.h"
#include "Types/cl_entity.h"
#include "Types/efrag.h"
#include "Types/surfcache.h"
#include "Types/texture.h"
#include "Types/mtexinfo.h"
#include "Types/decal.h"
#include "Types/msurface.h"
#include "Types/mleaf.h"
#include "Types/mvertex.h"
#include "Types/medge.h"
#include "Types/dclipnode.h"
#include "Types/hull.h"
#include "Types/cache_user.h"
#include "Types/model.h"
#include "Types/sfx.h"
#include "Types/consistency.h"
#include "Types/dlight.h"
#include "Types/customization.h"
#include "Types/player_info.h"
#include "Types/event_args.h"
#include "Types/event_info.h"
#include "Types/event_state.h"
#include "Types/client_state.h"
#include "Types/client_textmessage.h"
#include "Types/sequenceCommandLine.h"
#include "Types/sequenceEntry.h"
#include "Types/sentenceEntry.h"
#include "Types/cmdalias.h"
#include "Types/cl_enginefuncs.h"
#include "Types/kbutton.h"
#include "Types/cldll_func.h"
#include "Types/physent.h"
#include "Types/plane.h"
#include "Types/movevars.h"
#include "Types/pmplane.h"
#include "Types/pmtrace.h"
#include "Types/trace.h"
#include "Types/playermove.h"
#include "Types/FileHandle.h"
#include "Types/FileSystemSeek.h"
#include "Types/FileFindHandle.h"
#include "Types/FileWarningLevel.h"
#include "Types/WairForResourcesHandle.h"
#include "Interfaces/IBaseInterface.h"
#include "Interfaces/IGameConsole.h"
#include "Interfaces/IGame.h"
#include "Interfaces/IEngine.h"
#include "Interfaces/IBaseUI.h"
#include "Interfaces/ISystemModule.h"
#include "Interfaces/IFileSystem.h"
#include "Interfaces/IVGuiModule.h"
#include "Interfaces/IObjectContainer.h"
#include "Interfaces/IBaseSystem.h"
#include "Classes/CGameConsoleDialog.h"
#include "Classes/CGameConsole.h"
#include "Classes/CGame.h"
#include "Classes/CEngine.h"
#include "Classes/CSave.h"
#include "Classes/CRestore.h"
#include "Classes/CSquadMonster.h"
#include "Classes/CBaseEntity.h"
#include "Classes/CBaseDelay.h"
#include "Classes/CBaseAnimating.h"
#include "Classes/CBaseToggle.h"
#include "Classes/CBaseMonster.h"
#include "Classes/CHintMessageQueue.h"
#include "Classes/CUnifiedSignals.h"
#include "Classes/CBasePlayerItem.h"
#include "Classes/CWeaponBox.h"
#include "Classes/CBasePlayer.h"
#include "Classes/ObjectList.h"

#endif