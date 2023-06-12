#include <aws/crt/Api.h>
#include <aws/crt/UUID.h>
#include "CommandLineUtils.h"

using namespace Aws::Crt;

int main(int argc, char *argv[]){
    // do a global initialization for the API
    ApiHandle apiHandle;

    Utils::cmdData cmdData = Utils::parseSampleInputBasicConnect(argc, argv, &apiHandle);
     
    // create an mqtt builder and populate it with dara from cmdData
    auto clientConfigBuilder = Aws::Iot::MqttClientConnectionConfigBuilder(cmdData.input_cert.c_str(), 
    cmdData.input_key.c_str());
}

