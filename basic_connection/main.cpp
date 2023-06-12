#include <aws/crt/Api.h>
#include <aws/crt/UUID.h>
#include "CommandLineUtils.h"

using namespace Aws::Crt;

int main(int argc, char *argv[]){
    // do a global initialization for the API
    ApiHandle apiHandle;

    Utils::cmdData cmdData = Utils::parseSampleInputBasicConnect(argc, argv, &apiHandle);
     
    // create an mqtt builder and populate it with data from cmdData
    auto clientConfigBuilder = Aws::Iot::MqttClientConnectionConfigBuilder(cmdData.input_cert.c_str(), 
    cmdData.input_key.c_str());

    clientConfigBuilder.WithEndpoint(cmdData.input_endpoint);
    if (cmdData.input_ca != ""){
        clientConfigBuilder.WithCertificateAuthority(cmdData.input_ca.c_str());
    }
    if (cmdData.input_proxyHost != ""){
        Aws::Crt::Http::HttpClientConnectionProxyOptions proxyOptions;
        proxyOptions.HostName = cmdData.input_proxyHost;
        proxyOptions.Port = static_cast<uint16_t>(cmdData.input_proxyPort);
        proxyOptions.AuthType = Aws::Crt::Http::AwsHttpProxyAuthenticationType::None;
        clientConfigBuilder.WithHttpProxyOptions(proxyOptions);
    }
    if (cmdData.input_port != 0){
        clientConfigBuilder.WithPortOverride(static_cast<uint16_t>(cmdData.input_port));
    }

    // create an mqtt connection from the mqtt builder
    auto clientConfig = clientConfigBuilder.Build();
    if(!clientConfig){
        fprintf(
            stderr,
            "Client Configuration Initialization failed with Error %s\n",
            Aws::Crt::ErrorDebugString(clientConfig.LastError())
        );
        exit(-1);
    }
    Aws::Iot::MqttClient client = Aws::Iot::MqttClient();
    auto connection = client.NewConnection(clientConfig);
    if(!*connection){
        fprintf(
            stderr,
            "MQTT Connection Creation Failed with error %s\n",
            Aws::Crt::ErrorDebugString(connection->LastError())
        );
        exit(-1);
    }

    // condition variable to check connection completion
    std::promise<bool> connectionCompletedPromise;
    std::promise<void> connectionClosedPromise;

    // invoke when an MQTT connection ahas completed or failed
    auto onConnectionCompleted = 
    [&] (Aws::Crt::Mqtt::MqttConnection &, int errorCode, Aws::Crt::Mqtt::ReturnCode returnCode, bool){
        if (errorCode){
            fprintf(stdout, "Connection failed with error %s\n", Aws::Crt::ErrorDebugString(errorCode));
            connectionCompletedPromise.set_value(false);
        }
        else{
            fprintf(stdout, "Connection Completed with return code %d\n", returnCode);
            connectionCompletedPromise.set_value(true);
        }
    };
    /* the above is a lambda function assigned to the variable onConnectionCompleted.
    it is used as a callback function when mqtt connection is completed */

    // invoke when an mqtt connection is lost or interrupted
    auto onInterrupted = [&](Aws::Crt::Mqtt::MqttConnection &, int error){
        fprintf(stdout, "Connection interrrupted with error %s\n", Aws::Crt::ErrorDebugString(error));
    };

    // invoke when mqtt connection is lost/interrupted but recconnected succesfully
    auto onResumed = [&](Aws::Crt::Mqtt::MqttConnection &, Aws::Crt::Mqtt::ReturnCode, bool){
        fprintf(stdout, "Connection Resumed\n");
    };

    // invoke when a disconnect message has completed
    auto onDisconnect = [&](Aws::Crt::Mqtt::MqttConnection &){
        fprintf(stdout, "Disconnect Compeleted\n");
        connectionClosedPromise.set_value();
    };

    // Assing Callbacks
    connection->OnConnectionCompleted = std::move(onConnectionCompleted);
    connection->OnDisconnect = std::move(onDisconnect);
    connection->OnConnectionInterrupted = std::move(onInterrupted);
    connection->OnConnectionResumed = std::move(onResumed);

    /* 
    connection - object
    On********** - eventHandler
    -> member access through pointer operator, access member of a class/structure
    */

   /* Run the code sample */
   fprintf(stdout, "Connecting...\n");
   if(connection->Connect(cmdData.input_clientId.c_str(), false /*cleanSession*/, 1000 /*keepAliveTimeSecs*/)){
    fprintf(stderr, "MQTT Connection failed with error %s\n", Aws::Crt::ErrorDebugString(connection->LastError()));
    exit(-1);
   }
   // wait for the OnConnectionCompleted callback t fire, which sets connectionCompletedPromise
   if(connectionCompletedPromise.get_future().get() == false){
    fprintf(stderr, "Connection Failed\n");
    exit(-1);
   } 
   // Disconnect
   if (connection->Disconnect()){
        connectionClosedPromise.get_future().wait();
   }
   return 0;
}

