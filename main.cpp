#include <iostream>
#include <Poco/URI.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/StreamCopier.h>

using namespace Poco;
using namespace Poco::Net;

const std::string URL_INST_DIR("https://api.github.com/zen");
// const std::string URL_INST_DIR("https://api.github.com/repos/mantidproject/"
// "mantid/contents/Code/Mantid/instrument");
// const std::string URL_INST_DIR("https://www.google.com/#q=porsche");

int main(int argc, const char *argv[]) {
  Poco::URI uri(URL_INST_DIR);

  try {
    // initialize ssl
    // Poco::Net::initializeSSL();
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pHandler =
        new AcceptCertificateHandler(true); // was false
    Context::Ptr pContext =
        new Context(Context::CLIENT_USE, "", Context::VERIFY_NONE);
    SSLManager::instance().initializeClient(0, pHandler, pContext);

    // setup the client session
    std::cout << "url=" << URL_INST_DIR << std::endl;
    std::cout << "host=" << uri.getHost() << std::endl;
    std::cout << "port=" << uri.getPort() << std::endl;
    HTTPSClientSession session(uri.getHost(), uri.getPort(), pContext);

    // create a request
    std::cout << "path=" << uri.getPathAndQuery() << std::endl;
    HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPathAndQuery(),
                        HTTPMessage::HTTP_1_1);
    request.set("User-Agent", "MANTID-Instrument-Repo");
    // request.setContentType("application/json; charset=utf-8");
    session.sendRequest(request);

    HTTPResponse res;
    std::istream &rs = session.receiveResponse(res);
    if (res.getStatus() != HTTPResponse::HTTP_OK) { // 200
      std::cout << "Status[" << res.getStatus() << "] " << res.getReason()
                << std::endl;
    } else {
      std::cout << "It worked!!!!!!!!!!!!!!!!!" << std::endl;
      Poco::StreamCopier::copyStream(rs, std::cout);
      std::cout << rs << std::endl;
    }
  }
  catch (Poco::Exception &e) {
    std::cout << "Error: " << e.displayText() << std::endl;
    return -1;
  }
  return 0;
}
