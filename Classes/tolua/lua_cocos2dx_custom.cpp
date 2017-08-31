#include "lua_cocos2dx_custom.hpp"
#include "meEngine.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_custom_LogonUI_onGPNotice(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "LogonUI:onGPNotice"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPNotice'", nullptr);
            return 0;
        }
        cobj->onGPNotice(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPNotice",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPLoginFailure(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPLoginFailure'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "LogonUI:onGPLoginFailure"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPLoginFailure'", nullptr);
            return 0;
        }
        cobj->onGPLoginFailure(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPLoginFailure",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPLoginFailure'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPLoginComplete(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPLoginComplete'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPLoginComplete'", nullptr);
            return 0;
        }
        cobj->onGPLoginComplete();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPLoginComplete",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPLoginComplete'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_loginByType(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_loginByType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LogonUI:loginByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_loginByType'", nullptr);
            return 0;
        }
        cobj->loginByType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:loginByType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_loginByType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_getBaseEnsureTake(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_getBaseEnsureTake'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_getBaseEnsureTake'", nullptr);
            return 0;
        }
        cobj->getBaseEnsureTake();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:getBaseEnsureTake",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_getBaseEnsureTake'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_regist(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_regist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LogonUI:regist");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LogonUI:regist");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_regist'", nullptr);
            return 0;
        }
        cobj->regist(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:regist",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_regist'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPMsgError(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPMsgError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LogonUI:onGPMsgError");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPMsgError'", nullptr);
            return 0;
        }
        cobj->onGPMsgError(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPMsgError",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPMsgError'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPError(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LogonUI:onGPError");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPError'", nullptr);
            return 0;
        }
        cobj->onGPError(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPError",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPError'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPLoginSuccess(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPLoginSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPLoginSuccess'", nullptr);
            return 0;
        }
        cobj->onGPLoginSuccess();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPLoginSuccess",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPLoginSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_logout(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_logout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_logout'", nullptr);
            return 0;
        }
        cobj->logout();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:logout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_logout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_onGPBaseEnsureComplete(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_onGPBaseEnsureComplete'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        bool arg0;
        const char* arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "LogonUI:onGPBaseEnsureComplete");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "LogonUI:onGPBaseEnsureComplete"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_onGPBaseEnsureComplete'", nullptr);
            return 0;
        }
        cobj->onGPBaseEnsureComplete(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:onGPBaseEnsureComplete",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_onGPBaseEnsureComplete'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_login(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LogonUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_LogonUI_login'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LogonUI:login");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LogonUI:login");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_login'", nullptr);
            return 0;
        }
        cobj->login(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:login",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_login'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_LogonUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LogonUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LogonUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LogonUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_create'", nullptr);
            return 0;
        }
        LogonUI* ret = LogonUI::create(arg0, arg1);
        object_to_luaval<LogonUI>(tolua_S, "LogonUI",(LogonUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LogonUI:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_LogonUI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    LogonUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_LogonUI_constructor'", nullptr);
            return 0;
        }
        cobj = new LogonUI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"LogonUI");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LogonUI:LogonUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_LogonUI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_LogonUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LogonUI)");
    return 0;
}

int lua_register_cocos2dx_custom_LogonUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"LogonUI");
    tolua_cclass(tolua_S,"LogonUI","LogonUI","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"LogonUI");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_LogonUI_constructor);
        tolua_function(tolua_S,"onGPNotice",lua_cocos2dx_custom_LogonUI_onGPNotice);
        tolua_function(tolua_S,"onGPLoginFailure",lua_cocos2dx_custom_LogonUI_onGPLoginFailure);
        tolua_function(tolua_S,"onGPLoginComplete",lua_cocos2dx_custom_LogonUI_onGPLoginComplete);
        tolua_function(tolua_S,"loginByType",lua_cocos2dx_custom_LogonUI_loginByType);
        tolua_function(tolua_S,"getBaseEnsureTake",lua_cocos2dx_custom_LogonUI_getBaseEnsureTake);
        tolua_function(tolua_S,"regist",lua_cocos2dx_custom_LogonUI_regist);
        tolua_function(tolua_S,"onGPMsgError",lua_cocos2dx_custom_LogonUI_onGPMsgError);
        tolua_function(tolua_S,"onGPError",lua_cocos2dx_custom_LogonUI_onGPError);
        tolua_function(tolua_S,"onGPLoginSuccess",lua_cocos2dx_custom_LogonUI_onGPLoginSuccess);
        tolua_function(tolua_S,"logout",lua_cocos2dx_custom_LogonUI_logout);
        tolua_function(tolua_S,"onGPBaseEnsureComplete",lua_cocos2dx_custom_LogonUI_onGPBaseEnsureComplete);
        tolua_function(tolua_S,"login",lua_cocos2dx_custom_LogonUI_login);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_LogonUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(LogonUI).name();
    g_luaType[typeName] = "LogonUI";
    g_typeCast["LogonUI"] = "LogonUI";
    return 1;
}

int lua_cocos2dx_custom_BankUI_transfer(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_transfer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        int arg0;
        long long arg1;
        const char* arg2;
        const char* arg3;
        uint16_t arg4;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "BankUI:transfer");

        ok &= luaval_to_long_long(tolua_S, 3,&arg1, "BankUI:transfer");

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "BankUI:transfer"); arg2 = arg2_tmp.c_str();

        std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "BankUI:transfer"); arg3 = arg3_tmp.c_str();

        ok &= luaval_to_uint16(tolua_S, 6,&arg4, "BankUI:transfer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_transfer'", nullptr);
            return 0;
        }
        cobj->transfer(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:transfer",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_transfer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_onInsureFailure(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_onInsureFailure'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "BankUI:onInsureFailure");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "BankUI:onInsureFailure"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_onInsureFailure'", nullptr);
            return 0;
        }
        cobj->onInsureFailure(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:onInsureFailure",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_onInsureFailure'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_onInsureInfo(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_onInsureInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_onInsureInfo'", nullptr);
            return 0;
        }
        cobj->onInsureInfo();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:onInsureInfo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_onInsureInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_onInsureSuccess(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_onInsureSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "BankUI:onInsureSuccess");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "BankUI:onInsureSuccess"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_onInsureSuccess'", nullptr);
            return 0;
        }
        cobj->onInsureSuccess(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:onInsureSuccess",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_onInsureSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_take(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_take'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        long long arg0;
        const char* arg1;

        ok &= luaval_to_long_long(tolua_S, 2,&arg0, "BankUI:take");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "BankUI:take"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_take'", nullptr);
            return 0;
        }
        cobj->take(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:take",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_take'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_query(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_query'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_query'", nullptr);
            return 0;
        }
        cobj->query();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:query",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_query'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_save(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_save'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "BankUI:save");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_save'", nullptr);
            return 0;
        }
        cobj->save(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:save",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_save'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_modifyPassword(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BankUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BankUI_modifyPassword'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        const char* arg1;
        const char* arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "BankUI:modifyPassword");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "BankUI:modifyPassword"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "BankUI:modifyPassword"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_modifyPassword'", nullptr);
            return 0;
        }
        cobj->modifyPassword(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:modifyPassword",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_modifyPassword'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BankUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"BankUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "BankUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "BankUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_create'", nullptr);
            return 0;
        }
        BankUI* ret = BankUI::create(arg0, arg1);
        object_to_luaval<BankUI>(tolua_S, "BankUI",(BankUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "BankUI:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_BankUI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    BankUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BankUI_constructor'", nullptr);
            return 0;
        }
        cobj = new BankUI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"BankUI");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "BankUI:BankUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BankUI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_BankUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BankUI)");
    return 0;
}

int lua_register_cocos2dx_custom_BankUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"BankUI");
    tolua_cclass(tolua_S,"BankUI","BankUI","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"BankUI");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_BankUI_constructor);
        tolua_function(tolua_S,"transfer",lua_cocos2dx_custom_BankUI_transfer);
        tolua_function(tolua_S,"onInsureFailure",lua_cocos2dx_custom_BankUI_onInsureFailure);
        tolua_function(tolua_S,"onInsureInfo",lua_cocos2dx_custom_BankUI_onInsureInfo);
        tolua_function(tolua_S,"onInsureSuccess",lua_cocos2dx_custom_BankUI_onInsureSuccess);
        tolua_function(tolua_S,"take",lua_cocos2dx_custom_BankUI_take);
        tolua_function(tolua_S,"query",lua_cocos2dx_custom_BankUI_query);
        tolua_function(tolua_S,"save",lua_cocos2dx_custom_BankUI_save);
        tolua_function(tolua_S,"modifyPassword",lua_cocos2dx_custom_BankUI_modifyPassword);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_BankUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(BankUI).name();
    g_luaType[typeName] = "BankUI";
    g_typeCast["BankUI"] = "BankUI";
    return 1;
}

