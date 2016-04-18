#include "stdafx.h"
#include "Data.h"


CData::CData()
{ 
}


CData::~CData()
{
}

tagBuffer* CData::addInfo(COPYDATASTRUCT* pCopyDataStruct)
{
    tagBuffer *pData = new tagBuffer;
    if (pData == nullptr)
    {
        ::MessageBox(nullptr, L"系统内存不足，请点击【清理列表】", L"系统提示", MB_OK);
        return nullptr;
    }
 
    pData->m_type = pCopyDataStruct->dwData; 
    pData->m_lenth = pCopyDataStruct->cbData;
    pData->m_byte = new BYTE[pCopyDataStruct->cbData];
    if (pData->m_byte == nullptr)
    {
        ::MessageBox(nullptr, L"系统内存不足，请点击【清理列表】", L"系统提示", MB_OK);
        delete pData;
        return nullptr;
    }

    memset(pData->m_byte, 0x0, pData->m_lenth);
    memcpy(pData->m_byte, pCopyDataStruct->lpData, pData->m_lenth);
    
    if (pCopyDataStruct->dwData == SEND_SERVER || pCopyDataStruct->dwData == RECV_SERVER)
    {
        m_packAll[SEND_RECV].insert(std::pair<int, tagBuffer*>(m_packAll[SEND_RECV].size(), pData));
  
        int inedx = (pCopyDataStruct->dwData == SEND_SERVER) ? 0 : 1;
        m_sr[inedx].insert(std::pair<int, tagBuffer*>(m_sr[inedx].size(), pData));
    }
    else if (pCopyDataStruct->dwData == SEND_HARDWARE || pCopyDataStruct->dwData == RECV_HARDWARE)
    {
        m_packAll[WRITE_READ].insert(std::pair<int, tagBuffer*>(m_packAll[WRITE_READ].size(), pData));

        int inedx = (pCopyDataStruct->dwData == SEND_HARDWARE) ? 0 : 1;
        m_wr[inedx].insert(std::pair<int, tagBuffer*>(m_wr[inedx].size(), pData));
    }
    else
    {
        delete pData;
        return nullptr;
    }

    m_packAll[ALLPACK].insert(std::pair<int, tagBuffer*>(m_packAll[ALLPACK].size(), pData));

    return pData;
} 
 
std::map<int, tagBuffer*>* CData::getByteAll()
{
    return &m_packAll[0];
}

std::map<int, tagBuffer*>* CData::getSR()
{
    return &m_packAll[1];
}

std::map<int, tagBuffer*>* CData::getSend()
{
    return &m_sr[0];
}

std::map<int, tagBuffer*>* CData::getRecv()
{
    return &m_sr[1];
}

std::map<int, tagBuffer*>* CData::getWR()
{
    return &m_packAll[2];
}

std::map<int, tagBuffer*>* CData::getWeite()
{
    return &m_wr[0];
}

std::map<int, tagBuffer*>* CData::getRead()
{
    return &m_wr[1];
}

void CData::deleteList(int showComm)
{
    switch (showComm)
    {
    case 0:
    {
        deleteAll(0);
        break;
    }
    case 1:
    {
        deleteAll(1);
        break;
    } 
    case 2:
    {
        deleteSendRecv(0);
        break;
    }
    case 3:
    {
        deleteSendRecv(1);
        break;
    }
    case 4:
    {
        deleteAll(2);
        break;
    }
    case 5:
    {
        deleteWriteRead(0);
        break;
    }
    case 6:
    {
        deleteWriteRead(1);
        break;
    }
    default:
        break;
    }
}

void CData::deleteAll(int showComm)
{
    std::map<int, tagBuffer*>::iterator it = m_packAll[showComm].begin();
    for (it; it != m_packAll[showComm].end();)
    {
        if (it->second->m_isDelete >= 3)
        {
            delete it->second;
        } 
        else
        {
            it->second->m_isDelete++;
        }

        std::map<int, tagBuffer*>::iterator oit = it;
        it++;
        m_packAll[showComm].erase(oit);
    }

    m_packAll[showComm].clear();
}
 

void CData::deleteSendRecv(int showComm)
{
    std::map<int, tagBuffer*>::iterator it = m_sr[showComm].begin();
    for (it; it != m_sr[showComm].end();)
    {
        if (it->second->m_isDelete >= 3)
        {
            delete it->second;
        }
        else
        {
            it->second->m_isDelete++;
        }

        std::map<int, tagBuffer*>::iterator oit = it;
        it++;
        m_sr[showComm].erase(oit);
    }

    m_sr[showComm].clear();
}

void CData::deleteWriteRead(int showComm)
{
    std::map<int, tagBuffer*>::iterator it = m_wr[showComm].begin();
    for (it; it != m_wr[showComm].end();)
    {
        if (it->second->m_isDelete >= 3)
        {
            delete it->second;
        }
        else
        {
            it->second->m_isDelete++;
        }

        std::map<int, tagBuffer*>::iterator oit = it;
        it++;
        m_wr[showComm].erase(oit);
    }

    m_wr[showComm].clear();
}

void CData::deleteAllData()
{
    deleteList(0);
    deleteList(1);
    deleteList(2);
    deleteList(3);
    deleteList(4);
    deleteList(5);
    deleteList(6);
    deleteList(7);
}