
--------------------------------
-- @module TableUI
-- @extend Layer,TableViewDataSource,TableViewDelegate
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#TableUI] setTableScrollOffset 
-- @param self
-- @param #int yOffset
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] onEnter 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] onExit 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] cellSizeForTable 
-- @param self
-- @param #cc.TableView table
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TableUI] scrollViewDidScroll 
-- @param self
-- @param #cc.ScrollView view
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellSizeForIndex 
-- @param self
-- @param #cc.TableView table
-- @param #int idx
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TableUI] getTableScrollOffset 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] scrollViewDidZoom 
-- @param self
-- @param #cc.ScrollView view
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellAtIndex 
-- @param self
-- @param #cc.TableView table
-- @param #int idx
-- @return TableViewCell#TableViewCell ret (return value: cc.TableViewCell)
        
--------------------------------
-- 
-- @function [parent=#TableUI] setChairIcon 
-- @param self
-- @param #int nTable
-- @param #int nChair
-- @param #char icon
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] numberOfCellsInTableView 
-- @param self
-- @param #cc.TableView table
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellTouched 
-- @param self
-- @param #cc.TableView table
-- @param #cc.TableViewCell cell
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellWillRecycle 
-- @param self
-- @param #cc.TableView table
-- @param #cc.TableViewCell cell
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] backToServerListScene 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellHighlight 
-- @param self
-- @param #cc.TableView table
-- @param #cc.TableViewCell cell
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] onEnterTransitionDidFinish 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] tableCellUnhighlight 
-- @param self
-- @param #cc.TableView table
-- @param #cc.TableViewCell cell
-- @return TableUI#TableUI self (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] create 
-- @param self
-- @param #int width
-- @param #int height
-- @param #int x
-- @param #int y
-- @return TableUI#TableUI ret (return value: TableUI)
        
--------------------------------
-- 
-- @function [parent=#TableUI] TableUI 
-- @param self
-- @return TableUI#TableUI self (return value: TableUI)
        
return nil