int lua_cocos2dx_custom_ServerListUI_OnGameItemUpdateFinish(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdateFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdateFinish'", nullptr);
            return 0;
        }
        cobj->OnGameItemUpdateFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameItemUpdateFinish",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdateFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_enterServerRoom(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_enterServerRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ServerListUI:enterServerRoom");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ServerListUI:enterServerRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_enterServerRoom'", nullptr);
            return 0;
        }
        bool ret = cobj->enterServerRoom(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:enterServerRoom",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_enterServerRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_onGameItemFinishNofity(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_onGameItemFinishNofity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0, "ServerListUI:onGameItemFinishNofity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_onGameItemFinishNofity'", nullptr);
            return 0;
        }
        cobj->onGameItemFinishNofity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:onGameItemFinishNofity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_onGameItemFinishNofity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_getServerLists(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_getServerLists'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ServerListUI:getServerLists");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_getServerLists'", nullptr);
            return 0;
        }
        cobj->getServerLists(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:getServerLists",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_getServerLists'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_OnGameItemFinish(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemFinish'", nullptr);
            return 0;
        }
        cobj->OnGameItemFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameItemFinish",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_OnGameKindFinish(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameKindFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned short arg0;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "ServerListUI:OnGameKindFinish");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameKindFinish'", nullptr);
            return 0;
        }
        cobj->OnGameKindFinish(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameKindFinish",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameKindFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_OnGameItemDelete(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemDelete'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        CGameListItem* arg0;

        ok &= luaval_to_object<CGameListItem>(tolua_S, 2, "CGameListItem",&arg0, "ServerListUI:OnGameItemDelete");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemDelete'", nullptr);
            return 0;
        }
        cobj->OnGameItemDelete(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameItemDelete",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemDelete'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_OnGameItemUpdate(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        CGameListItem* arg0;

        ok &= luaval_to_object<CGameListItem>(tolua_S, 2, "CGameListItem",&arg0, "ServerListUI:OnGameItemUpdate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdate'", nullptr);
            return 0;
        }
        cobj->OnGameItemUpdate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameItemUpdate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_OnGameItemInsert(lua_State* tolua_S)
{
    int argc = 0;
    ServerListUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ServerListUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemInsert'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        CGameListItem* arg0;

        ok &= luaval_to_object<CGameListItem>(tolua_S, 2, "CGameListItem",&arg0, "ServerListUI:OnGameItemInsert");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemInsert'", nullptr);
            return 0;
        }
        cobj->OnGameItemInsert(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ServerListUI:OnGameItemInsert",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_OnGameItemInsert'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_ServerListUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ServerListUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ServerListUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ServerListUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ServerListUI_create'", nullptr);
            return 0;
        }
        ServerListUI* ret = ServerListUI::create(arg0, arg1);
        object_to_luaval<ServerListUI>(tolua_S, "ServerListUI",(ServerListUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ServerListUI:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ServerListUI_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_ServerListUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ServerListUI)");
    return 0;
}

int lua_register_cocos2dx_custom_ServerListUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ServerListUI");
    tolua_cclass(tolua_S,"ServerListUI","ServerListUI","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ServerListUI");
        tolua_function(tolua_S,"OnGameItemUpdateFinish",lua_cocos2dx_custom_ServerListUI_OnGameItemUpdateFinish);
        tolua_function(tolua_S,"enterServerRoom",lua_cocos2dx_custom_ServerListUI_enterServerRoom);
        tolua_function(tolua_S,"onGameItemFinishNofity",lua_cocos2dx_custom_ServerListUI_onGameItemFinishNofity);
        tolua_function(tolua_S,"getServerLists",lua_cocos2dx_custom_ServerListUI_getServerLists);
        tolua_function(tolua_S,"OnGameItemFinish",lua_cocos2dx_custom_ServerListUI_OnGameItemFinish);
        tolua_function(tolua_S,"OnGameKindFinish",lua_cocos2dx_custom_ServerListUI_OnGameKindFinish);
        tolua_function(tolua_S,"OnGameItemDelete",lua_cocos2dx_custom_ServerListUI_OnGameItemDelete);
        tolua_function(tolua_S,"OnGameItemUpdate",lua_cocos2dx_custom_ServerListUI_OnGameItemUpdate);
        tolua_function(tolua_S,"OnGameItemInsert",lua_cocos2dx_custom_ServerListUI_OnGameItemInsert);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_ServerListUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ServerListUI).name();
    g_luaType[typeName] = "ServerListUI";
    g_typeCast["ServerListUI"] = "ServerListUI";
    return 1;
}

int lua_cocos2dx_custom_MENetUtil_GetCardPip(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:GetCardPip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetCardPip'", nullptr);
            return 0;
        }
        int ret = MENetUtil::GetCardPip(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetCardPip",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetCardPip'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_operatePai(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:operatePai");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:operatePai");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_operatePai'", nullptr);
            return 0;
        }
        MENetUtil::operatePai(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:operatePai",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_operatePai'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_GetAreaTotalScore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:GetAreaTotalScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetAreaTotalScore'", nullptr);
            return 0;
        }
        unsigned int ret = MENetUtil::GetAreaTotalScore(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetAreaTotalScore",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetAreaTotalScore'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setGameClock(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:setGameClock");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:setGameClock");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MENetUtil:setGameClock");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setGameClock'", nullptr);
            return 0;
        }
        MENetUtil::setGameClock(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setGameClock",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setGameClock'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_chuPai(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:chuPai");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_chuPai'", nullptr);
            return 0;
        }
        MENetUtil::chuPai(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:chuPai",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_chuPai'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserNameByID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:getUserNameByID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserNameByID'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getUserNameByID(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserNameByID",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserNameByID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getFaceID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getFaceID'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getFaceID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getFaceID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getFaceID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getSex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getSex'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getSex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getSex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getSex'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_ready(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_ready'", nullptr);
            return 0;
        }
        MENetUtil::ready();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:ready",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_ready'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserGold'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getUserGold();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserGold",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_changePai(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:changePai");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:changePai");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MENetUtil:changePai");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_changePai'", nullptr);
            return 0;
        }
        MENetUtil::changePai(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:changePai",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_changePai'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getRoomGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getRoomGold'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getRoomGold();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getRoomGold",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getRoomGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setUserGoldOrRoomCard(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        long long arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:setUserGoldOrRoomCard");
        ok &= luaval_to_long_long(tolua_S, 3,&arg1, "MENetUtil:setUserGoldOrRoomCard");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setUserGoldOrRoomCard'", nullptr);
            return 0;
        }
        int ret = MENetUtil::setUserGoldOrRoomCard(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setUserGoldOrRoomCard",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setUserGoldOrRoomCard'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getCustomRoomID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getCustomRoomID'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getCustomRoomID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getCustomRoomID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getCustomRoomID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_selectPai(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:selectPai");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_selectPai'", nullptr);
            return 0;
        }
        MENetUtil::selectPai(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:selectPai",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_selectPai'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_GetMaxPlayerScore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:GetMaxPlayerScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetMaxPlayerScore'", nullptr);
            return 0;
        }
        unsigned int ret = MENetUtil::GetMaxPlayerScore(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetMaxPlayerScore",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetMaxPlayerScore'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserDailiOrder(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserDailiOrder'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getUserDailiOrder();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserDailiOrder",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserDailiOrder'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_dismisCustomServer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "MENetUtil:dismisCustomServer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServer'", nullptr);
            return 0;
        }
        MENetUtil::dismisCustomServer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:dismisCustomServer",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServer'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getCurBanker(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getCurBanker'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getCurBanker();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getCurBanker",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getCurBanker'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_playChat(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:playChat");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:playChat");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MENetUtil:playChat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_playChat'", nullptr);
            return 0;
        }
        MENetUtil::playChat(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:playChat",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_playChat'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_playTalk(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        const char* arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:playTalk");
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MENetUtil:playTalk"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_playTalk'", nullptr);
            return 0;
        }
        MENetUtil::playTalk(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:playTalk",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_playTalk'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_leaveGame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_leaveGame'", nullptr);
            return 0;
        }
        MENetUtil::leaveGame();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:leaveGame",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_leaveGame'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        int arg1;
        int arg2;
        const char* arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:init");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:init");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MENetUtil:init");
        std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "MENetUtil:init"); arg3 = arg3_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_init'", nullptr);
            return 0;
        }
        bool ret = MENetUtil::init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:init",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_init'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getNickName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getNickName'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getNickName();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getNickName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getNickName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_startTalk(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_startTalk'", nullptr);
            return 0;
        }
        MENetUtil::startTalk();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:startTalk",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_startTalk'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setDizhu(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:setDizhu");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setDizhu'", nullptr);
            return 0;
        }
        MENetUtil::setDizhu(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setDizhu",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setDizhu'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserIconUrl(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserIconUrl'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getUserIconUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserIconUrl",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserIconUrl'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_enterGame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_enterGame'", nullptr);
            return 0;
        }
        MENetUtil::enterGame();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:enterGame",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_enterGame'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getTableGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:getTableGold");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:getTableGold");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getTableGold'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getTableGold(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getTableGold",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getTableGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getGameID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getGameID'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getGameID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getGameID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getGameID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getPassword(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getPassword'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getPassword();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getPassword",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getPassword'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getChairID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getChairID'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getChairID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getChairID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getChairID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_admitDefeat(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_admitDefeat'", nullptr);
            return 0;
        }
        MENetUtil::admitDefeat();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:admitDefeat",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_admitDefeat'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getBankPassword(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getBankPassword'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getBankPassword();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getBankPassword",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getBankPassword'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_dismisCustomServerVote(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:dismisCustomServerVote");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServerVote'", nullptr);
            return 0;
        }
        MENetUtil::dismisCustomServerVote(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:dismisCustomServerVote",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServerVote'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_GetAreaPlayerScore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:GetAreaPlayerScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetAreaPlayerScore'", nullptr);
            return 0;
        }
        unsigned int ret = MENetUtil::GetAreaPlayerScore(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetAreaPlayerScore",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetAreaPlayerScore'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_isCustomServer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_isCustomServer'", nullptr);
            return 0;
        }
        bool ret = MENetUtil::isCustomServer();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:isCustomServer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_isCustomServer'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_adminCmd(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:adminCmd");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_adminCmd'", nullptr);
            return 0;
        }
        MENetUtil::adminCmd(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:adminCmd",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_adminCmd'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_isGamePlaying(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_isGamePlaying'", nullptr);
            return 0;
        }
        bool ret = MENetUtil::isGamePlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:isGamePlaying",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_isGamePlaying'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_endTalk(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "MENetUtil:endTalk");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_endTalk'", nullptr);
            return 0;
        }
        MENetUtil::endTalk(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:endTalk",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_endTalk'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_GetPlayerFreeScore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetPlayerFreeScore'", nullptr);
            return 0;
        }
        unsigned int ret = MENetUtil::GetPlayerFreeScore();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetPlayerFreeScore",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetPlayerFreeScore'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_autoJoin(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_autoJoin'", nullptr);
            return 0;
        }
        MENetUtil::autoJoin();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:autoJoin",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_autoJoin'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_checkNetWork(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_checkNetWork'", nullptr);
            return 0;
        }
        bool ret = MENetUtil::checkNetWork();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:checkNetWork",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_checkNetWork'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_applyBanker(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_applyBanker'", nullptr);
            return 0;
        }
        MENetUtil::applyBanker();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:applyBanker",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_applyBanker'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getEncryptPassword(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MENetUtil:getEncryptPassword"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getEncryptPassword'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getEncryptPassword(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getEncryptPassword",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getEncryptPassword'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserTypeByChair(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:getUserTypeByChair");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserTypeByChair'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getUserTypeByChair(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserTypeByChair",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserTypeByChair'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_logoutGame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_logoutGame'", nullptr);
            return 0;
        }
        MENetUtil::logoutGame();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:logoutGame",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_logoutGame'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getBet(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getBet'", nullptr);
            return 0;
        }
        MENetUtil::getBet();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getBet",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getBet'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setGameOffline(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setGameOffline'", nullptr);
            return 0;
        }
        MENetUtil::setGameOffline();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setGameOffline",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setGameOffline'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserIconUrlByChair(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:getUserIconUrlByChair");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserIconUrlByChair'", nullptr);
            return 0;
        }
        const char* ret = MENetUtil::getUserIconUrlByChair(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserIconUrlByChair",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserIconUrlByChair'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setGameEnterBackground(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "MENetUtil:setGameEnterBackground");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setGameEnterBackground'", nullptr);
            return 0;
        }
        MENetUtil::setGameEnterBackground(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setGameEnterBackground",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setGameEnterBackground'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserType'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getUserType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserType",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_exitGameRoom(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_exitGameRoom'", nullptr);
            return 0;
        }
        bool ret = MENetUtil::exitGameRoom();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:exitGameRoom",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_exitGameRoom'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_dismisCustomServerStartVote(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServerStartVote'", nullptr);
            return 0;
        }
        MENetUtil::dismisCustomServerStartVote();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:dismisCustomServerStartVote",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_dismisCustomServerStartVote'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_clearGameClock(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:clearGameClock");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_clearGameClock'", nullptr);
            return 0;
        }
        MENetUtil::clearGameClock(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:clearGameClock",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_clearGameClock'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setEnableGameClock(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "MENetUtil:setEnableGameClock");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setEnableGameClock'", nullptr);
            return 0;
        }
        MENetUtil::setEnableGameClock(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setEnableGameClock",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setEnableGameClock'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getUserID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getUserID'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getUserID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getUserID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getUserID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_setTrustee(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "MENetUtil:setTrustee");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_setTrustee'", nullptr);
            return 0;
        }
        MENetUtil::setTrustee(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:setTrustee",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_setTrustee'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_cancelBanker(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_cancelBanker'", nullptr);
            return 0;
        }
        MENetUtil::cancelBanker();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:cancelBanker",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_cancelBanker'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getTableMinGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getTableMinGold'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getTableMinGold();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getTableMinGold",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getTableMinGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_getBankGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_getBankGold'", nullptr);
            return 0;
        }
        int ret = MENetUtil::getBankGold();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:getBankGold",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_getBankGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_GetGameCurState(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_GetGameCurState'", nullptr);
            return 0;
        }
        int ret = MENetUtil::GetGameCurState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:GetGameCurState",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_GetGameCurState'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MENetUtil_placeBet(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MENetUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MENetUtil:placeBet");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MENetUtil:placeBet");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MENetUtil_placeBet'", nullptr);
            return 0;
        }
        MENetUtil::placeBet(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MENetUtil:placeBet",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MENetUtil_placeBet'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_MENetUtil_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MENetUtil)");
    return 0;
}

