
--------------------------------
-- @module BankUI
-- @extend Ref,IGPInsureMissionSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#BankUI] transfer 
-- @param self
-- @param #int nType
-- @param #long long score
-- @param #char szInsurePass
-- @param #char szNickName
-- @param #unsigned char cbByNickName
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] onInsureFailure 
-- @param self
-- @param #int type
-- @param #char szDescription
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] onInsureInfo 
-- @param self
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] onInsureSuccess 
-- @param self
-- @param #int type
-- @param #char szDescription
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] take 
-- @param self
-- @param #long long score
-- @param #char szInsurePass
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] query 
-- @param self
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] save 
-- @param self
-- @param #int value
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] modifyPassword 
-- @param self
-- @param #int nType
-- @param #char szOldPass
-- @param #char szNewPass
-- @return BankUI#BankUI self (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] create 
-- @param self
-- @param #string strIp
-- @param #int iPort
-- @return BankUI#BankUI ret (return value: BankUI)
        
--------------------------------
-- 
-- @function [parent=#BankUI] BankUI 
-- @param self
-- @return BankUI#BankUI self (return value: BankUI)
        
return nil
