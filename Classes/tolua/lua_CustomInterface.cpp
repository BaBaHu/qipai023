/*
** Lua binding: CustomInterface
** Generated automatically by tolua++-1.0.92 on 07/05/16 17:36:25.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CustomInterface_open (lua_State* tolua_S);

#include "lua_CustomInterface.h"
#include "tolua_fix.h"
#include "cocos2d.h"
USING_NS_CC;
#include "MELog.h"
#include "MECallBackListenerHelper.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MECallBackListenerHelper");
 
 tolua_usertype(tolua_S,"MELogUtil");
}

/* method: sharedLogManager of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_sharedLogManager00
static int tolua_CustomInterface_MELogUtil_sharedLogManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MELogUtil* tolua_ret = (MELogUtil*)  MELogUtil::sharedLogManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MELogUtil");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedLogManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCanWriteError of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_setCanWriteError00
static int tolua_CustomInterface_MELogUtil_setCanWriteError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
  bool canW = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCanWriteError'", NULL);
#endif
  {
   self->setCanWriteError(canW);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCanWriteError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCanWriteError of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_getCanWriteError00
static int tolua_CustomInterface_MELogUtil_getCanWriteError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCanWriteError'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCanWriteError();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCanWriteError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCanWriteInfo of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_setCanWriteInfo00
static int tolua_CustomInterface_MELogUtil_setCanWriteInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
  bool canW = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCanWriteInfo'", NULL);
#endif
  {
   self->setCanWriteInfo(canW);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCanWriteInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCanWriteInfo of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_getCanWriteInfo00
static int tolua_CustomInterface_MELogUtil_getCanWriteInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCanWriteInfo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCanWriteInfo();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCanWriteInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCanWriteWarning of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_setCanWriteWarning00
static int tolua_CustomInterface_MELogUtil_setCanWriteWarning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
  bool canW = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCanWriteWarning'", NULL);
#endif
  {
   self->setCanWriteWarning(canW);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCanWriteWarning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCanWriteWarning of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_getCanWriteWarning00
static int tolua_CustomInterface_MELogUtil_getCanWriteWarning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCanWriteWarning'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCanWriteWarning();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCanWriteWarning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLogPath of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_setLogPath00
static int tolua_CustomInterface_MELogUtil_setLogPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
  const char* szPath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLogPath'", NULL);
#endif
  {
   self->setLogPath(szPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLogPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLogPath of class  MELogUtil */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELogUtil_getLogPath00
static int tolua_CustomInterface_MELogUtil_getLogPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MELogUtil",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MELogUtil* self = (MELogUtil*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLogPath'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getLogPath();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLogPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MELOGERROR */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELOGERROR00
static int tolua_CustomInterface_MELOGERROR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   MELOGERROR(msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MELOGERROR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MELOGWARNING */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELOGWARNING00
static int tolua_CustomInterface_MELOGWARNING00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   MELOGWARNING(msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MELOGWARNING'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MELOGINFO */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MELOGINFO00
static int tolua_CustomInterface_MELOGINFO00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   MELOGINFO(msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MELOGINFO'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  MECallBackListenerHelper */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MECallBackListenerHelper_getInstance00
static int tolua_CustomInterface_MECallBackListenerHelper_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MECallBackListenerHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MECallBackListenerHelper* tolua_ret = (MECallBackListenerHelper*)  MECallBackListenerHelper::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MECallBackListenerHelper");
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

/* method: purge of class  MECallBackListenerHelper */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MECallBackListenerHelper_purge00
static int tolua_CustomInterface_MECallBackListenerHelper_purge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MECallBackListenerHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MECallBackListenerHelper::purge();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptCallBackHandler of class  MECallBackListenerHelper */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MECallBackListenerHelper_registerScriptCallBackHandler00
static int tolua_CustomInterface_MECallBackListenerHelper_registerScriptCallBackHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MECallBackListenerHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MECallBackListenerHelper* self = (MECallBackListenerHelper*)  tolua_tousertype(tolua_S,1,0);
  std::string strHandler = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  LUA_FUNCTION luaHanlder = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptCallBackHandler'", NULL);
#endif
  {
   self->registerScriptCallBackHandler(strHandler,luaHanlder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptCallBackHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptCallBackHandler of class  MECallBackListenerHelper */
#ifndef TOLUA_DISABLE_tolua_CustomInterface_MECallBackListenerHelper_unregisterScriptCallBackHandler00
static int tolua_CustomInterface_MECallBackListenerHelper_unregisterScriptCallBackHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MECallBackListenerHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MECallBackListenerHelper* self = (MECallBackListenerHelper*)  tolua_tousertype(tolua_S,1,0);
  std::string strHandler = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptCallBackHandler'", NULL);
#endif
  {
   self->unregisterScriptCallBackHandler(strHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptCallBackHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CustomInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MAX_LOG_LEN",MAX_LOG_LEN);
  tolua_constant(tolua_S,"MELOG_ERROR",MELOG_ERROR);
  tolua_constant(tolua_S,"MELOG_INFO",MELOG_INFO);
  tolua_constant(tolua_S,"MELOG_WARNING",MELOG_WARNING);
  tolua_cclass(tolua_S,"MELogUtil","MELogUtil","",NULL);
  tolua_beginmodule(tolua_S,"MELogUtil");
   tolua_function(tolua_S,"sharedLogManager",tolua_CustomInterface_MELogUtil_sharedLogManager00);
   tolua_function(tolua_S,"setCanWriteError",tolua_CustomInterface_MELogUtil_setCanWriteError00);
   tolua_function(tolua_S,"getCanWriteError",tolua_CustomInterface_MELogUtil_getCanWriteError00);
   tolua_function(tolua_S,"setCanWriteInfo",tolua_CustomInterface_MELogUtil_setCanWriteInfo00);
   tolua_function(tolua_S,"getCanWriteInfo",tolua_CustomInterface_MELogUtil_getCanWriteInfo00);
   tolua_function(tolua_S,"setCanWriteWarning",tolua_CustomInterface_MELogUtil_setCanWriteWarning00);
   tolua_function(tolua_S,"getCanWriteWarning",tolua_CustomInterface_MELogUtil_getCanWriteWarning00);
   tolua_function(tolua_S,"setLogPath",tolua_CustomInterface_MELogUtil_setLogPath00);
   tolua_function(tolua_S,"getLogPath",tolua_CustomInterface_MELogUtil_getLogPath00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"MELOGERROR",tolua_CustomInterface_MELOGERROR00);
  tolua_function(tolua_S,"MELOGWARNING",tolua_CustomInterface_MELOGWARNING00);
  tolua_function(tolua_S,"MELOGINFO",tolua_CustomInterface_MELOGINFO00);
  tolua_cclass(tolua_S,"MECallBackListenerHelper","MECallBackListenerHelper","",NULL);
  tolua_beginmodule(tolua_S,"MECallBackListenerHelper");
   tolua_function(tolua_S,"getInstance",tolua_CustomInterface_MECallBackListenerHelper_getInstance00);
   tolua_function(tolua_S,"purge",tolua_CustomInterface_MECallBackListenerHelper_purge00);
   tolua_function(tolua_S,"registerScriptCallBackHandler",tolua_CustomInterface_MECallBackListenerHelper_registerScriptCallBackHandler00);
   tolua_function(tolua_S,"unregisterScriptCallBackHandler",tolua_CustomInterface_MECallBackListenerHelper_unregisterScriptCallBackHandler00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CustomInterface (lua_State* tolua_S) {
 return tolua_CustomInterface_open(tolua_S);
};
#endif