int lua_register_cocos2dx_custom_MENetUtil(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MENetUtil");
    tolua_cclass(tolua_S,"MENetUtil","MENetUtil","",nullptr);

    tolua_beginmodule(tolua_S,"MENetUtil");
        tolua_function(tolua_S,"GetCardPip", lua_cocos2dx_custom_MENetUtil_GetCardPip);
        tolua_function(tolua_S,"operatePai", lua_cocos2dx_custom_MENetUtil_operatePai);
        tolua_function(tolua_S,"GetAreaTotalScore", lua_cocos2dx_custom_MENetUtil_GetAreaTotalScore);
        tolua_function(tolua_S,"setGameClock", lua_cocos2dx_custom_MENetUtil_setGameClock);
        tolua_function(tolua_S,"chuPai", lua_cocos2dx_custom_MENetUtil_chuPai);
        tolua_function(tolua_S,"getUserNameByID", lua_cocos2dx_custom_MENetUtil_getUserNameByID);
        tolua_function(tolua_S,"getFaceID", lua_cocos2dx_custom_MENetUtil_getFaceID);
        tolua_function(tolua_S,"getSex", lua_cocos2dx_custom_MENetUtil_getSex);
        tolua_function(tolua_S,"ready", lua_cocos2dx_custom_MENetUtil_ready);
        tolua_function(tolua_S,"getUserGold", lua_cocos2dx_custom_MENetUtil_getUserGold);
        tolua_function(tolua_S,"changePai", lua_cocos2dx_custom_MENetUtil_changePai);
        tolua_function(tolua_S,"getRoomGold", lua_cocos2dx_custom_MENetUtil_getRoomGold);
        tolua_function(tolua_S,"setUserGoldOrRoomCard", lua_cocos2dx_custom_MENetUtil_setUserGoldOrRoomCard);
        tolua_function(tolua_S,"getCustomRoomID", lua_cocos2dx_custom_MENetUtil_getCustomRoomID);
        tolua_function(tolua_S,"selectPai", lua_cocos2dx_custom_MENetUtil_selectPai);
        tolua_function(tolua_S,"GetMaxPlayerScore", lua_cocos2dx_custom_MENetUtil_GetMaxPlayerScore);
        tolua_function(tolua_S,"getUserDailiOrder", lua_cocos2dx_custom_MENetUtil_getUserDailiOrder);
        tolua_function(tolua_S,"dismisCustomServer", lua_cocos2dx_custom_MENetUtil_dismisCustomServer);
        tolua_function(tolua_S,"getCurBanker", lua_cocos2dx_custom_MENetUtil_getCurBanker);
        tolua_function(tolua_S,"playChat", lua_cocos2dx_custom_MENetUtil_playChat);
        tolua_function(tolua_S,"playTalk", lua_cocos2dx_custom_MENetUtil_playTalk);
        tolua_function(tolua_S,"leaveGame", lua_cocos2dx_custom_MENetUtil_leaveGame);
        tolua_function(tolua_S,"init", lua_cocos2dx_custom_MENetUtil_init);
        tolua_function(tolua_S,"getNickName", lua_cocos2dx_custom_MENetUtil_getNickName);
        tolua_function(tolua_S,"startTalk", lua_cocos2dx_custom_MENetUtil_startTalk);
        tolua_function(tolua_S,"setDizhu", lua_cocos2dx_custom_MENetUtil_setDizhu);
        tolua_function(tolua_S,"getUserIconUrl", lua_cocos2dx_custom_MENetUtil_getUserIconUrl);
        tolua_function(tolua_S,"enterGame", lua_cocos2dx_custom_MENetUtil_enterGame);
        tolua_function(tolua_S,"getTableGold", lua_cocos2dx_custom_MENetUtil_getTableGold);
        tolua_function(tolua_S,"getGameID", lua_cocos2dx_custom_MENetUtil_getGameID);
        tolua_function(tolua_S,"getPassword", lua_cocos2dx_custom_MENetUtil_getPassword);
        tolua_function(tolua_S,"getChairID", lua_cocos2dx_custom_MENetUtil_getChairID);
        tolua_function(tolua_S,"admitDefeat", lua_cocos2dx_custom_MENetUtil_admitDefeat);
        tolua_function(tolua_S,"getBankPassword", lua_cocos2dx_custom_MENetUtil_getBankPassword);
        tolua_function(tolua_S,"dismisCustomServerVote", lua_cocos2dx_custom_MENetUtil_dismisCustomServerVote);
        tolua_function(tolua_S,"GetAreaPlayerScore", lua_cocos2dx_custom_MENetUtil_GetAreaPlayerScore);
        tolua_function(tolua_S,"isCustomServer", lua_cocos2dx_custom_MENetUtil_isCustomServer);
        tolua_function(tolua_S,"adminCmd", lua_cocos2dx_custom_MENetUtil_adminCmd);
        tolua_function(tolua_S,"isGamePlaying", lua_cocos2dx_custom_MENetUtil_isGamePlaying);
        tolua_function(tolua_S,"endTalk", lua_cocos2dx_custom_MENetUtil_endTalk);
        tolua_function(tolua_S,"GetPlayerFreeScore", lua_cocos2dx_custom_MENetUtil_GetPlayerFreeScore);
        tolua_function(tolua_S,"autoJoin", lua_cocos2dx_custom_MENetUtil_autoJoin);
        tolua_function(tolua_S,"checkNetWork", lua_cocos2dx_custom_MENetUtil_checkNetWork);
        tolua_function(tolua_S,"applyBanker", lua_cocos2dx_custom_MENetUtil_applyBanker);
        tolua_function(tolua_S,"getEncryptPassword", lua_cocos2dx_custom_MENetUtil_getEncryptPassword);
        tolua_function(tolua_S,"getUserTypeByChair", lua_cocos2dx_custom_MENetUtil_getUserTypeByChair);
        tolua_function(tolua_S,"logoutGame", lua_cocos2dx_custom_MENetUtil_logoutGame);
        tolua_function(tolua_S,"getBet", lua_cocos2dx_custom_MENetUtil_getBet);
        tolua_function(tolua_S,"setGameOffline", lua_cocos2dx_custom_MENetUtil_setGameOffline);
        tolua_function(tolua_S,"getUserIconUrlByChair", lua_cocos2dx_custom_MENetUtil_getUserIconUrlByChair);
        tolua_function(tolua_S,"setGameEnterBackground", lua_cocos2dx_custom_MENetUtil_setGameEnterBackground);
        tolua_function(tolua_S,"getUserType", lua_cocos2dx_custom_MENetUtil_getUserType);
        tolua_function(tolua_S,"exitGameRoom", lua_cocos2dx_custom_MENetUtil_exitGameRoom);
        tolua_function(tolua_S,"dismisCustomServerStartVote", lua_cocos2dx_custom_MENetUtil_dismisCustomServerStartVote);
        tolua_function(tolua_S,"clearGameClock", lua_cocos2dx_custom_MENetUtil_clearGameClock);
        tolua_function(tolua_S,"setEnableGameClock", lua_cocos2dx_custom_MENetUtil_setEnableGameClock);
        tolua_function(tolua_S,"getUserID", lua_cocos2dx_custom_MENetUtil_getUserID);
        tolua_function(tolua_S,"setTrustee", lua_cocos2dx_custom_MENetUtil_setTrustee);
        tolua_function(tolua_S,"cancelBanker", lua_cocos2dx_custom_MENetUtil_cancelBanker);
        tolua_function(tolua_S,"getTableMinGold", lua_cocos2dx_custom_MENetUtil_getTableMinGold);
        tolua_function(tolua_S,"getBankGold", lua_cocos2dx_custom_MENetUtil_getBankGold);
        tolua_function(tolua_S,"GetGameCurState", lua_cocos2dx_custom_MENetUtil_GetGameCurState);
        tolua_function(tolua_S,"placeBet", lua_cocos2dx_custom_MENetUtil_placeBet);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MENetUtil).name();
    g_luaType[typeName] = "MENetUtil";
    g_typeCast["MENetUtil"] = "MENetUtil";
    return 1;
}

