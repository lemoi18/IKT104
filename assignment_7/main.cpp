#include "mbed.h"
#include "HTS221Sensor.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include "MbedJSONValue.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms



void post_request_string(HTS221Sensor *sensor, float *temp,float *hum,  char *returnS){
     char request[1000] = "POST /api/v1/KO4ihjy1NJHe38L8GuVH/telemetry HTTP/1.1\r\n"
                           "Host: 192.168.68.104:9090\r\n"
                           "Content-Type: application/json\r\n"
                           "Content-Length: ";
                            
                           
sensor->get_temperature(temp);  sensor->get_humidity(hum);

    

    char json[250] = {0};
    


    sprintf(json, "{\"temperature\":\"%.1f\", \"humidity\" : \"%.1f\"}", *temp, *hum);
    
 
    uint8_t content_length = strlen(json);
    char number[16] = {0};

    sprintf(number, "%i\r\n\r\n", content_length);

    char eof[4]= {"\r\n"};

    
    strcat(request, number);
    strcat(request, json);
    strcat(request, eof);

    strcpy(returnS, request);

    //printf("request: %s", returnS);



}

nsapi_size_or_error_t send_request(TCPSocket &socket, const char *request) {
    // The request might not be fully sent in one go, so keep track of how much we have sent
    nsapi_size_t bytes_to_send = strlen(request);
    nsapi_size_or_error_t bytes_sent = 0;
 
    printf("Sending message: \n%s", request);
 
    // Loop as long as there are more data to send
    while (bytes_to_send) {
        // Try to send the remaining data. send() returns how many bytes were actually sent
        bytes_sent = socket.send(request + bytes_sent, bytes_to_send);
 
        // Negative return values from send() are errors
        if (bytes_sent < 0) {
            return bytes_sent;
        } else {
            printf("sent %d bytes\n", bytes_sent);
        }
 
        bytes_to_send -= bytes_sent;
    }
 
    printf("Complete message sent\n");
 
    return 0;
}
nsapi_size_or_error_t read_response(TCPSocket &socket) {
    // We need to read the response into memory. The destination is called a buffer
    char buffer[1000];
    
    int remaining_bytes = 1000;
    int received_bytes = 0;
    char *p;
 
    // Loop as long as there are more data to read. We might not read all in one call to recv()
    while (remaining_bytes > 0) {
        nsapi_size_or_error_t result = socket.recv(buffer + received_bytes, remaining_bytes);
 
         
    
        // If the result is 0 there are no more bytes to read
        if (result == 0) {
            break;
        }
 
        // Negative return values from recv() are errors
        if (result < 0) {
            return result;
        }
 
        received_bytes += result;
        remaining_bytes -= result;
 
    }
 
    printf("received %d bytes:\n%.*s\n", received_bytes, strstr(buffer, "\n") - buffer, buffer); 
    //printf("received %d bytes:\r\n%.*s\r\n\r\n", received_bytes, strstr(buffer, "{"), buffer);
    
 return 0;

}
int main() {

    
    DevI2C i2c(PB_11, PB_10);
    HTS221Sensor sensor(&i2c);
    sensor.init(nullptr);
    sensor.enable();
    char  returnS[2000];

    // Get pointer to default network interface
    NetworkInterface *network = NetworkInterface::get_default_instance();
 
    if (!network) {
        printf("Failed to get default network interface\n");
        while (1);
    }
 
    // Connect to network
    printf("Connecting to the network...\n");
    nsapi_size_or_error_t result = network->connect();
 
    // Check if the connection is successful
    if (result != 0) {
        printf("Failed to connect to network: %d\n", result);
        while (1);
    }
 
    printf("Connection to network successful!\n");
 
    // Create and allocate resources for socket
    TCPSocket socket;
    socket.open(network);
 
    // Create destination address
    SocketAddress address;
 
    // Get IP address of host by name
    result = network->gethostbyname("192.168.68.104", &address);
 
    // Check result
    if (result != 0) {
        printf("Failed to get IP address of host: %d\n", result);
        while (1);
    }
 
    printf("Got address of host\n");
 
    // Set server port number
    address.set_port(9090);
 
    // Connect to server at the given address
    result = socket.connect(address);
 
    // Check result
    if (result != 0) {
        printf("Failed to connect to server: %d\n", result);
        while (1);
    }
 
    printf("Connection to server successful!\n");
    
    float temp, hum;
    while (true) {
    
    
    if (sensor.get_humidity(&hum)!= 0) {
    printf("error");
    }
    if (sensor.get_temperature(&temp)!= 0) {
    printf("error");
    }
    
    
 
post_request_string(&sensor, &temp, &hum, returnS);

result = send_request(socket, returnS);
    ThisThread::sleep_for(2s);
    }
 // Check result
    if (result != 0) {
        printf("Failed to send request: %d\n", result);
        while (1);
    }

}