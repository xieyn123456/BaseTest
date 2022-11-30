#pragma once
//Version 1.1.190
class CMotionLibInterface
{
public:
	CMotionLibInterface(void);
	~CMotionLibInterface(void);
public:
	CString m_Version;
public:
	virtual int InitMotionLib();
	virtual int ShowParamDlg();
	virtual int ShowMonitorDlg();
	virtual int ShowManualDlg();
public:
	/****************************************************************
	函    数    名  GetAxisCardNum
	功  能  描  述  获取轴卡数量
	输  入  参  数  
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetAxisCardNum();

	/****************************************************************
	函    数    名  GetAxisName
	功  能  描  述  获取轴名称
	输  入  参  数  
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual CString GetAxisName(int CardNum,int AxisNum);

	/****************************************************************
	函    数    名  GetIOCardNum
	功  能  描  述  获取IO卡数量
	输  入  参  数
	输  出  参  数
	编    撰    者
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetIOCardNum();

	/****************************************************************
	函    数    名  GetVolCardNum
	功  能  描  述  获取模拟量卡数量
	输  入  参  数  
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetVolCardNum();

	/****************************************************************
	函    数    名  GetAxisNum
	功  能  描  述  获取控制卡轴数量
	输  入  参  数  CardNum：卡号
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetAxisNum(int CardNum);

	/****************************************************************
	函    数    名  GetInputNum
	功  能  描  述  获取IO卡输入信号数量
	输  入  参  数  CardNum：卡号
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetInputNum(int CardNum);

	/****************************************************************
	函    数    名  GetOutputNum
	功  能  描  述  获取IO卡输出信号数量
	输  入  参  数  CardNum：卡号
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetOutputNum(int CardNum);

	/****************************************************************
	函    数    名  GetInputName
	功  能  描  述  获取IO卡输入信号名称
	输  入  参  数  CardNum：卡号
	                BitNum：端口号
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual CString GetInputName(int CardNum,int BitNum);

	/****************************************************************
	函    数    名  GetOutputName
	功  能  描  述  获取IO卡输出信号名称
	输  入  参  数  CardNum：卡号
	                BitNum：端口号
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual CString GetOutputName(int CardNum,int BitNum);

	/****************************************************************
	函    数    名  SetLimitEnable
	功  能  描  述  设置正负极限使能
	输  入  参  数  CardNum：卡号
	                AxisNum：轴号
	                Value：0：开启 1：关闭
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetLimitEnable(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetLimitMode
	功  能  描  述  设置正负极限信号模式
	输  入  参  数  CardNum：卡号
	                AxisNum：轴号
	                Value：0：高电平有效 1：低电平有效
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetLimitMode(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetEncMode
	功  能  描  述  设置编码器模式
	输  入  参  数  CardNum：卡号
	                AxisNum：轴号
	                Value：0：打开编码器 1：关闭编码器
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetEncMode(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetPulseMode
	功  能  描  述  设置脉冲模式
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	                Value：模式(0：脉冲+方向，1：CW/CCW)
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetPulseMode(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetAlarmEnable
	功  能  描  述  设置伺服报警模式
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	                Value：模式(0：报警打开，1：报警关闭)
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetAlarmEnable(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetPulseInputMode
	功  能  描  述  设置脉冲输入模式
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	                Value：模式(0：正常，1：取反)
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetPulseInputMode(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetServoEnbale
	功  能  描  述  设置伺服ON
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	                Value：模式(0：关闭伺服，1：打开伺服)
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetServoEnbale(int CardNum,int AxisNum,int Value);

	/****************************************************************
	函    数    名  SetSoftLimitParam
	功  能  描  述  设置软件行程
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	                LimitP：正行程参数
					LimitN：负行程参数
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetSoftLimitParam(int CardNum,int AxisNum,double LimitP,double LimitN);

	/****************************************************************
	函    数    名  SetSoftLimitEnable
	功  能  描  述  设置软件行程使能
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Value：0：禁用 1：启用
	                LimitP：正行程参数
					LimitN：负行程参数
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetSoftLimitEnable(int CardNum,int AxisNum,int Value,double LimitP,double LimitN);

	/****************************************************************
	函    数    名  AxisHome
	功  能  描  述  轴回原点
	输  入  参  数  RunNum：轴数量
	                CardNum[]：卡号数组{0，0，0，0}
                	AxisNum[]：轴号数组{1，2，3，4}
					Speed[]：速度数组
					Mode[]：模式数组（设置0）
	输  出  参  数  
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AxisHome(int RunNum,int CardNum[],int AxisNum[]);

	/****************************************************************
	函    数    名  JogMove
	功  能  描  述  马达移动
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Speed：速度
					Acc：加速度
					Dec：减速度
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int JogMove(int CardNum,int AxisNum,int Dir,double Speed);

	/****************************************************************
	函    数    名  AxisRun
	功  能  描  述  获取轴状态
	输  入  参  数  RunNum：轴数量
	                CardNum[]：卡号数组{0，0，0，0}
                	AxisNum[]：轴号数组{1，2，3，4}
					Pos[]：位置数组
					Speed[]：速度数组
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AxisRun(int RunNum,int CardNum[],int AxisNum[],double Pos[],double Speed[]);

	/****************************************************************
	函    数    名  AxisRun2
	功  能  描  述  带暂停功能的轴运行
	输  入  参  数  RunNum：轴数量
	                CardNum[]：卡号数组{0，0，0，0}
                	AxisNum[]：轴号数组{1，2，3，4}
					Pos[]：位置数组
					Speed[]：速度数组
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AxisRun2(int RunNum,int CardNum[],int AxisNum[],double Pos[],double Speed[],int StopCard,int StopPort,int StopValue,int StartCard,int StartPort,int StartValue);

	/****************************************************************
	函    数    名  AxisRun3
	功  能  描  述  带暂停功能的轴运行
	输  入  参  数  ProgramNum：程序号
	                RunNum：    轴数量
	                CardNum[]： 卡号数组{0，0，0，0}
                	AxisNum[]： 轴号数组{1，2，3，4}
					Pos[]：     位置数组
					Speed[]：   速度数组
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AxisRun3(int ProgramNum,int RunNum,int CardNum[],int AxisNum[],double Pos[],double Speed[],int StopCard,int StopPort,int StopValue,int StartCard,int StartPort,int StartValue);

	/****************************************************************
	函    数    名  AxisRun4
	功  能  描  述  带暂停功能的轴运行
	输  入  参  数  ProgramNum：  程序号
	                RunNum：      轴数量
	                CardNum[]：   卡号数组{0，0，0，0}
                	AxisNum[]：   轴号数组{1，2，3，4}
					Pos[]：       位置数组
					Speed[]：     速度数组
					StopSignalM： 停止信号M0--M1999，1：停止  0：运行
	输  出  参  数
	编    撰    者   
	日          期  2021.07.29
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AxisRun4(int ProgramNum,int RunNum,int CardNum[],int AxisNum[],double Pos[],double Speed[],int StopSignalM);

	/****************************************************************
	函    数    名  InPos
	功  能  描  述  获取轴定位完成
	输  入  参  数  RunNum：轴数量
	                CardNum[]：卡号数组{0，0，0，0}
                	AxisNum[]：轴号数组{1，2，3，4}
					Mode：0：暂停功能OFF
					      1：暂停功能ON
	输  出  参  数
	编    撰    者   
	日          期  2021.07.29
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int InPos(int RunNum,int CardNum[],int AxisNum[],int Mode);

	/****************************************************************
	函    数    名  LineInit
	功  能  描  述  插补参数初始化
	输  入  参  数  
	                RunNum：插补轴数
	                CardNum：卡号
					AxisNum[]：轴号数组{1，2，3，4}
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LineInit(int RunNum,int CardNum,int AxisNum[],int Group);

	/****************************************************************
	函    数    名  LinePass
	功  能  描  述  直线插补
	输  入  参  数  
	                CardNum：卡号
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LineStart(int CardNum,int Group);

	/****************************************************************
	函    数    名  LinePass
	功  能  描  述  直线插补
	输  入  参  数  RunNum：轴数量
	                CardNum：卡号
                	AxisNum[]：轴号数组{1，2，3，4}
					StartPos[]：开始位置
					EndPos[]：结束位置
					Speed：速度
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LinePass(int RunNum,int CardNum,int AxisNum[],double StartPos[],double EndPos[],double Speed,int Group);

	/****************************************************************
	函    数    名  LineArc
	功  能  描  述  圆弧插补
	输  入  参  数  RunNum：轴数量
	                CardNum：卡号
                	AxisNum[]：轴号数组{1，2，3，4}
					StartPos[]：开始位置
					ArcPos[]：圆弧中间位置
					EndPos[]：结束位置
					Speed：速度
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LineArc(int RunNum,int CardNum,int AxisNum[],double StartPos[],double ArcPos[],double EndPos[],double Speed,int Group);

	/****************************************************************
	函    数    名  GetCurrentLineEnd
	功  能  描  述  获取插补状态
	输  入  参  数  RunNum：轴数量
        	        CardNum：卡号
                	AxisNum[]：轴号数组{1，2，3，4}
					Mode：1：带暂停功能
	输  出  参  数  0：允许插入下一条
	                1：暂停
					-1：异常
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetCurrentLineEnd(int RunNum,int CardNum,int AxisNum[],int Mode);

	/****************************************************************
	函    数    名  GetLineEnd
	功  能  描  述  获取插补状态
	输  入  参  数  RunNum：轴数量
        	        CardNum：卡号
                	AxisNum[]：轴号数组{1，2，3，4}
					Group：插补组号
					Param[]：{0：剩余插补线段}
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetLineEnd(int RunNum,int CardNum,int AxisNum[],int Group,long Param[]);

	/****************************************************************
	函    数    名  LineIO
	功  能  描  述  插补IO输出
	输  入  参  数  
        	        CardNum：卡号
                	Bit：端口号
					Value：输出结果
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LineIO(int CardNum,int Bit,int Value,int Group);

	/****************************************************************
	函    数    名  GetLineEnd
	功  能  描  述  获取插补状态
	输  入  参  数  
        	        CardNum：卡号
                	Time：延时时间
					Group：插补组号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int LineDelay(int CardNum,double Time,int Group);

	/****************************************************************
	函    数    名  AbsPosition
	功  能  描  述  绝对定位
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Pos：位置
					Speed：速度
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int AbsPosition(int CardNum,int AxisNum,double Pos,double Speed);

	/****************************************************************
	函    数    名  RelPosition
	功  能  描  述  相对定位
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Pos：位置
					Speed：速度
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int RelPosition(int CardNum,int AxisNum,double Pos,double Speed);

	/****************************************************************
	函    数    名  GetAxisSignal
	功  能  描  述  获取轴IO状态
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Status：运动IO状态返回值
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetAxisSignal(int CardNum,int AxisNum,long &Status);

	/****************************************************************
	函    数    名  GetAxisIO
	功  能  描  述  获取轴IO信号
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Mode：0：伺服报警
					      1：正极限
                          2：负极限
						  3：原点
						  4：伺服ON
						  5：复位完成
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetAxisIO(int CardNum,int AxisNum,int Mode);

	/****************************************************************
	函    数    名  GetAxisStatus
	功  能  描  述  获取轴状态
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	输  出  参  数  0：轴运行状态
	                5：轴停止状态
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int GetAxisStatus(int CardNum,int AxisNum);

	/****************************************************************
	函    数    名  ReadAxisPos
	功  能  描  述  获取轴当前位置
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Param：位置
	输  出  参  数
	编    撰    者
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int ReadAxisPos(int CardNum,int AxisNum,double &Param);

	/****************************************************************
	函    数    名  ReadCommandPos
	功  能  描  述  获取轴指令位置
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Param：位置
	输  出  参  数
	编    撰    者
	日          期  2021.07.29
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int ReadCommandPos(int CardNum,int AxisNum,double &Param);

	/****************************************************************
	函    数    名  SetSuddenStop
	功  能  描  述  停止轴
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetSuddenStop(int CardNum,int AxisNum);

	/****************************************************************
	函    数    名  SetAxisParam
	功  能  描  述  设置轴参数
	输  入  参  数  CardNum：卡号
                	AxisNum：轴号
					Type：0.极限信号模式
					      1.返回脉冲接收功能
					Param：参数
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetAxisParam(int CardNum,int AxisNum,int Type,int Param);

	/****************************************************************
	函    数    名  WriteOutput
	功  能  描  述  轴卡信号输出
	输  入  参  数  CardNum：卡号
                	Bit：端口号
					Value：输出值
	输  出  参  数
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int WriteOutput(int CardNum,int Bit,short Value);

	/****************************************************************
	函    数    名  ReadInput
	功  能  描  述  读取轴卡输入信号
	输  入  参  数  CardNum：扩展模块卡号
                	Bit：端口号
	输  出  参  数  0：低电平信号
	                1：高电平信号
	编    撰    者   
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int ReadInput(int CardNum,int Bit);

	/****************************************************************
	函    数    名  ReadInputExtMdl
	功  能  描  述  读取轴卡输出信号
	输  入  参  数  CardNum：扩展模块卡号
                	Bit：端口号
	输  出  参  数  0：低电平信号
	                1：高电平信号
	编    撰    者
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int ReadOutput(int CardNum,int Bit);

	/****************************************************************
	函    数    名  SetAxisPos
	功  能  描  述  轴位置置零
	输  入  参  数  CardNum：扩展模块卡号
                	AxisNum：轴号
					Pos:需要设置的位置(脉冲数?)
	输  出  参  数
	编    撰    者
	日          期
	修    改    者
	日          期
	版    本    号	V1.0
	*****************************************************************/
	virtual int SetAxisPos(int CardNum,int AxisNum,long Pos);
};