int lua_cocos2dx_custom_TableUI_setTableScrollOffset(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_setTableScrollOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "TableUI:setTableScrollOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_setTableScrollOffset'", nullptr);
            return 0;
        }
        cobj->setTableScrollOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:setTableScrollOffset",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_setTableScrollOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_onEnter(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_onEnter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_onEnter'", nullptr);
            return 0;
        }
        cobj->onEnter();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:onEnter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_onEnter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_onExit(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_onExit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_onExit'", nullptr);
            return 0;
        }
        cobj->onExit();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:onExit",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_onExit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_cellSizeForTable(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_cellSizeForTable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::TableView* arg0;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:cellSizeForTable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_cellSizeForTable'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->cellSizeForTable(arg0);
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:cellSizeForTable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_cellSizeForTable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_scrollViewDidScroll(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_scrollViewDidScroll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::ScrollView* arg0;

        ok &= luaval_to_object<cocos2d::extension::ScrollView>(tolua_S, 2, "cc.ScrollView",&arg0, "TableUI:scrollViewDidScroll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_scrollViewDidScroll'", nullptr);
            return 0;
        }
        cobj->scrollViewDidScroll(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:scrollViewDidScroll",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_scrollViewDidScroll'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellSizeForIndex(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellSizeForIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellSizeForIndex");

        ok &= luaval_to_ssize(tolua_S, 3, &arg1, "TableUI:tableCellSizeForIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellSizeForIndex'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->tableCellSizeForIndex(arg0, arg1);
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellSizeForIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellSizeForIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_getTableScrollOffset(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_getTableScrollOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_getTableScrollOffset'", nullptr);
            return 0;
        }
        cobj->getTableScrollOffset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:getTableScrollOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_getTableScrollOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_scrollViewDidZoom(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_scrollViewDidZoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::ScrollView* arg0;

        ok &= luaval_to_object<cocos2d::extension::ScrollView>(tolua_S, 2, "cc.ScrollView",&arg0, "TableUI:scrollViewDidZoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_scrollViewDidZoom'", nullptr);
            return 0;
        }
        cobj->scrollViewDidZoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:scrollViewDidZoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_scrollViewDidZoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellAtIndex");

        ok &= luaval_to_ssize(tolua_S, 3, &arg1, "TableUI:tableCellAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellAtIndex'", nullptr);
            return 0;
        }
        cocos2d::extension::TableViewCell* ret = cobj->tableCellAtIndex(arg0, arg1);
        object_to_luaval<cocos2d::extension::TableViewCell>(tolua_S, "cc.TableViewCell",(cocos2d::extension::TableViewCell*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellAtIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_setChairIcon(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_setChairIcon'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        const char* arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "TableUI:setChairIcon");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "TableUI:setChairIcon");

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "TableUI:setChairIcon"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_setChairIcon'", nullptr);
            return 0;
        }
        cobj->setChairIcon(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:setChairIcon",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_setChairIcon'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_numberOfCellsInTableView(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_numberOfCellsInTableView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::TableView* arg0;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:numberOfCellsInTableView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_numberOfCellsInTableView'", nullptr);
            return 0;
        }
        ssize_t ret = cobj->numberOfCellsInTableView(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:numberOfCellsInTableView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_numberOfCellsInTableView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellTouched(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellTouched'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        cocos2d::extension::TableViewCell* arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellTouched");

        ok &= luaval_to_object<cocos2d::extension::TableViewCell>(tolua_S, 3, "cc.TableViewCell",&arg1, "TableUI:tableCellTouched");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellTouched'", nullptr);
            return 0;
        }
        cobj->tableCellTouched(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellTouched",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellTouched'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellWillRecycle(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellWillRecycle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        cocos2d::extension::TableViewCell* arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellWillRecycle");

        ok &= luaval_to_object<cocos2d::extension::TableViewCell>(tolua_S, 3, "cc.TableViewCell",&arg1, "TableUI:tableCellWillRecycle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellWillRecycle'", nullptr);
            return 0;
        }
        cobj->tableCellWillRecycle(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellWillRecycle",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellWillRecycle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_backToServerListScene(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_backToServerListScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_backToServerListScene'", nullptr);
            return 0;
        }
        cobj->backToServerListScene();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:backToServerListScene",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_backToServerListScene'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellHighlight(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellHighlight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        cocos2d::extension::TableViewCell* arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellHighlight");

        ok &= luaval_to_object<cocos2d::extension::TableViewCell>(tolua_S, 3, "cc.TableViewCell",&arg1, "TableUI:tableCellHighlight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellHighlight'", nullptr);
            return 0;
        }
        cobj->tableCellHighlight(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellHighlight",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellHighlight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_onEnterTransitionDidFinish(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_onEnterTransitionDidFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_onEnterTransitionDidFinish'", nullptr);
            return 0;
        }
        cobj->onEnterTransitionDidFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:onEnterTransitionDidFinish",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_onEnterTransitionDidFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_tableCellUnhighlight(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (TableUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_TableUI_tableCellUnhighlight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::extension::TableView* arg0;
        cocos2d::extension::TableViewCell* arg1;

        ok &= luaval_to_object<cocos2d::extension::TableView>(tolua_S, 2, "cc.TableView",&arg0, "TableUI:tableCellUnhighlight");

        ok &= luaval_to_object<cocos2d::extension::TableViewCell>(tolua_S, 3, "cc.TableViewCell",&arg1, "TableUI:tableCellUnhighlight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_tableCellUnhighlight'", nullptr);
            return 0;
        }
        cobj->tableCellUnhighlight(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:tableCellUnhighlight",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_tableCellUnhighlight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_TableUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"TableUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "TableUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "TableUI:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "TableUI:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "TableUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_create'", nullptr);
            return 0;
        }
        TableUI* ret = TableUI::create(arg0, arg1, arg2, arg3);
        object_to_luaval<TableUI>(tolua_S, "TableUI",(TableUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "TableUI:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_TableUI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    TableUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_TableUI_constructor'", nullptr);
            return 0;
        }
        cobj = new TableUI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"TableUI");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "TableUI:TableUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_TableUI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_TableUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TableUI)");
    return 0;
}

int lua_register_cocos2dx_custom_TableUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"TableUI");
    tolua_cclass(tolua_S,"TableUI","TableUI","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"TableUI");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_TableUI_constructor);
        tolua_function(tolua_S,"setTableScrollOffset",lua_cocos2dx_custom_TableUI_setTableScrollOffset);
        tolua_function(tolua_S,"onEnter",lua_cocos2dx_custom_TableUI_onEnter);
        tolua_function(tolua_S,"onExit",lua_cocos2dx_custom_TableUI_onExit);
        tolua_function(tolua_S,"cellSizeForTable",lua_cocos2dx_custom_TableUI_cellSizeForTable);
        tolua_function(tolua_S,"scrollViewDidScroll",lua_cocos2dx_custom_TableUI_scrollViewDidScroll);
        tolua_function(tolua_S,"tableCellSizeForIndex",lua_cocos2dx_custom_TableUI_tableCellSizeForIndex);
        tolua_function(tolua_S,"getTableScrollOffset",lua_cocos2dx_custom_TableUI_getTableScrollOffset);
        tolua_function(tolua_S,"scrollViewDidZoom",lua_cocos2dx_custom_TableUI_scrollViewDidZoom);
        tolua_function(tolua_S,"tableCellAtIndex",lua_cocos2dx_custom_TableUI_tableCellAtIndex);
        tolua_function(tolua_S,"setChairIcon",lua_cocos2dx_custom_TableUI_setChairIcon);
        tolua_function(tolua_S,"numberOfCellsInTableView",lua_cocos2dx_custom_TableUI_numberOfCellsInTableView);
        tolua_function(tolua_S,"tableCellTouched",lua_cocos2dx_custom_TableUI_tableCellTouched);
        tolua_function(tolua_S,"tableCellWillRecycle",lua_cocos2dx_custom_TableUI_tableCellWillRecycle);
        tolua_function(tolua_S,"backToServerListScene",lua_cocos2dx_custom_TableUI_backToServerListScene);
        tolua_function(tolua_S,"tableCellHighlight",lua_cocos2dx_custom_TableUI_tableCellHighlight);
        tolua_function(tolua_S,"onEnterTransitionDidFinish",lua_cocos2dx_custom_TableUI_onEnterTransitionDidFinish);
        tolua_function(tolua_S,"tableCellUnhighlight",lua_cocos2dx_custom_TableUI_tableCellUnhighlight);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_TableUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(TableUI).name();
    g_luaType[typeName] = "TableUI";
    g_typeCast["TableUI"] = "TableUI";
    return 1;
}

int lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomFailure(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomFailure'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CustonRoomUI:onGPEnterCustomRoomFailure");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomFailure'", nullptr);
            return 0;
        }
        cobj->onGPEnterCustomRoomFailure(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:onGPEnterCustomRoomFailure",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomFailure'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_enterRoom(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_enterRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CustonRoomUI:enterRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_enterRoom'", nullptr);
            return 0;
        }
        cobj->enterRoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:enterRoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_enterRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomFailure(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomFailure'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CustonRoomUI:onGPCreateCustomRoomFailure");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomFailure'", nullptr);
            return 0;
        }
        cobj->onGPCreateCustomRoomFailure(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:onGPCreateCustomRoomFailure",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomFailure'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_enterCustomRoom(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_enterCustomRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CustonRoomUI:enterCustomRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_enterCustomRoom'", nullptr);
            return 0;
        }
        cobj->enterCustomRoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:enterCustomRoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_enterCustomRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomSuccess(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        tagGameServer arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "CustonRoomUI:onGPEnterCustomRoomSuccess");

        #pragma warning NO CONVERSION TO NATIVE FOR tagGameServer
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomSuccess'", nullptr);
            return 0;
        }
        cobj->onGPEnterCustomRoomSuccess(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:onGPEnterCustomRoomSuccess",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_checkAutoEnterCustomGame(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_checkAutoEnterCustomGame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_checkAutoEnterCustomGame'", nullptr);
            return 0;
        }
        bool ret = cobj->checkAutoEnterCustomGame();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:checkAutoEnterCustomGame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_checkAutoEnterCustomGame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomSuccess(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        tagGameServer arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "CustonRoomUI:onGPCreateCustomRoomSuccess");

        #pragma warning NO CONVERSION TO NATIVE FOR tagGameServer
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomSuccess'", nullptr);
            return 0;
        }
        cobj->onGPCreateCustomRoomSuccess(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:onGPCreateCustomRoomSuccess",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_createRoom(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CustonRoomUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CustonRoomUI_createRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CustonRoomUI:createRoom");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CustonRoomUI:createRoom");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "CustonRoomUI:createRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_createRoom'", nullptr);
            return 0;
        }
        cobj->createRoom(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:createRoom",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_createRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CustonRoomUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "CustonRoomUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CustonRoomUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_create'", nullptr);
            return 0;
        }
        CustonRoomUI* ret = CustonRoomUI::create(arg0, arg1);
        object_to_luaval<CustonRoomUI>(tolua_S, "CustonRoomUI",(CustonRoomUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CustonRoomUI:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_CustonRoomUI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    CustonRoomUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CustonRoomUI_constructor'", nullptr);
            return 0;
        }
        cobj = new CustonRoomUI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CustonRoomUI");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CustonRoomUI:CustonRoomUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CustonRoomUI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_CustonRoomUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CustonRoomUI)");
    return 0;
}

int lua_register_cocos2dx_custom_CustonRoomUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CustonRoomUI");
    tolua_cclass(tolua_S,"CustonRoomUI","CustonRoomUI","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CustonRoomUI");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_CustonRoomUI_constructor);
        tolua_function(tolua_S,"onGPEnterCustomRoomFailure",lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomFailure);
        tolua_function(tolua_S,"enterRoom",lua_cocos2dx_custom_CustonRoomUI_enterRoom);
        tolua_function(tolua_S,"onGPCreateCustomRoomFailure",lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomFailure);
        tolua_function(tolua_S,"enterCustomRoom",lua_cocos2dx_custom_CustonRoomUI_enterCustomRoom);
        tolua_function(tolua_S,"onGPEnterCustomRoomSuccess",lua_cocos2dx_custom_CustonRoomUI_onGPEnterCustomRoomSuccess);
        tolua_function(tolua_S,"checkAutoEnterCustomGame",lua_cocos2dx_custom_CustonRoomUI_checkAutoEnterCustomGame);
        tolua_function(tolua_S,"onGPCreateCustomRoomSuccess",lua_cocos2dx_custom_CustonRoomUI_onGPCreateCustomRoomSuccess);
        tolua_function(tolua_S,"createRoom",lua_cocos2dx_custom_CustonRoomUI_createRoom);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_CustonRoomUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(CustonRoomUI).name();
    g_luaType[typeName] = "CustonRoomUI";
    g_typeCast["CustonRoomUI"] = "CustonRoomUI";
    return 1;
}

int lua_cocos2dx_custom_PayUI_onGPShaerResult(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_onGPShaerResult'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "PayUI:onGPShaerResult"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_onGPShaerResult'", nullptr);
            return 0;
        }
        cobj->onGPShaerResult(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:onGPShaerResult",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_onGPShaerResult'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_exchange(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_exchange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "PayUI:exchange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_exchange'", nullptr);
            return 0;
        }
        cobj->exchange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:exchange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_exchange'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_pay(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_pay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        long long arg1;
        unsigned int arg2;
        int arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "PayUI:pay");

        ok &= luaval_to_long_long(tolua_S, 3,&arg1, "PayUI:pay");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "PayUI:pay");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "PayUI:pay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_pay'", nullptr);
            return 0;
        }
        cobj->pay(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:pay",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_pay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_share(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_share'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_share'", nullptr);
            return 0;
        }
        cobj->share();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:share",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_share'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_onGPExchangeResult(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_onGPExchangeResult'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "PayUI:onGPExchangeResult");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "PayUI:onGPExchangeResult"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_onGPExchangeResult'", nullptr);
            return 0;
        }
        cobj->onGPExchangeResult(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:onGPExchangeResult",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_onGPExchangeResult'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_payCard(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_payCard'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "PayUI:payCard"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "PayUI:payCard"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_payCard'", nullptr);
            return 0;
        }
        cobj->payCard(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:payCard",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_payCard'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_onGPPayCardResult(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_onGPPayCardResult'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "PayUI:onGPPayCardResult"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_onGPPayCardResult'", nullptr);
            return 0;
        }
        cobj->onGPPayCardResult(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:onGPPayCardResult",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_onGPPayCardResult'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_payIpa(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PayUI*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_PayUI_payIpa'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "PayUI:payIpa"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_payIpa'", nullptr);
            return 0;
        }
        cobj->payIpa(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:payIpa",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_payIpa'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_PayUI_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"PayUI",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "PayUI:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "PayUI:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_create'", nullptr);
            return 0;
        }
        PayUI* ret = PayUI::create(arg0, arg1);
        object_to_luaval<PayUI>(tolua_S, "PayUI",(PayUI*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "PayUI:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_PayUI_constructor(lua_State* tolua_S)
{
    int argc = 0;
    PayUI* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_PayUI_constructor'", nullptr);
            return 0;
        }
        cobj = new PayUI();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"PayUI");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PayUI:PayUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_PayUI_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_PayUI_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PayUI)");
    return 0;
}

int lua_register_cocos2dx_custom_PayUI(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"PayUI");
    tolua_cclass(tolua_S,"PayUI","PayUI","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"PayUI");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_PayUI_constructor);
        tolua_function(tolua_S,"onGPShaerResult",lua_cocos2dx_custom_PayUI_onGPShaerResult);
        tolua_function(tolua_S,"exchange",lua_cocos2dx_custom_PayUI_exchange);
        tolua_function(tolua_S,"pay",lua_cocos2dx_custom_PayUI_pay);
        tolua_function(tolua_S,"share",lua_cocos2dx_custom_PayUI_share);
        tolua_function(tolua_S,"onGPExchangeResult",lua_cocos2dx_custom_PayUI_onGPExchangeResult);
        tolua_function(tolua_S,"payCard",lua_cocos2dx_custom_PayUI_payCard);
        tolua_function(tolua_S,"onGPPayCardResult",lua_cocos2dx_custom_PayUI_onGPPayCardResult);
        tolua_function(tolua_S,"payIpa",lua_cocos2dx_custom_PayUI_payIpa);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_PayUI_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(PayUI).name();
    g_luaType[typeName] = "PayUI";
    g_typeCast["PayUI"] = "PayUI";
    return 1;
}

int lua_cocos2dx_custom_CGDialogManager_PerformOkAction(lua_State* tolua_S)
{
    int argc = 0;
    CGDialogManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CGDialogManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CGDialogManager_PerformOkAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CGDialogManager:PerformOkAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_PerformOkAction'", nullptr);
            return 0;
        }
        bool ret = cobj->PerformOkAction(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CGDialogManager:PerformOkAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_PerformOkAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_RemoveDialog(lua_State* tolua_S)
{
    int argc = 0;
    CGDialogManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CGDialogManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CGDialogManager_RemoveDialog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CGDialogManager:RemoveDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_RemoveDialog'", nullptr);
            return 0;
        }
        bool ret = cobj->RemoveDialog(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CGDialogManager:RemoveDialog",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_RemoveDialog'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_AddDialog(lua_State* tolua_S)
{
    int argc = 0;
    CGDialogManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CGDialogManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CGDialogManager_AddDialog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        CGDialog* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CGDialogManager:AddDialog");

        ok &= luaval_to_object<CGDialog>(tolua_S, 3, "CGDialog",&arg1, "CGDialogManager:AddDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_AddDialog'", nullptr);
            return 0;
        }
        bool ret = cobj->AddDialog(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CGDialogManager:AddDialog",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_AddDialog'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_PerformCancelAction(lua_State* tolua_S)
{
    int argc = 0;
    CGDialogManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CGDialogManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CGDialogManager_PerformCancelAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CGDialogManager:PerformCancelAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_PerformCancelAction'", nullptr);
            return 0;
        }
        bool ret = cobj->PerformCancelAction(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CGDialogManager:PerformCancelAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_PerformCancelAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_GetDialgID(lua_State* tolua_S)
{
    int argc = 0;
    CGDialogManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CGDialogManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_CGDialogManager_GetDialgID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_GetDialgID'", nullptr);
            return 0;
        }
        int ret = cobj->GetDialgID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CGDialogManager:GetDialgID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_GetDialgID'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_purge(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_purge'", nullptr);
            return 0;
        }
        CGDialogManager::purge();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CGDialogManager:purge",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_purge'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_CGDialogManager_shared(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CGDialogManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_CGDialogManager_shared'", nullptr);
            return 0;
        }
        CGDialogManager* ret = CGDialogManager::shared();
        object_to_luaval<CGDialogManager>(tolua_S, "CGDialogManager",(CGDialogManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CGDialogManager:shared",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_CGDialogManager_shared'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_CGDialogManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CGDialogManager)");
    return 0;
}

int lua_register_cocos2dx_custom_CGDialogManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CGDialogManager");
    tolua_cclass(tolua_S,"CGDialogManager","CGDialogManager","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CGDialogManager");
        tolua_function(tolua_S,"PerformOkAction",lua_cocos2dx_custom_CGDialogManager_PerformOkAction);
        tolua_function(tolua_S,"RemoveDialog",lua_cocos2dx_custom_CGDialogManager_RemoveDialog);
        tolua_function(tolua_S,"AddDialog",lua_cocos2dx_custom_CGDialogManager_AddDialog);
        tolua_function(tolua_S,"PerformCancelAction",lua_cocos2dx_custom_CGDialogManager_PerformCancelAction);
        tolua_function(tolua_S,"GetDialgID",lua_cocos2dx_custom_CGDialogManager_GetDialgID);
        tolua_function(tolua_S,"purge", lua_cocos2dx_custom_CGDialogManager_purge);
        tolua_function(tolua_S,"shared", lua_cocos2dx_custom_CGDialogManager_shared);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(CGDialogManager).name();
    g_luaType[typeName] = "CGDialogManager";
    g_typeCast["CGDialogManager"] = "CGDialogManager";
    return 1;
}

