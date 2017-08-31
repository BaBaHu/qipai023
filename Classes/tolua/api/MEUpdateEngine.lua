
--------------------------------
-- @module MEUpdateEngine
-- @extend Node
-- @parent_module cc

--------------------------------
-- brief 设置更新包下载url<br>
-- param packageUrl 下载文件的url
-- @function [parent=#MEUpdateEngine] setPackageUrl 
-- @param self
-- @param #char packageUrl
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getDownPackageStoragePath 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getVersionFileUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- brief 设置连接超时，单位为秒<br>
-- param timeout 超时时间
-- @function [parent=#MEUpdateEngine] setConnectionTimeout 
-- @param self
-- @param #unsigned int timeout
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] setVersion 
-- @param self
-- @param #char version
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getBaseVersionFileUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] checkUpdate 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] setBaseVersion 
-- @param self
-- @param #char base_version
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
--  @brief 获取连接超时
-- @function [parent=#MEUpdateEngine] getConnectionTimeout 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- brief 设置下载文件存储地址<br>
-- param storagePath 下载文件的保存路径(解压后的文件也在该位置) 注：该路径为安装文件的私有文件夹下的相对路径,<br>
-- 用于在私有文件夹下添加文件夹
-- @function [parent=#MEUpdateEngine] setStoragePath 
-- @param self
-- @param #char storagePath
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getStoragePath 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- brief 开始更新
-- @function [parent=#MEUpdateEngine] update 
-- @param self
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getBaseVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] setVersionFileUrl 
-- @param self
-- @param #char versionFileUrl
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- brief 设置接口对象<br>
-- param delegateProtocol 接口对象
-- @function [parent=#MEUpdateEngine] setDelegate 
-- @param self
-- @param #MEUpdateManagerDelegateProtocol delegateProtocol
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- brief 是否下载的是安装包
-- @function [parent=#MEUpdateEngine] isDownpackage 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MEUpdateEngine] getDelegate 
-- @param self
-- @return MEUpdateManagerDelegateProtocol#MEUpdateManagerDelegateProtocol ret (return value: MEUpdateManagerDelegateProtocol)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] checkBaseVersion 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] setBaseVersionFileUrl 
-- @param self
-- @param #char versionBaseFileUrl
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
--------------------------------
-- 
-- @function [parent=#MEUpdateEngine] getPackageUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- brief 设置下载的相关数据<br>
-- param packageUrl 下载文件的url<br>
-- param storagePath 下载文件的保存路径(解压后的文件也在该位置) 注：该路径为安装文件的私有文件夹下的相对路径<br>
-- 用于在私有文件夹下添加文件夹
-- @function [parent=#MEUpdateEngine] MEUpdateEngine 
-- @param self
-- @return MEUpdateEngine#MEUpdateEngine self (return value: MEUpdateEngine)
        
return nil
