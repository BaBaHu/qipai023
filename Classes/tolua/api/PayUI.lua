
--------------------------------
-- @module PayUI
-- @extend Ref,IGPExchangeMissionSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PayUI] onGPShaerResult 
-- @param self
-- @param #char szDescription
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] exchange 
-- @param self
-- @param #int item
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] pay 
-- @param self
-- @param #int nBuyType
-- @param #long long lBuyCount
-- @param #unsigned int mPayRMB
-- @param #int nPayType
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] share 
-- @param self
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] onGPExchangeResult 
-- @param self
-- @param #int lResultCode
-- @param #char szDescription
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] payCard 
-- @param self
-- @param #char card
-- @param #char pwd
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] onGPPayCardResult 
-- @param self
-- @param #char szDescription
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] payIpa 
-- @param self
-- @param #char proId
-- @return PayUI#PayUI self (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] create 
-- @param self
-- @param #string strIp
-- @param #int iPort
-- @return PayUI#PayUI ret (return value: PayUI)
        
--------------------------------
-- 
-- @function [parent=#PayUI] PayUI 
-- @param self
-- @return PayUI#PayUI self (return value: PayUI)
        
return nil
