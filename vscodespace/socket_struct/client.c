#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "client.h"

int main(int argc,char *argv[]){
	struct sockaddr_in server;
	char msg[128];
	char buf[128];
	web_req webreq;

	//webreq结构体赋值
	strcpy(webreq.SliceCTL,"creat");
	strcpy(webreq.Slicename,"slice1");
	strcpy(webreq.Network_scenario,"video");
	strcpy(webreq.Isolation,"yes");
	webreq.Uplink=1000;
	webreq.Downlink=2000;
	webreq.Latency=1;
	webreq.Mobility=500;
	webreq.reliability=99;
	

	//创建socket通讯描述符
	int s_fd=socket(AF_INET,SOCK_STREAM,0);
	if(s_fd==-1){
		perror("socket");
		return 1;
	}
	//初始化服务器的地址和端口号
	server.sin_family=AF_INET;
	server.sin_port=htons(7777);
	//127.0.0.1
	inet_pton(AF_INET,argv[1],\
		&server.sin_addr);
	//连接s_fd到服务器的地址
	int c=connect(s_fd,\
		(struct sockaddr *)&server,\
		sizeof(server));
	if(c==-1){
		perror("connect");
		return 2;
	}
#if 0
	//向服务器发送数据
	write(s_fd,msg,strlen(msg));
	//阻塞等待服务器响应信息的到来
	int r=read(s_fd,buf,128);
	write(1,buf,r);
#endif
	/*一次连接可以交互多次*/
	while(fgets(msg,128,stdin)!=NULL){
		
		if(strcmp(msg,"send\n")==0)
			{
				write(s_fd,(char *)&webreq,sizeof(webreq));
			}
		else
		{
			write(s_fd,msg,\
				strlen(msg)+1);
		}
		

		if (strcmp(msg,"quit\n")==0)
			break;

		int r=read(s_fd,buf,128);
		write(1,buf,r);
		printf("\n");
	}
	close(s_fd);
	return 0;
}
