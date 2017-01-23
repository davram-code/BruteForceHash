#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <poll.h>

class connection_t
{
  private:
    int socket_fd;
    bool am_i_connected = false;
    bool create_socket(int *file_descriptor);

  public:
    bool is_connected();
    void assign_connected_fd(int assigned_fd);

    bool send(void *buffer, size_t buffer_length);
    bool receive(void **buffer, size_t buffer_length);

    bool connect_to(const char *ip_address, unsigned short port);
    bool await_connection_on(unsigned short port);

    template <class struct_type>
    void send_as(struct_type *input);
    template <class struct_type>
    void send_as(struct_type *input,int structSize);
    template <class struct_type>
    void receive_as(struct_type **output_buffer);

    static bool poll(connection_t *connections, unsigned short connections_count, unsigned short timeout_useconds, bool *output_buffer);
    static pthread_t *await_multiple_connections(connection_t *connections, unsigned short connections_count, unsigned short port);
};

struct listen_info_t
{
    connection_t *connections;
    unsigned short connections_count;
    unsigned short port;
};
struct ConnexionsVector
{
    connection_t *connections;
    
};

template <class struct_type>
void connection_t::send_as(struct_type* input){
    void* send_buffer = new unsigned char[sizeof(struct_type)];
    
    memcpy(send_buffer,input,sizeof(struct_type));
    this->send(send_buffer,sizeof(struct_type));

    delete[] send_buffer;
}

template <class struct_type>
void connection_t::send_as(struct_type* input, int struct_size){
    void* send_buffer = new unsigned char[struct_size];
    
    memcpy(send_buffer,input,sizeof(struct_type));
    this->send(send_buffer,sizeof(struct_type));

    delete[] send_buffer;
}


/*If output buffer is nullptr, allocate memory*/
template <class struct_type>
void connection_t::receive_as(struct_type** output_buffer){
    if(*output_buffer == nullptr)
        *output_buffer = new struct_type;//CHECK NIca

    unsigned char* receive_buffer = new unsigned char[sizeof(struct_type)];

    receive((void**)(&receive_buffer),sizeof(struct_type));
    memcpy(*output_buffer,receive_buffer,sizeof(struct_type));

    delete[] receive_buffer;
}