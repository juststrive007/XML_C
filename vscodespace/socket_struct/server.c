#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>
#include "server.h"
int t_listen(short port,int backlog){
	int s_fd;
	struct sockaddr_in server;
	s_fd=socket(AF_INET,SOCK_STREAM,0);
	if(s_fd==-1){
		perror("socket");
		return -1;
	}
	
	//对服务器的地址和端口号初始化
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	//INADDR_ANY代表本机上的所有ip地址
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	//绑定服务器的地址和端口号到通讯描述符
	int b=bind(s_fd,(struct sockaddr *)&server,\
			sizeof(server));
	if(b==-1){
		perror("bind");
		return -1;
	}
	//在s_fd描述符上监听
	listen(s_fd,backlog);
	return s_fd;

}
int main(void){
	int s_fd,conn_fd;
	char buf[128];
	char IP[128];
	int len;
	struct sockaddr_in client;
	
	web_req webreq; //定义接收的结构体

	
	s_fd=t_listen(7777,5);
	while(1){
		len=sizeof(client);
		//阻塞等待客户端连接的到来
		conn_fd=accept(s_fd,\
		(struct sockaddr *)&client,&len);
		if(conn_fd==-1){
			perror("accept");
			return 3;
		}
		printf("%s\n",\
	inet_ntop(AF_INET,&client.sin_addr,IP,128));
		while(1){
			//获取客户端的数据
			int r=read(conn_fd,buf,128);
			//strcmp(buf,"q");
			//比较大小
				
			printf("sizeof webrep:%d\n",sizeof(webreq));
			printf("hello word!\n");
			printf("r:%d\n",r);
			if(r==sizeof(webreq))
			{
				printf("start memcpy\n");
				memcpy(&webreq,buf,sizeof(webreq));
				printf("SliceCTL:%s\n",webreq.SliceCTL);
				printf("Slicename:%s\n",webreq.Slicename);
				printf("Network_scenario:%s\n",webreq.Network_scenario);
				printf("Isolation:%s\n",webreq.Isolation);
				printf("Uplink:%ld\n",webreq.Uplink);
				printf("Downlink:%ld\n",webreq.Downlink);
				printf("Latency:%ld\n",webreq.Latency);
				printf("Mobility:%ld\n",webreq.Mobility);
				printf("reliability:%d\n",webreq.reliability);
			}


			//处理数据
			for(int i=0;i<r;i++)
				buf[i]=toupper(buf[i]);
			if(strcmp(buf,"QUIT\n")==0)
				break;
			//发送给客户端
			write(conn_fd,buf,r);
		}
		//关闭连接
		close(conn_fd);

	}
	close(s_fd);
	return 0;
}