int lua_cocos2dx_custom_MEFileUtil_createDir(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEFileUtil:createDir");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_createDir'", nullptr);
            return 0;
        }
        int ret = MEFileUtil::createDir(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:createDir",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_createDir'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_existFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEFileUtil:existFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_existFile'", nullptr);
            return 0;
        }
        bool ret = MEFileUtil::existFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:existFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_existFile'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_getFileLength(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEFileUtil:getFileLength");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_getFileLength'", nullptr);
            return 0;
        }
        int ret = MEFileUtil::getFileLength(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:getFileLength",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_getFileLength'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_checkSpritePixel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        std::string arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFileUtil:checkSpritePixel");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFileUtil:checkSpritePixel");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "MEFileUtil:checkSpritePixel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_checkSpritePixel'", nullptr);
            return 0;
        }
        bool ret = MEFileUtil::checkSpritePixel(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:checkSpritePixel",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_checkSpritePixel'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_getLogValue(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFileUtil:getLogValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_getLogValue'", nullptr);
            return 0;
        }
        int ret = MEFileUtil::getLogValue(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:getLogValue",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_getLogValue'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_destroyDirectory(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEFileUtil:destroyDirectory");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_destroyDirectory'", nullptr);
            return 0;
        }
        MEFileUtil::destroyDirectory(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:destroyDirectory",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_destroyDirectory'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_IsValidRight(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFileUtil:IsValidRight");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFileUtil:IsValidRight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_IsValidRight'", nullptr);
            return 0;
        }
        bool ret = MEFileUtil::IsValidRight(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:IsValidRight",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_IsValidRight'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFileUtil_createDirectory(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFileUtil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEFileUtil:createDirectory");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFileUtil_createDirectory'", nullptr);
            return 0;
        }
        bool ret = MEFileUtil::createDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFileUtil:createDirectory",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFileUtil_createDirectory'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_MEFileUtil_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEFileUtil)");
    return 0;
}

int lua_register_cocos2dx_custom_MEFileUtil(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEFileUtil");
    tolua_cclass(tolua_S,"MEFileUtil","MEFileUtil","",nullptr);

    tolua_beginmodule(tolua_S,"MEFileUtil");
        tolua_function(tolua_S,"createDir", lua_cocos2dx_custom_MEFileUtil_createDir);
        tolua_function(tolua_S,"existFile", lua_cocos2dx_custom_MEFileUtil_existFile);
        tolua_function(tolua_S,"getFileLength", lua_cocos2dx_custom_MEFileUtil_getFileLength);
        tolua_function(tolua_S,"checkSpritePixel", lua_cocos2dx_custom_MEFileUtil_checkSpritePixel);
        tolua_function(tolua_S,"getLogValue", lua_cocos2dx_custom_MEFileUtil_getLogValue);
        tolua_function(tolua_S,"destroyDirectory", lua_cocos2dx_custom_MEFileUtil_destroyDirectory);
        tolua_function(tolua_S,"IsValidRight", lua_cocos2dx_custom_MEFileUtil_IsValidRight);
        tolua_function(tolua_S,"createDirectory", lua_cocos2dx_custom_MEFileUtil_createDirectory);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEFileUtil).name();
    g_luaType[typeName] = "MEFileUtil";
    g_typeCast["MEFileUtil"] = "MEFileUtil";
    return 1;
}

int lua_cocos2dx_custom_METimeUtils_clock(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"METimeUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_METimeUtils_clock'", nullptr);
            return 0;
        }
        double ret = METimeUtils::clock();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "METimeUtils:clock",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_METimeUtils_clock'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_METimeUtils_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (METimeUtils)");
    return 0;
}

int lua_register_cocos2dx_custom_METimeUtils(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"METimeUtils");
    tolua_cclass(tolua_S,"METimeUtils","METimeUtils","",nullptr);

    tolua_beginmodule(tolua_S,"METimeUtils");
        tolua_function(tolua_S,"clock", lua_cocos2dx_custom_METimeUtils_clock);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(METimeUtils).name();
    g_luaType[typeName] = "METimeUtils";
    g_typeCast["METimeUtils"] = "METimeUtils";
    return 1;
}

int lua_cocos2dx_custom_MEShake_stop(lua_State* tolua_S)
{
    int argc = 0;
    MEShake* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEShake",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEShake*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEShake_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEShake_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEShake:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEShake_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEShake_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    MEShake* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEShake",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEShake*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEShake_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        double arg1;
        double arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "MEShake:initWithDuration");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "MEShake:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "MEShake:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEShake_initWithDuration'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithDuration(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEShake:initWithDuration",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEShake_initWithDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEShake_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEShake",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "MEShake:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "MEShake:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "MEShake:create");
            if (!ok) { break; }
            MEShake* ret = MEShake::create(arg0, arg1, arg2);
            object_to_luaval<MEShake>(tolua_S, "MEShake",(MEShake*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "MEShake:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "MEShake:create");
            if (!ok) { break; }
            MEShake* ret = MEShake::create(arg0, arg1);
            object_to_luaval<MEShake>(tolua_S, "MEShake",(MEShake*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "MEShake:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEShake_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEShake_constructor(lua_State* tolua_S)
{
    int argc = 0;
    MEShake* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEShake_constructor'", nullptr);
            return 0;
        }
        cobj = new MEShake();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MEShake");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEShake:MEShake",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEShake_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_MEShake_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEShake)");
    return 0;
}

int lua_register_cocos2dx_custom_MEShake(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEShake");
    tolua_cclass(tolua_S,"MEShake","MEShake","cc.ActionInterval",nullptr);

    tolua_beginmodule(tolua_S,"MEShake");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_MEShake_constructor);
        tolua_function(tolua_S,"stop",lua_cocos2dx_custom_MEShake_stop);
        tolua_function(tolua_S,"initWithDuration",lua_cocos2dx_custom_MEShake_initWithDuration);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_MEShake_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEShake).name();
    g_luaType[typeName] = "MEShake";
    g_typeCast["MEShake"] = "MEShake";
    return 1;
}

int lua_cocos2dx_custom_MEResolution_setResolutionRect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEResolution",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEResolution:setResolutionRect");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEResolution:setResolutionRect");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MEResolution:setResolutionRect");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "MEResolution:setResolutionRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEResolution_setResolutionRect'", nullptr);
            return 0;
        }
        MEResolution::setResolutionRect(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEResolution:setResolutionRect",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEResolution_setResolutionRect'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEResolution_setDefaultRect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEResolution",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEResolution_setDefaultRect'", nullptr);
            return 0;
        }
        MEResolution::setDefaultRect();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEResolution:setDefaultRect",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEResolution_setDefaultRect'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_MEResolution_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEResolution)");
    return 0;
}

int lua_register_cocos2dx_custom_MEResolution(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEResolution");
    tolua_cclass(tolua_S,"MEResolution","MEResolution","",nullptr);

    tolua_beginmodule(tolua_S,"MEResolution");
        tolua_function(tolua_S,"setResolutionRect", lua_cocos2dx_custom_MEResolution_setResolutionRect);
        tolua_function(tolua_S,"setDefaultRect", lua_cocos2dx_custom_MEResolution_setDefaultRect);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEResolution).name();
    g_luaType[typeName] = "MEResolution";
    g_typeCast["MEResolution"] = "MEResolution";
    return 1;
}

