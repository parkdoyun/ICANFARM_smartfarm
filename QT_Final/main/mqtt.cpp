#include "mqtt.h"

std::string PWD = "123456";
double TEMP_SET = 30.0;
double TEMP_RANGE;
double HUMID_SET = 64.0;
double HUMID_RANGE;
int CO2_SET = 400;
int CO2_RANGE;

void MqttCallback::connection_lost(const std::string& cause)
{
    std::cout << "Connection lost: " << cause << std::endl;

    while (true)
    {
        // 연결이 끊겼을 때 재연결을 시도
        try
        {
            std::cout << "Trying to reconnect\n";
            mqtt::token_ptr conntok = mqtt_client.connect(connOpts);
            conntok->wait();
            std::cout << "Reconnected." << std::endl;
            break;
        }
        catch (const mqtt::exception& exc)
        {
            std::cerr << "Error: " << exc.what() << std::endl;
        }
    }
}

void MqttCallback::message_arrived(mqtt::const_message_ptr msg)
{
    std::string topic = msg->get_topic();
    std::string data = msg->to_string();
    std::cout << "MQTT received on '" << topic << "' : " << data << std::endl;

    if (topic == "server/admin/password/" + CLIENT_ID)
    {
        PWD = msg->to_string();
        std::cout << "PWD changed to " << PWD << std::endl;
    }
    else if (topic == "server/temp/set/" + CLIENT_ID)
    {
        TEMP_SET = stod(msg->to_string());
        emit sendServerTemp(TEMP_SET); // emit signal temp
        std::cout << "TEMP set at " << TEMP_SET << std::endl;
    }
    else if (topic == "server/temp/range/" + CLIENT_ID)
    {
        TEMP_RANGE = stod(msg->to_string());
        std::cout << "TEMP tolerance range : " << TEMP_RANGE << std::endl;
    }
    else if (topic == "server/humid/set/" + CLIENT_ID)
    {
        HUMID_SET = stod(msg->to_string());
        emit sendServerHumid(HUMID_SET); // emit signal humid
        std::cout << "HUMID set at " << HUMID_SET << std::endl;
    }
    else if (topic == "server/humid/range/" + CLIENT_ID)
    {
        HUMID_RANGE = stod(msg->to_string());
        std::cout << "HUMID tolerance range : " << HUMID_RANGE << std::endl;
    }
    else if (topic == "server/co2/set/" + CLIENT_ID)
    {
        CO2_SET = stoi(msg->to_string());
        emit sendServerCo2(CO2_SET); // emit signal co2
        std::cout << "CO2 set at " << CO2_SET << std::endl;
    }
    else if (topic == "server/co2/range/" + CLIENT_ID)
    {
        CO2_RANGE = stoi(msg->to_string());
        std::cout << "CO2 tolerance range : " << CO2_RANGE << std::endl;
    }
}
