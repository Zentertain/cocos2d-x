//
//  LuaSlotsSaga.cpp
//  slotssaga3
//
//  Created by Alanmars on 14-1-22.
//
//

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "CCLuaEngine.h"

#include "Game.h"
#include "LogicMan.h"

#include "LuaSlotsSaga.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "Game");
	tolua_usertype(tolua_S, "LogicMan");
	tolua_usertype(tolua_S, "isValidSymbolForCol");
}

/* function: whether or not the symbol is valid for colume */
#ifndef TOLUA_DISABLE_tolua_User_Define_isValidSymbolForCol
static int tolua_User_Define_isValidSymbolForCol(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int col     = ((int) tolua_tonumber(tolua_S,1,0));
        int mask    = ((int) tolua_tonumber(tolua_S,2,0));
        int rst     = mask & (1 << (col-1));
        tolua_pushnumber(tolua_S,(lua_Number)rst);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_getInstance00
static int tolua_User_Define_Game_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Game* tolua_ret = (Game*)  Game::getInstance();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Game");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modeTypePersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_modeTypePersistence00
static int tolua_User_Define_Game_modeTypePersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        int modeType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modeTypePersistence'", NULL);
#endif
        {
            self->modeTypePersistence(modeType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'modeTypePersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: luckyModeLeftSpinCountPersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_luckyModeLeftSpinCountPersistence00
static int tolua_User_Define_Game_luckyModeLeftSpinCountPersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        int luckyModeLeftSpinCount = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'luckyModeLeftSpinCountPersistence'", NULL);
#endif
        {
            self->luckyModeLeftSpinCountPersistence(luckyModeLeftSpinCount);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'luckyModeLeftSpinCountPersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: userMustLiveLeftSpinCountPersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_UserMustLiveLeftSpinCountPersistence00
static int tolua_User_Define_Game_UserMustLiveLeftSpinCountPersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        int leftSpinCount = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'userMustLiveLeftSpinCountPersistence'", NULL);
#endif
        {
            self->userMustLiveLeftSpinCountPersistence(leftSpinCount);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'userMustLiveLeftSpinCountPersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: userMustLiveLeftSpinCountPersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_LuaRuntimeParameterPersistence00
static int tolua_User_Define_Game_LuaRuntimeParameterPersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,9,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        int modeType =              ((int)  tolua_tonumber(tolua_S,2,0));
        int leftSpinCount =         ((int)  tolua_tonumber(tolua_S,3,0));
        int mustLiveCount =         ((int)  tolua_tonumber(tolua_S,4,0));
        int mustDieCount =          ((int)  tolua_tonumber(tolua_S,5,0));
        int lowRateSpinCount =      ((int)  tolua_tonumber(tolua_S,6,0));
        int64_t upperThreshold =    ((int64_t)  tolua_tonumber(tolua_S,7,0));
        int64_t lowerThreshold =    ((int64_t)  tolua_tonumber(tolua_S,8,0));

#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRuntimeParameterPersistence'", NULL);
#endif
        {
            self->luaRuntimeParameterPersistence( modeType, leftSpinCount, mustLiveCount, mustDieCount,
                                                 lowRateSpinCount, upperThreshold, lowerThreshold);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'LuaRuntimeParameterPersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* method: userMustDieLeftSpinCountPersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_UserMustDieLeftSpinCountPersistence00
static int tolua_User_Define_Game_UserMustDieLeftSpinCountPersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        int leftSpinCount = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'userMustDieLeftSpinCountPersistence'", NULL);
#endif
        {
            self->userMustDieLeftSpinCountPersistence(leftSpinCount);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'userMustDieLeftSpinCountPersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: luckyTablePersistence of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_LuckyTablePersistence00
static int tolua_User_Define_Game_LuckyTablePersistence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
        std::vector<int> luckyTable;
        
        /*
         lua_gettable(tolua_S,2);
         lua_pushnil(tolua_S);
         while ( lua_next(tolua_S, 2) )
         {
         lua_pushnil(tolua_S);
         while ( lua_next(tolua_S, 2) )
         {
         int value = (int)lua_tonumber(tolua_S, -1);
         lua_pop(tolua_S,1);
         int key = (int)lua_tonumber(tolua_S, -1);
         luckyTable.push_back(value);
         }
         }
         */
        //lua_pushnumber(tolua_S, 1);
        //lua_gettable(tolua_S,2);
        //lua_pushnil(tolua_S);
        if ( lua_istable(tolua_S, 2) )
        {
            lua_pushnil(tolua_S);
            while ( lua_next(tolua_S, -2) )
            {
                //
                lua_pushnil(tolua_S);
                while ( lua_next(tolua_S, -2) )
                {
                    int value = (int)lua_tonumber(tolua_S, -1);
                    lua_pop(tolua_S,1);
                    //lua_tonumber(tolua_S, -1);
                    luckyTable.push_back(value);
                }
                lua_pop(tolua_S,1);
                //lua_tonumber(tolua_S, -1);
            }
        }
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'luckyTablePersistence'", NULL);
#endif
        {
            self->luckyTablePersistence(luckyTable);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'luckyTablePersistence'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClientPlatformType of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_GetClientPlatformType00
static int tolua_User_Define_Game_GetClientPlatformType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClientPlatformType'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->getClientPlatformType();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getClientPlatformType'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClientVersion of class  Game */
#ifndef TOLUA_DISABLE_tolua_User_Define_Game_GetClientVersion00
static int tolua_User_Define_Game_GetClientVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Game",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Game* self = (Game*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClientVersion'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->getClientVersion();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getClientVersion'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

//-------------------------------------------------------
#ifndef TOLUA_DISABLE_tolua_User_Define_LogicMan_getInstance00
static int tolua_User_Define_LogicMan_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"LogicMan",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            LogicMan* tolua_ret = (LogicMan*)  LogicMan::getInstance();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"LogicMan");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


#ifndef TOLUA_DISABLE_tolua_User_Define_LogicMan_forceUpdateClient00
static int tolua_User_Define_LogicMan_forceUpdateClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"LogicMan",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LogicMan* self = (LogicMan*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'forceUpdateClient'", NULL);
#endif
        {
            self->forceUpdateClient();
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SlotsSaga_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 
    tolua_function(tolua_S, "isValidSymbolForCol", tolua_User_Define_isValidSymbolForCol);
    
    tolua_cclass(tolua_S,"Game","Game","",NULL);
    tolua_beginmodule(tolua_S,"Game");
    tolua_function(tolua_S, "getInstance", tolua_User_Define_Game_getInstance00);
    tolua_function(tolua_S,"modeTypePersistence",tolua_User_Define_Game_modeTypePersistence00);
    tolua_function(tolua_S,"luckyModeLeftSpinCountPersistence",tolua_User_Define_Game_luckyModeLeftSpinCountPersistence00);
    tolua_function(tolua_S,"luckyTablePersistence",tolua_User_Define_Game_LuckyTablePersistence00);
    tolua_function(tolua_S, "userMustLiveLeftSpinCountPersistence", tolua_User_Define_Game_UserMustLiveLeftSpinCountPersistence00);
    tolua_function(tolua_S, "userMustDieLeftSpinCountPersistence", tolua_User_Define_Game_UserMustDieLeftSpinCountPersistence00);
    tolua_function(tolua_S, "luaRuntimeParameterPersistence", tolua_User_Define_Game_LuaRuntimeParameterPersistence00);
    tolua_function(tolua_S, "getClientVersion", tolua_User_Define_Game_GetClientVersion00);
    tolua_function(tolua_S, "getClientPlatformType", tolua_User_Define_Game_GetClientPlatformType00);
    tolua_endmodule(tolua_S);
    
    tolua_cclass(tolua_S,"LogicMan","LogicMan","",NULL);
    tolua_beginmodule(tolua_S,"LogicMan");
    tolua_function(tolua_S, "getInstance", tolua_User_Define_LogicMan_getInstance00);
    tolua_function(tolua_S, "forceUpdateClient", tolua_User_Define_LogicMan_forceUpdateClient00);
    tolua_endmodule(tolua_S);
    
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SlotsSaga (lua_State* tolua_S) {
 return tolua_SlotsSaga_open(tolua_S);
};
#endif

