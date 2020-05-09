#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

extern int getopt(int argc,char* const argv[],const char* optstring);
extern char* optarg;
extern int optind,opterr,optopt;
extern char* strerror(int errnum);


int main(int argc,char* argv[])
{
	int opt=0;

	short int PORT=33678;	//	Default port
	const char* IPADDR="127.0.0.1";	//	Default ip

	if ((opt=getopt(argc,argv,"cs")) != -1)	//	Get option."c" is a argument list.If detected a error,getop return '?'.
		switch (opt)
		{
			case 'c':	//	Client.
				sleep(2);
				char BUFF[10];	//	Buffer
				struct sockaddr_in ADDR={
					.sin_family=AF_INET,
					.sin_port=PORT,
				};	//	This struct is saving address of server.
				
				short result=inet_pton(AF_INET,IPADDR,&ADDR.sin_addr);	//	Point string to sockaddr structure.
				if (result == 1)
					;
				else
				{
					fprintf(stderr,"Convert ip address failed! Client %d \n",result);
					fprintf(stderr,"Error : %s \n",strerror(errno));
					exit(EXIT_FAILURE);
				}
		
				int socketfdc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	//	No name socket.
				if (socketfdc < 0)
				{
					fprintf(stderr,"Create socket failed,client!\n");
					exit(EXIT_FAILURE);
				}
				else
					if (connect(socketfdc,(struct sockaddr*)&ADDR,sizeof(ADDR)) == 0)	//	Connect successly.
					{
						short int result=read(socketfdc,&BUFF,10);
						if (result == 0)
						{
							fprintf(stderr,"Client read EOF!\n");
							//	Now quit.	
							close(socketfdc);
							exit(EXIT_SUCCESS);
						}
						else if (result == -1)
						{
							fprintf(stderr,"Client read error!\n");
							close(socketfdc);
							exit(EXIT_FAILURE);
						}
						else
						{
							fprintf(stderr,"Client read data record - numbers %d !\n",result);
							close(socketfdc);
							exit(EXIT_SUCCESS);
						}

					}
					else
					{
						fprintf(stderr,"Connect to server failed!\n");
						exit(EXIT_FAILURE);
					}
				
				break;
			case 's':
				fprintf(stderr,"In server !\n");
				//if (optopt == 's')	//	Server
				//{
				{
					struct sockaddr_in ADDR={
						.sin_family=AF_INET,
						.sin_port=PORT,
					};
					int result_value=inet_pton(AF_INET,IPADDR,&ADDR.sin_addr);	//	Succeed.
					if (result_value == 1)
						;
					else
					{
						fprintf(stderr,"Convert ip address failed! Server\n");
						fprintf(stderr,"Error : %s \n",strerror(errno));
						exit(EXIT_FAILURE);
					}

					int socketfds=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	//	Create socket.
					if (socketfds > 0)
						;
					else
					{
						fprintf(stderr,"Create sock failed! Server\n");
						exit(EXIT_FAILURE);
					}

					//	Bind socket.

					if (bind(socketfds,(struct sockaddr*)&ADDR,sizeof(ADDR)) == 0)		//	Bind socket
					{
						listen(socketfds,1);		//	Listen socket.
					}
					else		
					{
						fprintf(stderr,"Bind socket failed!\n");
						exit(EXIT_FAILURE);
					}

					int Connect_socket=accept(socketfds,NULL,NULL);		//	Wait a connection
		
					sleep(3);						//	sleep 3s.


					//	Up to there,has made a connection.

					//	Using shutdown.

					if (shutdown(Connect_socket,SHUT_RDWR) == 0)		//	Shutdown for a link from client.
					{
						fprintf(stderr,"Shutdown a connection,now quit!\n");
						close(socketfds);				//	Close server socket.
						exit(EXIT_SUCCESS);
					}
				}	
				//}
			
			//	else
			//	{
			//		fprintf(stderr,"Not defined option! %c \n",optopt);
			//		exit(EXIT_FAILURE);
			//	}
			default:
				;
		}
		else
			fprintf(stderr,"Option error!\n");

	exit(EXIT_FAILURE);

}
