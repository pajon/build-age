//
//  Server.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Server.h"

bool Server::shutdown = false;

static void write_to_file_cb(int severity, const char *msg)
{
    const char *s;

    switch (severity) {
        case _EVENT_LOG_DEBUG: s = "debug"; break;
        case _EVENT_LOG_MSG:   s = "msg";   break;
        case _EVENT_LOG_WARN:  s = "warn";  break;
        case _EVENT_LOG_ERR:   s = "error"; break;
        default:               s = "?";     break; /* never reached */
    }
    printf("[%s] %s\n", s, msg);
}

bool Server::isShutdown() {
    return shutdown;
}

void Server::startServer(int port) {
    int sock;
    event *ev_accept;
    struct sockaddr_in server_addr;
    
    
    event_enable_debug_mode();
    event_set_log_callback(write_to_file_cb);
    
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // INADDR_ANY;
    server_addr.sin_port = htons(2000);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock < 0) {
        printf("ERROR opening socket\n");
        exit(1);
    }

    if(bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("ERROR binding socket\n");
        exit(1);
    }
    
    if(listen(sock, 5) < 0) {
        perror("ERROR listening");
        exit(1);
    }
    
    /*
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    */
    
    printf("DEBUG: listening\n");
    
    
    if(evthread_use_pthreads() < 0) {
        perror("failed start event thread");
        exit(1);
    }
    
    
    base = event_base_new();
    evutil_make_socket_nonblocking(sock);
    
    startWorkers();
    
    ev_accept = event_new(base, sock, EV_READ|EV_PERSIST, Server::acceptCallback, (void *)this);
    
    event_add(ev_accept, NULL);
    
    event_base_dispatch(base);
    event_base_free(base);
    base = NULL;
    
    close(sock);
}

event_base *Server::getBase() {
    return base;
}

void Server::startWorkers() {
    
    worklist *w;
    
    for(int i=0; i < NUM_WORKERS; i++) {
        w = (worklist *)malloc(sizeof(worklist));
        w->w = new Worker(i);
        
        pthread_create(
                       w->w->getThread(),
                       NULL,
                       Worker::startThread,
                       (void *)w->w
        );
        
        workers.push_back(*w);
    }
}

void Server::acceptCallback(int fd, short ev, void *arg) {
    int client_sock;
    
    Server *s = (Server *)arg;
    
    struct sockaddr_in client_addr;
    socklen_t client_length = sizeof(client_addr);
    
    client_sock = accept(fd, (sockaddr *)&client_addr, &client_length);
    if(client_sock < 0) {
        perror("client accept");
        return;
    }
    
    if(evutil_make_socket_nonblocking(client_sock) < 0) {
        perror("client non-block");
        close(client_sock);
        return;
    }
    
    
    Client *c = new Client();
    c->setSock(client_sock);
    
    // CREATE EVENT
    event *e = event_new(s->getBase(), client_sock, EV_READ|EV_PERSIST, Worker::readBuffer, (void *)c);
    event_add(e, NULL);
    
    // SET EVENT
    c->setEvent(e);

    s->addClient(c);
}

void Server::addClient(Client *c) {
    unsigned int num = UINT_MAX;
    
    worklist *wtmp = NULL;
    Worker *work;
    
    pthread_mutex_lock(&mutex);
    
    unsigned int size = workers.size();
    
    for(int i=0; i < size;i++) {
        wtmp = &workers.front();
        if(wtmp->w->getNum() < num) {
            work = wtmp->w;
            num = wtmp->w->getNum();
        }
        
        workers.pop_front();
        workers.push_back(*wtmp);
    }
    
    printf("WORKER ID:%d\n", work->getID());
    
    pthread_mutex_unlock(&mutex);
    
    work->addClient(c);
}
