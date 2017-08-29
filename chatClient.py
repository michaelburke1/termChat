# chat_client.py
# based on unix echo client

import sys
import socket
import select

def chat_client():
    if(len(sys.argv) < 3) :
        print 'Usage : python ./chat_client.py [IP] [PORT]'
        sys.exit()

    host = sys.argv[1]
    port = int(sys.argv[2])

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)

    # connect to server
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()

    print 'Connected to remote host. Please enter a username:'
    username = sys.stdin.readline()
    username = username[:-1]
    print 'Thank you, you are now known as {}! Use "/" for commands and enjoy chatting!!'.format(username)
    sys.stdout.write('[Me: {}] '.format(username)); sys.stdout.flush()

    # set the username on the server as well as the client
    s.send('/initUsr {}'.format(username))

    while 1:
        socket_list = [sys.stdin, s]

        # Get the list sockets which are readable
        read_sockets, write_sockets, error_sockets = select.select(socket_list , [], [])

        for sock in read_sockets:
            if sock == s:
                # incoming message from remote server, s
                data = sock.recv(4096)
                if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
                else :
                    #print data
                    sys.stdout.write(data)
                    sys.stdout.write('[Me: {}] '.format(username)); sys.stdout.flush()

            else :
                # user entered a message
                msg = sys.stdin.readline()
                s.send(msg)
                sys.stdout.write('[Me: {}] '.format(username)); sys.stdout.flush()

if __name__ == "__main__":

    sys.exit(chat_client())

