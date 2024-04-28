#include "TCPServer.h"
#include <sys/select.h>
#include <iostream>
#include <unistd.h>

namespace pr {


bool TCPServer::startServer(int port) {
    ss = new ServerSocket(port);
    if (ss->isOpen()) {
        while (1) {
            std::cout << "En attente sur le port" << port << std::endl;
            Socket sc = ss->accept();
            if (sc.isOpen()) {
                handleConnection(sc);
            }
        }
        return true;
    }
    return false;
}



}