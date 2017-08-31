
--------------------------------
-- @module MENetUtil
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#MENetUtil] GetCardPip 
-- @param self
-- @param #int nCardID
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] operatePai 
-- @param self
-- @param #int nOperateCode
-- @param #int idxPai
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] GetAreaTotalScore 
-- @param self
-- @param #int cbBetArea
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setGameClock 
-- @param self
-- @param #int wChairID
-- @param #int nTimerID
-- @param #int nTimer
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] chuPai 
-- @param self
-- @param #int idxPai
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserNameByID 
-- @param self
-- @param #int nUserID
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getFaceID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getSex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] ready 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserGold 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] changePai 
-- @param self
-- @param #int nCard1
-- @param #int nCard2
-- @param #int nCard3
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getRoomGold 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setUserGoldOrRoomCard 
-- @param self
-- @param #int nType
-- @param #long long nValue
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getCustomRoomID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] selectPai 
-- @param self
-- @param #int nType
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] GetMaxPlayerScore 
-- @param self
-- @param #int cbBetArea
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserDailiOrder 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] dismisCustomServer 
-- @param self
-- @param #bool bRoomCreater
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getCurBanker 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] playChat 
-- @param self
-- @param #int nChair
-- @param #int nIdx
-- @param #int nSex
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] playTalk 
-- @param self
-- @param #int nChair
-- @param #char url
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] leaveGame 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] init 
-- @param self
-- @param #int iKindID
-- @param #int iPlayers
-- @param #int iClientVersion
-- @param #char sGameName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getNickName 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] startTalk 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setDizhu 
-- @param self
-- @param #int nDizhu
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserIconUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] enterGame 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getTableGold 
-- @param self
-- @param #int iKindID
-- @param #int iServerID
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getGameID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getPassword 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getChairID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] admitDefeat 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getBankPassword 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] dismisCustomServerVote 
-- @param self
-- @param #int nResult
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] GetAreaPlayerScore 
-- @param self
-- @param #int cbBetArea
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] isCustomServer 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] adminCmd 
-- @param self
-- @param #int cbReqType
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] isGamePlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] endTalk 
-- @param self
-- @param #bool bSend
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] GetPlayerFreeScore 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] autoJoin 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] checkNetWork 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] applyBanker 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getEncryptPassword 
-- @param self
-- @param #char pwd
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserTypeByChair 
-- @param self
-- @param #int nChair
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] logoutGame 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getBet 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setGameOffline 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserIconUrlByChair 
-- @param self
-- @param #int nChair
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setGameEnterBackground 
-- @param self
-- @param #bool bEnterBackground
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] exitGameRoom 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] dismisCustomServerStartVote 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] clearGameClock 
-- @param self
-- @param #int wChairID
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setEnableGameClock 
-- @param self
-- @param #bool bEnable
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getUserID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] setTrustee 
-- @param self
-- @param #bool Trustee
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] cancelBanker 
-- @param self
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getTableMinGold 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] getBankGold 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] GetGameCurState 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MENetUtil] placeBet 
-- @param self
-- @param #int cbBetArea
-- @param #int lBetScore
-- @return MENetUtil#MENetUtil self (return value: MENetUtil)
        
return nil
