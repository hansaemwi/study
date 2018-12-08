#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


/* 
 * [return value]
 * 1 : failed create socketpair 
 * 2 : failed write (socket_pair[1])
 * 3 : failed read
 * 4 : failed write (socket_pair[0])
 */

int main(int argc, char **argv)
{
    int ret_val;            /* status return code   */
    int socket_pair[2];     /* pair of sockets      */
    char *p;                /* work pointer         */
    char buf[80];           /* work buffer          */

    /* create a pair of local sockets   */
    ret_val = socketpair(AF_LOCAL, SOCK_STREAM,
                        0, socket_pair);
    
    if ( ret_val == -1 ){
        fprintf(stderr, "%s : socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_pair)",
                strerror(errno));
        return 1;
    }

    /* Write a message to socket socket_pair[1]     */
    ret_val = write(socket_pair[1], p="Hello?", 6);
    if ( ret_val < 0 ){
        fprintf(stderr, "%s : write(%d, \"%s\", %ld)\n",
                strerror(errno), socket_pair[1], p, strlen(p));
        return 2;
    }

    printf("Wrote message \"%s\" on socket_pair[1]\n", p);

    /* Read from socket socket_pair[0]  */
    ret_val = read(socket_pair[0], buf, sizeof buf);
    if ( ret_val < 0 ){
        fprintf(stderr, "%s : read(%d, buf, %ld)\n",
                strerror(errno), socket_pair[0], sizeof buf);
        return 3;
    }

    /* Report received message  */
    buf[ret_val] = 0; /* NULL terminate   */
    printf("Received message \"%s\" from socket socket_pair[0]\n", buf);

    /* Send a reply back to socket_pair[1] from socket_pair[0]  */
    ret_val = write(socket_pair[0], p = "Go away!", 8);
    if ( ret_val < 0 ){
        fprintf(stderr, "%s : write(%d, \"%s\", %ld)\n", 
                strerror(errno), socket_pair[0], p, strlen(p));
        return 4;
    }

    printf("Wrote message \"%s\" on socket_pair[0]\n", p);

    /* Read from socket socket_pair[1]  */
    ret_val = read(socket_pair[1], buf, sizeof buf);
    if ( ret_val < 0 ){
        fprintf(stderr, "%s : read(%d, buf, %ld)\n",
                strerror(errno), socket_pair[1], sizeof buf);
        return 3;
    }

    /* Report message received by socket_pair[0]    */
    buf[ret_val] = 0;   /*  Null terminate  */
    printf("Received message \"%s\" from socket socket_pair[1]\n", buf);

    /* close the sockets    */
    close(socket_pair[0]);
    close(socket_pair[1]);

    puts("Done.");
    return 0;
}
