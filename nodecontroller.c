#include "buf_mgr.h"
#include "ddonuts.h"

typedef struct thread_arg {
	int my_chan;
	int my_node_id;
}TH_ARG;

int th_index;
pthread_t thread_ids;
void *chan_monitor(void *);

int main(int argc, char *argv[]) {
	
	int inet_sock1, inet_sock2, inet_sock3, inet_sock4, inet_sock5, new_sock1, new_sock2;
	int fromlen1, fromlen2, cli_addr;
	struct sockaddr_in inet_telnum1, inet_telnum2, inet_telnum3, inet_telnum4, inet_telnum5;
	int wild_card1 = INADDR_ANY;
	int wild_card2 = INADDR_ANY;
	int input = atoi(argv[1]);
	struct hostent *heptr, *heptr1, *heptr2, *gethostbyname();
	int n;
	char buffer[256];
	char buff_out[1024];
	char buff_in[1024];
	int rlen;
	TH_ARG *th_arg;
	
	switch(input) {
		case 0:
			/***** allocate a socket to communicate with *****/
			if((inet_sock1=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			  perror("inet_sock allocation failed: ");
			}

			/***** byte copy the wild_card IP address INADDR_ANY into   *****/
			/***** IP address structure, along with port and family and *****/
			/***** use the structure to give yourself a connect address *****/

			bcopy(&wild_card1, &inet_telnum1.sin_addr, sizeof(int));
			inet_telnum1.sin_family = AF_INET;
			inet_telnum1.sin_port = htons( (u_short)PORT2 );

			if(bind(inet_sock1, (struct sockaddr *)&inet_telnum1, sizeof(struct sockaddr_in)) == -1){
			  perror("inet_sock bind failed: ");
			}

			listen(inet_sock1, 5);
			printf("\nTHE NODE CONTROLLER IS UP\n");
			
			fromlen1 = sizeof(struct sockaddr);
			while(1) {
				new_sock1 = accept(inet_sock1, (struct sockaddr *)&cli_addr, &fromlen1);
				if(new_sock1 == -1){
					perror("accept failed: ");
			 	}
				
				/*th_arg = malloc(sizeof(TH_ARG));
				th_arg->my_chan = new_sock1;
				th_arg->my_node_id = 0;
				pthread_create(&thread_ids, NULL, chan_monitor, (void *)th_arg);*/
			}
			//close(inet_sock1);
			break;
		case 1:
			/***** allocate a socket to communicate with *****/
			if((inet_sock2=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			  perror("inet_sock allocation failed: ");
			}

			/***** get a hostent pointer to point to a hostent structure *****/
			/***** which contains the remote IP address of server        *****/

			if((heptr = gethostbyname("localhost")) == NULL){
			  perror("gethostbyname failed: ");
			  exit(1);
			}

			/***** byte copy the IP adress from the h_addr field in the *****/
			/***** hostent structure into an IP address structure       *****/

			bcopy(heptr->h_addr, &inet_telnum2.sin_addr, heptr->h_length);
			inet_telnum2.sin_family = AF_INET;
			inet_telnum2.sin_port = htons( (u_short)PORT2 );

			/***** use the connect system call to open a TCP connection *****/

			if(connect(inet_sock2, (struct sockaddr *)&inet_telnum2, sizeof(struct sockaddr_in)) == -1){
			  perror("inet_sock connect failed: ");
			  exit(2);
			}
			
			/*th_arg = malloc(sizeof(TH_ARG));
			th_arg->my_chan = inet_sock2;
			th_arg->my_node_id = 1;
			pthread_create(&thread_ids, NULL, chan_monitor, (void *)th_arg);*/
			
			/***** allocate a socket to communicate with *****/
			if((inet_sock3=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			  perror("inet_sock allocation failed: ");
			}

			/***** byte copy the wild_card IP address INADDR_ANY into   *****/
			/***** IP address structure, along with port and family and *****/
			/***** use the structure to give yourself a connect address *****/

			bcopy(&wild_card2, &inet_telnum3.sin_addr, sizeof(int));
			inet_telnum3.sin_family = AF_INET;
			inet_telnum3.sin_port = htons( (u_short)PORT3 );

			if(bind(inet_sock3, (struct sockaddr *)&inet_telnum3, sizeof(struct sockaddr_in)) == -1){
			  perror("inet_sock bind failed: ");
			}

			listen(inet_sock3, 5);
			printf("\nTHE NODE CONTROLLER 2 IS UP\n");
	
			while(1) {
				fromlen2 = sizeof(struct sockaddr);
				new_sock2 = accept(inet_sock3, (struct sockaddr *)&cli_addr, &fromlen2);
				if(new_sock2 == -1){
					perror("accept failed: ");
			 	}
				/*th_arg = malloc(sizeof(TH_ARG));
				th_arg->my_chan = new_sock2;
				th_arg->my_node_id = 1;
				pthread_create(&thread_ids, NULL, chan_monitor, (void *)th_arg);*/			
			}
			//close(inet_sock2);
			//close(inet_sock3);
			break;
		case 2: 
			/***** allocate a socket to communicate with *****/

			if((inet_sock4=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			  perror("inet_sock allocation failed: ");
			  exit(1);
			}

			/***** get a hostent pointer to point to a hostent structure *****/
			/***** which contains the remote IP address of server        *****/

			if((heptr1 = gethostbyname("localhost")) == NULL){
			  perror("gethostbyname failed: ");
			  exit(1);
			}

			/***** byte copy the IP adress from the h_addr field in the *****/
			/***** hostent structure into an IP address structure       *****/

			bcopy(heptr1->h_addr, &inet_telnum4.sin_addr, heptr1->h_length);
			inet_telnum4.sin_family = AF_INET;
			inet_telnum4.sin_port = htons( (u_short)PORT2 );

			/***** use the connect system call to open a TCP connection *****/

			if(connect(inet_sock4, (struct sockaddr *)&inet_telnum4, sizeof(struct sockaddr_in)) == -1){
			  perror("inet_sock connect failed at: ");
			  exit(2);
			}
			
			/*th_arg = malloc(sizeof(TH_ARG));
			th_arg->my_chan = inet_sock4;
			th_arg->my_node_id = 2;
			pthread_create(&thread_ids, NULL, chan_monitor, (void *)th_arg);*/
			/***** allocate a socket to communicate with *****/

			if((inet_sock5=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			  perror("inet_sock allocation failed: ");
			  exit(1);
			}

			/***** get a hostent pointer to point to a hostent structure *****/
			/***** which contains the remote IP address of server        *****/

			if((heptr2 = gethostbyname("localhost")) == NULL){
			  perror("gethostbyname failed: ");
			  exit(1);
			}

			/***** byte copy the IP adress from the h_addr field in the *****/
			/***** hostent structure into an IP address structure       *****/

			bcopy(heptr2->h_addr, &inet_telnum5.sin_addr, heptr2->h_length);
			inet_telnum5.sin_family = AF_INET;
			inet_telnum5.sin_port = htons( (u_short)PORT3 );

			/***** use the connect system call to open a TCP connection *****/

			if(connect(inet_sock5, (struct sockaddr *)&inet_telnum5, sizeof(struct sockaddr_in)) == -1){
			  perror("inet_sock connect failed at: ");
			  exit(2);
			}
			
			/*th_arg = malloc(sizeof(TH_ARG));
			th_arg->my_chan = inet_sock5;
			th_arg->my_node_id = 2;
			pthread_create(&thread_ids, NULL, chan_monitor, (void *)th_arg);*/

			printf("\nTHE NODE CONTROLLER 3 IS UP\n");
			while(1) {
			}
			//close(inet_sock4);
			//close(inet_sock5);
			break;
		default:
			break;
	}
}

void *chan_monitor(void *arg) {
	TH_ARG *th_arg = (TH_ARG *)arg;
	char buff_out[1024];
	char buff_in[1024];
	int rlen;
	printf("in chan monitor");
	while(1) {
		if ((rlen = read(th_arg->my_chan, buff_in, sizeof(buff_in)-1))>0) {
			printf("Message received: %s", buff_in);
		}
		if (fgets(buff_out, 1024, stdin) > 0) {
			send(th_arg->my_chan, buff_out, strlen(buff_out), 0);
		}
		memset(&buff_out, sizeof(buff_out), 0);
	}
}