int lua_cocos2dx_custom_MEUpdateEngine_setPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setPackageUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setPackageUrl'", nullptr);
            return 0;
        }
        cobj->setPackageUrl(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setPackageUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getDownPackageStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getDownPackageStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getDownPackageStoragePath'", nullptr);
            return 0;
        }
        const char* ret = cobj->getDownPackageStoragePath();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getDownPackageStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getDownPackageStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersionFileUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getVersionFileUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getVersionFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "MEUpdateEngine:setConnectionTimeout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setConnectionTimeout'", nullptr);
            return 0;
        }
        cobj->setConnectionTimeout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setConnectionTimeout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setVersion(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setVersion"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersion'", nullptr);
            return 0;
        }
        cobj->setVersion(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getBaseVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersionFileUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getBaseVersionFileUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getBaseVersionFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_checkUpdate(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_checkUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_checkUpdate'", nullptr);
            return 0;
        }
        bool ret = cobj->checkUpdate();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:checkUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_checkUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setBaseVersion(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setBaseVersion"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersion'", nullptr);
            return 0;
        }
        cobj->setBaseVersion(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setBaseVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getConnectionTimeout'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getConnectionTimeout();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getConnectionTimeout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setStoragePath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setStoragePath'", nullptr);
            return 0;
        }
        cobj->setStoragePath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setStoragePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getStoragePath'", nullptr);
            return 0;
        }
        const char* ret = cobj->getStoragePath();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_update(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_update'", nullptr);
            return 0;
        }
        cobj->update();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:update",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getBaseVersion(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getBaseVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getBaseVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getBaseVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setVersionFileUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersionFileUrl'", nullptr);
            return 0;
        }
        cobj->setVersionFileUrl(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setVersionFileUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setDelegate(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        MEUpdateManagerDelegateProtocol* arg0;

        ok &= luaval_to_object<MEUpdateManagerDelegateProtocol>(tolua_S, 2, "MEUpdateManagerDelegateProtocol",&arg0, "MEUpdateEngine:setDelegate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setDelegate'", nullptr);
            return 0;
        }
        cobj->setDelegate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setDelegate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_isDownpackage(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_isDownpackage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_isDownpackage'", nullptr);
            return 0;
        }
        bool ret = cobj->isDownpackage();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:isDownpackage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_isDownpackage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getDelegate(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getDelegate'", nullptr);
            return 0;
        }
        MEUpdateManagerDelegateProtocol* ret = cobj->getDelegate();
        object_to_luaval<MEUpdateManagerDelegateProtocol>(tolua_S, "MEUpdateManagerDelegateProtocol",(MEUpdateManagerDelegateProtocol*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_checkBaseVersion(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_checkBaseVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_checkBaseVersion'", nullptr);
            return 0;
        }
        bool ret = cobj->checkBaseVersion();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:checkBaseVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_checkBaseVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_setBaseVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:setBaseVersionFileUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersionFileUrl'", nullptr);
            return 0;
        }
        cobj->setBaseVersionFileUrl(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:setBaseVersionFileUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_setBaseVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_getPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEUpdateEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEUpdateEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEUpdateEngine_getPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_getPackageUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPackageUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:getPackageUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_getPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEUpdateEngine_constructor(lua_State* tolua_S)
{
    int argc = 0;
    MEUpdateEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_constructor'", nullptr);
            return 0;
        }
        cobj = new MEUpdateEngine();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MEUpdateEngine");
        return 1;
    }
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:MEUpdateEngine"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_constructor'", nullptr);
            return 0;
        }
        cobj = new MEUpdateEngine(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MEUpdateEngine");
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:MEUpdateEngine"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MEUpdateEngine:MEUpdateEngine"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_constructor'", nullptr);
            return 0;
        }
        cobj = new MEUpdateEngine(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MEUpdateEngine");
        return 1;
    }
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEUpdateEngine:MEUpdateEngine"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MEUpdateEngine:MEUpdateEngine"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "MEUpdateEngine:MEUpdateEngine"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEUpdateEngine_constructor'", nullptr);
            return 0;
        }
        cobj = new MEUpdateEngine(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MEUpdateEngine");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEUpdateEngine:MEUpdateEngine",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEUpdateEngine_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_MEUpdateEngine_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEUpdateEngine)");
    return 0;
}

int lua_register_cocos2dx_custom_MEUpdateEngine(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEUpdateEngine");
    tolua_cclass(tolua_S,"MEUpdateEngine","MEUpdateEngine","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"MEUpdateEngine");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_MEUpdateEngine_constructor);
        tolua_function(tolua_S,"setPackageUrl",lua_cocos2dx_custom_MEUpdateEngine_setPackageUrl);
        tolua_function(tolua_S,"getDownPackageStoragePath",lua_cocos2dx_custom_MEUpdateEngine_getDownPackageStoragePath);
        tolua_function(tolua_S,"getVersionFileUrl",lua_cocos2dx_custom_MEUpdateEngine_getVersionFileUrl);
        tolua_function(tolua_S,"setConnectionTimeout",lua_cocos2dx_custom_MEUpdateEngine_setConnectionTimeout);
        tolua_function(tolua_S,"setVersion",lua_cocos2dx_custom_MEUpdateEngine_setVersion);
        tolua_function(tolua_S,"getBaseVersionFileUrl",lua_cocos2dx_custom_MEUpdateEngine_getBaseVersionFileUrl);
        tolua_function(tolua_S,"checkUpdate",lua_cocos2dx_custom_MEUpdateEngine_checkUpdate);
        tolua_function(tolua_S,"setBaseVersion",lua_cocos2dx_custom_MEUpdateEngine_setBaseVersion);
        tolua_function(tolua_S,"getConnectionTimeout",lua_cocos2dx_custom_MEUpdateEngine_getConnectionTimeout);
        tolua_function(tolua_S,"setStoragePath",lua_cocos2dx_custom_MEUpdateEngine_setStoragePath);
        tolua_function(tolua_S,"getStoragePath",lua_cocos2dx_custom_MEUpdateEngine_getStoragePath);
        tolua_function(tolua_S,"update",lua_cocos2dx_custom_MEUpdateEngine_update);
        tolua_function(tolua_S,"getBaseVersion",lua_cocos2dx_custom_MEUpdateEngine_getBaseVersion);
        tolua_function(tolua_S,"setVersionFileUrl",lua_cocos2dx_custom_MEUpdateEngine_setVersionFileUrl);
        tolua_function(tolua_S,"setDelegate",lua_cocos2dx_custom_MEUpdateEngine_setDelegate);
        tolua_function(tolua_S,"isDownpackage",lua_cocos2dx_custom_MEUpdateEngine_isDownpackage);
        tolua_function(tolua_S,"getVersion",lua_cocos2dx_custom_MEUpdateEngine_getVersion);
        tolua_function(tolua_S,"getDelegate",lua_cocos2dx_custom_MEUpdateEngine_getDelegate);
        tolua_function(tolua_S,"checkBaseVersion",lua_cocos2dx_custom_MEUpdateEngine_checkBaseVersion);
        tolua_function(tolua_S,"setBaseVersionFileUrl",lua_cocos2dx_custom_MEUpdateEngine_setBaseVersionFileUrl);
        tolua_function(tolua_S,"getPackageUrl",lua_cocos2dx_custom_MEUpdateEngine_getPackageUrl);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEUpdateEngine).name();
    g_luaType[typeName] = "MEUpdateEngine";
    g_typeCast["MEUpdateEngine"] = "MEUpdateEngine";
    return 1;
}

int lua_cocos2dx_custom_MEFvMask_HasAny(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:HasAny");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:HasAny");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_HasAny'", nullptr);
            return 0;
        }
        bool ret = MEFvMask::HasAny(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:HasAny",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_HasAny'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_IsAdd(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:IsAdd");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:IsAdd");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MEFvMask:IsAdd");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_IsAdd'", nullptr);
            return 0;
        }
        int ret = MEFvMask::IsAdd(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:IsAdd",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_IsAdd'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_Mask(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:Mask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_Mask'", nullptr);
            return 0;
        }
        int ret = MEFvMask::Mask(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:Mask",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_Mask'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_Remove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:Remove");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:Remove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_Remove'", nullptr);
            return 0;
        }
        int ret = MEFvMask::Remove(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:Remove",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_Remove'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_HasAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:HasAll");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:HasAll");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_HasAll'", nullptr);
            return 0;
        }
        bool ret = MEFvMask::HasAll(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:HasAll",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_HasAll'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_Add(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:Add");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:Add");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_Add'", nullptr);
            return 0;
        }
        int ret = MEFvMask::Add(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:Add",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_Add'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_Del(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:Del");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:Del");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_Del'", nullptr);
            return 0;
        }
        int ret = MEFvMask::Del(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:Del",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_Del'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEFvMask_IsDel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEFvMask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEFvMask:IsDel");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEFvMask:IsDel");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "MEFvMask:IsDel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEFvMask_IsDel'", nullptr);
            return 0;
        }
        int ret = MEFvMask::IsDel(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEFvMask:IsDel",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEFvMask_IsDel'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_MEFvMask_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEFvMask)");
    return 0;
}

int lua_register_cocos2dx_custom_MEFvMask(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEFvMask");
    tolua_cclass(tolua_S,"MEFvMask","MEFvMask","",nullptr);

    tolua_beginmodule(tolua_S,"MEFvMask");
        tolua_function(tolua_S,"HasAny", lua_cocos2dx_custom_MEFvMask_HasAny);
        tolua_function(tolua_S,"IsAdd", lua_cocos2dx_custom_MEFvMask_IsAdd);
        tolua_function(tolua_S,"Mask", lua_cocos2dx_custom_MEFvMask_Mask);
        tolua_function(tolua_S,"Remove", lua_cocos2dx_custom_MEFvMask_Remove);
        tolua_function(tolua_S,"HasAll", lua_cocos2dx_custom_MEFvMask_HasAll);
        tolua_function(tolua_S,"Add", lua_cocos2dx_custom_MEFvMask_Add);
        tolua_function(tolua_S,"Del", lua_cocos2dx_custom_MEFvMask_Del);
        tolua_function(tolua_S,"IsDel", lua_cocos2dx_custom_MEFvMask_IsDel);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEFvMask).name();
    g_luaType[typeName] = "MEFvMask";
    g_typeCast["MEFvMask"] = "MEFvMask";
    return 1;
}

int lua_cocos2dx_custom_MEImageDownloader_downImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MEImageDownloader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MEImageDownloader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MEImageDownloader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEImageDownloader_downImage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.MEImageDownloader:downImage");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.MEImageDownloader:downImage");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "cc.MEImageDownloader:downImage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEImageDownloader_downImage'", nullptr);
            return 0;
        }
        cobj->downImage(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MEImageDownloader:downImage",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEImageDownloader_downImage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEImageDownloader_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MEImageDownloader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.MEImageDownloader:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEImageDownloader_create'", nullptr);
            return 0;
        }
        cocos2d::MEImageDownloader* ret = cocos2d::MEImageDownloader::create(arg0);
        object_to_luaval<cocos2d::MEImageDownloader>(tolua_S, "cc.MEImageDownloader",(cocos2d::MEImageDownloader*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MEImageDownloader:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEImageDownloader_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEImageDownloader_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MEImageDownloader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.MEImageDownloader:MEImageDownloader");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEImageDownloader_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MEImageDownloader(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MEImageDownloader");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MEImageDownloader:MEImageDownloader",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEImageDownloader_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_MEImageDownloader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEImageDownloader)");
    return 0;
}

