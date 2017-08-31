#include "CServerItem.h"

//管理消息
bool CServerItem::OnSocketMainManager(int sub, void* data, int dataSize)
{
	switch (sub)
	{
	case SUB_GR_OPTION_CURRENT:	//当前配置
		{
			PLAZZ_PRINTF(("flow->CServerItem::OnSocketMainManager 当前配置 "));

			////效验参数
			//ASSERT(dataSize==sizeof(CMD_GR_OptionCurrent));
			//if (dataSize!=sizeof(CMD_GR_OptionCurrent)) return false;

			//PLAZZ_PRINTF("TODO:CServerItem::OnSocketMainManager 未处理\n");
			////消息处理
			//if (m_pDlgServerManager!=0)
			//{
			//	CMD_GR_OptionCurrent * pOptionCurrent=(CMD_GR_OptionCurrent *)data;
			//	m_pDlgServerManager->SetServerType(m_wServerType);
			//	m_pDlgServerManager->SetServerOptionInfo(pOptionCurrent->ServerOptionInfo,pOptionCurrent->dwRuleMask);
			//}

			return true;
		}
	case SUB_GR_DISMISSVOTENotiy:
		{
			if (!IClientKernel::get())
				return true;
			return IClientKernel::get()->OnGFEventSocket(MDM_GR_MANAGE, sub, data, dataSize);
		}
	case SUB_GR_DISMISSVOTERes:
		{
			if (!IClientKernel::get())
				return true;
			return IClientKernel::get()->OnGFEventSocket(MDM_GR_MANAGE, sub, data, dataSize);
		}
	}

	return true;
}
