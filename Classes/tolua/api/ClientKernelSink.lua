
--------------------------------
-- @module ClientKernelSink
-- @extend Ref,IClientKernelSink
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ClientKernelSink] operatePai 
-- @param self
-- @param #int nOperateCode
-- @param #int idxPai
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFTableMessage 
-- @param self
-- @param #char szMessage
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFGlobalMessage 
-- @param self
-- @param #char szMessage
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] setGameClock 
-- @param self
-- @param #int wChairID
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] chuPai 
-- @param self
-- @param #int idxPai
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventGameClockKill 
-- @param self
-- @param #unsigned short wChairID
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] GetGlobalMessage 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] ready 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFWaitTips 
-- @param self
-- @param #bool bWait
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFMatchInfo 
-- @param self
-- @param #tagMatchInfo pMatchInfo
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserScore 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventGameClockInfo 
-- @param self
-- @param #unsigned short wChairID
-- @param #unsigned int nElapse
-- @param #unsigned short wClockID
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFNoticeMessage 
-- @param self
-- @param #char szMessage
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] leaveGame 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] SetupGameClient 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserClock 
-- @param self
-- @param #unsigned short wChairID
-- @param #unsigned short wUserClock
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] ResetGameClient 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFMatchWaitTips 
-- @param self
-- @param #tagMatchWaitTip pMatchWaitTip
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] setDizhu 
-- @param self
-- @param #int nDizhu
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnGFMatchResult 
-- @param self
-- @param #tagMatchResult pMatchResult
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] enterGame 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserStatus 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] CloseGameClient 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] admitDefeat 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserEnter 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserLeave 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] getTableMinGold 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventUserAttrib 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] setTrustee 
-- @param self
-- @param #bool Trustee
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] OnEventCustomFace 
-- @param self
-- @param #IClientUserItem pIClientUserItem
-- @param #bool bLookonUser
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] Release 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] GetInstance 
-- @param self
-- @return ClientKernelSink#ClientKernelSink ret (return value: ClientKernelSink)
        
--------------------------------
-- 
-- @function [parent=#ClientKernelSink] ClientKernelSink 
-- @param self
-- @return ClientKernelSink#ClientKernelSink self (return value: ClientKernelSink)
        
return nil
