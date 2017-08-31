
--------------------------------
-- @module MEWeiXinHelper
-- @extend IWeiXinMissionSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] wxPay 
-- @param self
-- @param #char body
-- @param #char price
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] shareUrlWX 
-- @param self
-- @param #char kUrl
-- @param #char kTitle
-- @param #char kDesc
-- @param #int nType
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onApplyPayResultState 
-- @param self
-- @param #int iCode
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] applyPay 
-- @param self
-- @param #char subject
-- @param #char body
-- @param #char price
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] applyPayByOrder 
-- @param self
-- @param #char order
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] showWebView 
-- @param self
-- @param #char kUrl
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] getLoginInfoByType 
-- @param self
-- @param #int nType
-- @return WxUserInfo#WxUserInfo ret (return value: WxUserInfo)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] shareImageWX 
-- @param self
-- @param #char ImgPath
-- @param #int nType
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] shareTextWX 
-- @param self
-- @param #char kText
-- @param #int nType
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] wxlogin 
-- @param self
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] qqlogin 
-- @param self
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] qqlogout 
-- @param self
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onQQLoginSuccess 
-- @param self
-- @param #string param
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] wxPayByOrder 
-- @param self
-- @param #char order
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onWxLoginFail 
-- @param self
-- @param #string kError
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onWxPayResultState 
-- @param self
-- @param #int iCode
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onWxLoginSuccess 
-- @param self
-- @param #WxUserInfo kWxUserInfo
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] onWxShareResultState 
-- @param self
-- @param #int iCode
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] purge 
-- @param self
-- @return MEWeiXinHelper#MEWeiXinHelper self (return value: MEWeiXinHelper)
        
--------------------------------
-- 
-- @function [parent=#MEWeiXinHelper] getInstance 
-- @param self
-- @return MEWeiXinHelper#MEWeiXinHelper ret (return value: MEWeiXinHelper)
        
return nil