int lua_register_cocos2dx_custom_MEImageDownloader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.MEImageDownloader");
    tolua_cclass(tolua_S,"MEImageDownloader","cc.MEImageDownloader","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"MEImageDownloader");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_MEImageDownloader_constructor);
        tolua_function(tolua_S,"downImage",lua_cocos2dx_custom_MEImageDownloader_downImage);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_MEImageDownloader_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::MEImageDownloader).name();
    g_luaType[typeName] = "cc.MEImageDownloader";
    g_typeCast["MEImageDownloader"] = "cc.MEImageDownloader";
    return 1;
}

int lua_cocos2dx_custom_MEWeiXinHelper_wxPay(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:wxPay"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MEWeiXinHelper:wxPay"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPay'", nullptr);
            return 0;
        }
        cobj->wxPay(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:wxPay",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_shareUrlWX(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareUrlWX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        int arg3;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:shareUrlWX"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MEWeiXinHelper:shareUrlWX"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "MEWeiXinHelper:shareUrlWX"); arg2 = arg2_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "MEWeiXinHelper:shareUrlWX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareUrlWX'", nullptr);
            return 0;
        }
        cobj->shareUrlWX(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:shareUrlWX",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareUrlWX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onApplyPayResultState(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onApplyPayResultState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEWeiXinHelper:onApplyPayResultState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onApplyPayResultState'", nullptr);
            return 0;
        }
        cobj->onApplyPayResultState(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onApplyPayResultState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onApplyPayResultState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_applyPay(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:applyPay"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MEWeiXinHelper:applyPay"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "MEWeiXinHelper:applyPay"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPay'", nullptr);
            return 0;
        }
        cobj->applyPay(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:applyPay",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_applyPayByOrder(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPayByOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:applyPayByOrder"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPayByOrder'", nullptr);
            return 0;
        }
        cobj->applyPayByOrder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:applyPayByOrder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_applyPayByOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_showWebView(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_showWebView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:showWebView"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_showWebView'", nullptr);
            return 0;
        }
        cobj->showWebView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:showWebView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_showWebView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_getLoginInfoByType(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_getLoginInfoByType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEWeiXinHelper:getLoginInfoByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_getLoginInfoByType'", nullptr);
            return 0;
        }
        WxUserInfo& ret = cobj->getLoginInfoByType(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR WxUserInfo;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:getLoginInfoByType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_getLoginInfoByType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_shareImageWX(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareImageWX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:shareImageWX"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEWeiXinHelper:shareImageWX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareImageWX'", nullptr);
            return 0;
        }
        cobj->shareImageWX(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:shareImageWX",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareImageWX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_shareTextWX(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareTextWX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:shareTextWX"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "MEWeiXinHelper:shareTextWX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareTextWX'", nullptr);
            return 0;
        }
        cobj->shareTextWX(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:shareTextWX",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_shareTextWX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_wxlogin(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxlogin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxlogin'", nullptr);
            return 0;
        }
        cobj->wxlogin();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:wxlogin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxlogin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_qqlogin(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogin'", nullptr);
            return 0;
        }
        cobj->qqlogin();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:qqlogin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_qqlogout(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogout'", nullptr);
            return 0;
        }
        cobj->qqlogout();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:qqlogout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_qqlogout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onQQLoginSuccess(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onQQLoginSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEWeiXinHelper:onQQLoginSuccess");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onQQLoginSuccess'", nullptr);
            return 0;
        }
        cobj->onQQLoginSuccess(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onQQLoginSuccess",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onQQLoginSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_wxPayByOrder(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPayByOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "MEWeiXinHelper:wxPayByOrder"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPayByOrder'", nullptr);
            return 0;
        }
        cobj->wxPayByOrder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:wxPayByOrder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_wxPayByOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginFail(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginFail'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "MEWeiXinHelper:onWxLoginFail");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginFail'", nullptr);
            return 0;
        }
        cobj->onWxLoginFail(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onWxLoginFail",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginFail'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onWxPayResultState(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxPayResultState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEWeiXinHelper:onWxPayResultState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxPayResultState'", nullptr);
            return 0;
        }
        cobj->onWxPayResultState(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onWxPayResultState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxPayResultState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginSuccess(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginSuccess'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        WxUserInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR WxUserInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginSuccess'", nullptr);
            return 0;
        }
        cobj->onWxLoginSuccess(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onWxLoginSuccess",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginSuccess'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_onWxShareResultState(lua_State* tolua_S)
{
    int argc = 0;
    MEWeiXinHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MEWeiXinHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxShareResultState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MEWeiXinHelper:onWxShareResultState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxShareResultState'", nullptr);
            return 0;
        }
        cobj->onWxShareResultState(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MEWeiXinHelper:onWxShareResultState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_onWxShareResultState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_purge(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_purge'", nullptr);
            return 0;
        }
        MEWeiXinHelper::purge();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEWeiXinHelper:purge",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_purge'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_MEWeiXinHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MEWeiXinHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_MEWeiXinHelper_getInstance'", nullptr);
            return 0;
        }
        MEWeiXinHelper* ret = MEWeiXinHelper::getInstance();
        object_to_luaval<MEWeiXinHelper>(tolua_S, "MEWeiXinHelper",(MEWeiXinHelper*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MEWeiXinHelper:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_MEWeiXinHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_MEWeiXinHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MEWeiXinHelper)");
    return 0;
}

int lua_register_cocos2dx_custom_MEWeiXinHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MEWeiXinHelper");
    tolua_cclass(tolua_S,"MEWeiXinHelper","MEWeiXinHelper","IWeiXinMissionSink",nullptr);

    tolua_beginmodule(tolua_S,"MEWeiXinHelper");
        tolua_function(tolua_S,"wxPay",lua_cocos2dx_custom_MEWeiXinHelper_wxPay);
        tolua_function(tolua_S,"shareUrlWX",lua_cocos2dx_custom_MEWeiXinHelper_shareUrlWX);
        tolua_function(tolua_S,"onApplyPayResultState",lua_cocos2dx_custom_MEWeiXinHelper_onApplyPayResultState);
        tolua_function(tolua_S,"applyPay",lua_cocos2dx_custom_MEWeiXinHelper_applyPay);
        tolua_function(tolua_S,"applyPayByOrder",lua_cocos2dx_custom_MEWeiXinHelper_applyPayByOrder);
        tolua_function(tolua_S,"showWebView",lua_cocos2dx_custom_MEWeiXinHelper_showWebView);
        tolua_function(tolua_S,"getLoginInfoByType",lua_cocos2dx_custom_MEWeiXinHelper_getLoginInfoByType);
        tolua_function(tolua_S,"shareImageWX",lua_cocos2dx_custom_MEWeiXinHelper_shareImageWX);
        tolua_function(tolua_S,"shareTextWX",lua_cocos2dx_custom_MEWeiXinHelper_shareTextWX);
        tolua_function(tolua_S,"wxlogin",lua_cocos2dx_custom_MEWeiXinHelper_wxlogin);
        tolua_function(tolua_S,"qqlogin",lua_cocos2dx_custom_MEWeiXinHelper_qqlogin);
        tolua_function(tolua_S,"qqlogout",lua_cocos2dx_custom_MEWeiXinHelper_qqlogout);
        tolua_function(tolua_S,"onQQLoginSuccess",lua_cocos2dx_custom_MEWeiXinHelper_onQQLoginSuccess);
        tolua_function(tolua_S,"wxPayByOrder",lua_cocos2dx_custom_MEWeiXinHelper_wxPayByOrder);
        tolua_function(tolua_S,"onWxLoginFail",lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginFail);
        tolua_function(tolua_S,"onWxPayResultState",lua_cocos2dx_custom_MEWeiXinHelper_onWxPayResultState);
        tolua_function(tolua_S,"onWxLoginSuccess",lua_cocos2dx_custom_MEWeiXinHelper_onWxLoginSuccess);
        tolua_function(tolua_S,"onWxShareResultState",lua_cocos2dx_custom_MEWeiXinHelper_onWxShareResultState);
        tolua_function(tolua_S,"purge", lua_cocos2dx_custom_MEWeiXinHelper_purge);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_custom_MEWeiXinHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MEWeiXinHelper).name();
    g_luaType[typeName] = "MEWeiXinHelper";
    g_typeCast["MEWeiXinHelper"] = "MEWeiXinHelper";
    return 1;
}
TOLUA_API int register_all_cocos2dx_custom(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_custom_CustonRoomUI(tolua_S);
	lua_register_cocos2dx_custom_MEResolution(tolua_S);
	lua_register_cocos2dx_custom_LogonUI(tolua_S);
	lua_register_cocos2dx_custom_MENetUtil(tolua_S);
	lua_register_cocos2dx_custom_METimeUtils(tolua_S);
	lua_register_cocos2dx_custom_MEImageDownloader(tolua_S);
	lua_register_cocos2dx_custom_MEUpdateEngine(tolua_S);
	lua_register_cocos2dx_custom_MEShake(tolua_S);
	lua_register_cocos2dx_custom_CGDialogManager(tolua_S);
	lua_register_cocos2dx_custom_MEWeiXinHelper(tolua_S);
	lua_register_cocos2dx_custom_MEFvMask(tolua_S);
	lua_register_cocos2dx_custom_TableUI(tolua_S);
	lua_register_cocos2dx_custom_PayUI(tolua_S);
	lua_register_cocos2dx_custom_BankUI(tolua_S);
	lua_register_cocos2dx_custom_ServerListUI(tolua_S);
	lua_register_cocos2dx_custom_MEFileUtil(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

