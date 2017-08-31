
--------------------------------
-- @module CustonRoomUI
-- @extend Ref,IGPCustomRoomMissionSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#CustonRoomUI] onGPEnterCustomRoomFailure 
-- @param self
-- @param #int errorCode
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] enterRoom 
-- @param self
-- @param #int iRoomID
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] onGPCreateCustomRoomFailure 
-- @param self
-- @param #int errorCode
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] enterCustomRoom 
-- @param self
-- @param #int iRoomID
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] onGPEnterCustomRoomSuccess 
-- @param self
-- @param #unsigned int dwRoomID
-- @param #tagGameServer server
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] checkAutoEnterCustomGame 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] onGPCreateCustomRoomSuccess 
-- @param self
-- @param #unsigned int dwRoomID
-- @param #tagGameServer server
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] createRoom 
-- @param self
-- @param #int iKindID
-- @param #int cbRound
-- @param #int cbWF
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] create 
-- @param self
-- @param #string strIp
-- @param #int iPort
-- @return CustonRoomUI#CustonRoomUI ret (return value: CustonRoomUI)
        
--------------------------------
-- 
-- @function [parent=#CustonRoomUI] CustonRoomUI 
-- @param self
-- @return CustonRoomUI#CustonRoomUI self (return value: CustonRoomUI)
        
return nil
