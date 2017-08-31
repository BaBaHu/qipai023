
--------------------------------
-- @module LogonUI
-- @extend Ref,IGPLoginMissionSink,IGPMsgMissionSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#LogonUI] onGPNotice 
-- @param self
-- @param #char szDescription
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPLoginFailure 
-- @param self
-- @param #char szDescription
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPLoginComplete 
-- @param self
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] loginByType 
-- @param self
-- @param #int nLoginType
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] getBaseEnsureTake 
-- @param self
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] regist 
-- @param self
-- @param #string strAccount
-- @param #string strPwd
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPMsgError 
-- @param self
-- @param #int errorCode
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPError 
-- @param self
-- @param #int err
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPLoginSuccess 
-- @param self
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] logout 
-- @param self
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] onGPBaseEnsureComplete 
-- @param self
-- @param #bool bSuccessedconst
-- @param #char szDescription
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] login 
-- @param self
-- @param #string strAccount
-- @param #string strPwd
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] create 
-- @param self
-- @param #string strIp
-- @param #int iPort
-- @return LogonUI#LogonUI ret (return value: LogonUI)
        
--------------------------------
-- 
-- @function [parent=#LogonUI] LogonUI 
-- @param self
-- @return LogonUI#LogonUI self (return value: LogonUI)
        
return nil
