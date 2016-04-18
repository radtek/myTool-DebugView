DebugView是一款方便分析网络程序、硬件通信和组合通信查看发包信息的一款工具。

帮助分析人员理顺发(收)包顺序流程，便于逆向分析或者还原发包流程。

这款工具不是万能的，你需要自行找到发送点并且自己进行做HOOK。 

  HWND m_hwnd = ::FindWindow(NULL, \"DebugView\");  
  .... 
  
  ::SendMessage(m_hwnd, WM_COPYDATA, NULL, (LPARAM)&data); 
  
命令：

    send:      1 
    
    recve:     2
    
    WriteFile: 3 
    
    ReadFile:  4
    

作者：http://www.xuwu.org/debugview/
