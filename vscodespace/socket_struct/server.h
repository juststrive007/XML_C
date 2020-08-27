#include<stdio.h>


typedef struct {
	char SliceCTL[10];			//切片操作
	char Slicename[10];			//切片名称
	char Network_scenario[10];	//切片场景
	char Isolation[10];			//隔离程度
	int reliability;			//可靠性
	long Uplink;				//上行速度
	long Downlink;				//下行速度
	long Latency;				//延迟
	long Mobility;				//移动性
}web_req;
