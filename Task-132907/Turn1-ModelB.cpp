
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/ThreadPool.h>
#include <Poco/Thread.h>
#include <iostream>

class AsyncHandler: public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override
    {
        // Handle the request asynchronously by scheduling it on a thread pool
        Poco::ThreadPool::defaultPool().enqueue(std::bind(&AsyncHandler::handleRequestAsync, this, request, response));
    }

private:
    void handleRequestAsync(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    {
        // Simulate expensive task (e.g., rendering)
        Poco::Thread::sleep(2); // Sleep for 2 seconds

        // Prepare the response
        std::stringstream responseContent;
        responseContent << "<html><body><h1>Hello, world!</h1></body></html>";

        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/html");
        response.setContentLength(responseContent.str().length());

        // Send the response
        std::ostream& os = response.send();
        os << responseContent.rdbuf();
    }
};

class AsyncHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override
    {
        return new AsyncHandler;
    }
};

int main()
{
    try
    {
        // Create a server socket on port 8080
        Poco::Net::ServerSocket serverSocket(8080);

        // Create a thread pool with 4 worker threads
        Poco::ThreadPool threadPool(4);
        Poco::ThreadPool::defaultPool().setMaxThreads(4);

        // Create an HTTP server and set the thread pool
        Poco::Net::HTTPServer server(serverSocket, new AsyncHandlerFactory, &threadPool);

        // Start the server
        server.start();
        std::cout << "Server started on port 8080." << std::endl;