#include <iostream>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SSLManager.h>

using namespace Poco;
using namespace Poco::Net;

int main(int argc, const char *argv[]){

try{
    Poco::Net::initializeSSL();
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrHandler = new AcceptCertificateHandler(false);
    Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);

    Poco::Net::SocketAddress address("www.server.com:443");
    Poco::Net::SecureStreamSocket socket(address);
    if (socket.havePeerCertificate())
    {
        X509Certificate cert = socket.peerCertificate();
        std::cout<<cert.issuerName()<<"\n"; 
    }
    else
    {
        std::cout<<"No certificate";
    }

}catch (Poco::Exception& e) {
    std::cout << "Error: " << e.displayText() << "\n";
    return -1;
}
}
