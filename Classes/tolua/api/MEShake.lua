
--------------------------------
-- @module MEShake
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#MEShake] stop 
-- @param self
-- @return MEShake#MEShake self (return value: MEShake)
        
--------------------------------
-- 
-- @function [parent=#MEShake] initWithDuration 
-- @param self
-- @param #float d
-- @param #float strength_x
-- @param #float strength_y
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, float, float, float         
-- @overload self, float, float         
-- @function [parent=#MEShake] create
-- @param self
-- @param #float d
-- @param #float strength_x
-- @param #float strength_y
-- @return MEShake#MEShake ret (return value: MEShake)

--------------------------------
-- 
-- @function [parent=#MEShake] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return MEShake#MEShake self (return value: MEShake)
        
--------------------------------
-- 
-- @function [parent=#MEShake] clone 
-- @param self
-- @return MEShake#MEShake ret (return value: MEShake)
        
--------------------------------
-- 
-- @function [parent=#MEShake] reverse 
-- @param self
-- @return MEShake#MEShake ret (return value: MEShake)
        
--------------------------------
-- 
-- @function [parent=#MEShake] update 
-- @param self
-- @param #float time
-- @return MEShake#MEShake self (return value: MEShake)
        
--------------------------------
-- 
-- @function [parent=#MEShake] MEShake 
-- @param self
-- @return MEShake#MEShake self (return value: MEShake)
        
return nil
