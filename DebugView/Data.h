#pragma once

#include <map> 

#define SEND_SERVER 1
#define RECV_SERVER 2
#define SEND_HARDWARE 3 
#define RECV_HARDWARE 4 

#define ALLPACK 0
#define SEND_RECV 1
#define WRITE_READ 2

struct tagBuffer
{
    tagBuffer()
    {
        int m_type = -1;
        m_byte = nullptr;
        m_str = L"";
        m_lenth = 0;
        m_isDelete = 0;
    }
    ~tagBuffer(){};

    int m_type;
    BYTE* m_byte;
    CString m_str;
    int m_lenth;
    int m_isDelete;
};

class CData
{
public:
    CData();
    ~CData();

    tagBuffer* addInfo(COPYDATASTRUCT* pCopyDataStruct);
      
    std::map<int, tagBuffer*>* getByteAll();

    std::map<int, tagBuffer*>* getSR();

    std::map<int, tagBuffer*>* getSend();

    std::map<int, tagBuffer*>* getRecv();

    std::map<int, tagBuffer*>* getWR();
      
    std::map<int, tagBuffer*>* getWeite();

    std::map<int, tagBuffer*>* getRead();
    
    void deleteList(int showComm);

    void deleteAllData();

protected:
    void deleteAll(int showComm);
      
    void deleteSendRecv(int comm);

    void deleteWriteRead(int comm);

private: 

    //0£ºËùÓÐbyte£¬1£ºsr, 2£ºwr
    std::map<int, tagBuffer*> m_packAll[3];
    
    std::map<int, tagBuffer*> m_sr[2];
    std::map<int, tagBuffer*> m_wr[2];
}; 