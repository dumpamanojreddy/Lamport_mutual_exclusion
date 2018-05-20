/* utilities.c: semsetall(), p(), and v() functions  */
/*              for shared memory / semaphore donuts */


#include "ddonuts.h"

int    p(semidgroup, donut_type)
        int semidgroup, donut_type;
{
        struct sembuf semopbuf;

        semopbuf.sem_num=donut_type;
        semopbuf.sem_op=(-1);
        semopbuf.sem_flg=0;

        if(semop(semidgroup, &semopbuf,1) == -1){
                return (-1);
        }
	return(0);
}

int    v(int semidgroup, int donut_type)
{
        struct sembuf semopbuf;

        semopbuf.sem_num=donut_type;
        semopbuf.sem_op=(+1);
        semopbuf.sem_flg=0;

        if(semop(semidgroup, &semopbuf,1) == -1){
                return(-1);
        }
	return(0);
}


int    semsetall(int semgroup, int number_in_group, int set_all_value)
{
        int     i,j,k;
        union semun {
               int val;                    /* value for SETVAL */
               struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
               unsigned short int *array;  /* array for GETALL, SETALL */
               struct seminfo *__buf;      /* buffer for IPC_INFO */
        }my_union;

        my_union.val = set_all_value;

        for(i=0; i<number_in_group; i++){
          if(semctl(semgroup, i, SETVAL, my_union) == -1){
                return(-1);
          }
        }
	return(0);
}

