#pragma once

#include <queue>                    // from C++ library
#include <WString.h>                // from DFRobot esp32 library
#include <WiFi.h>                   // from DFRobot esp32 library
#include <ArduinoMqttClient.h>      // from Arduino library 
#include "setting.hpp"              // from src/main/setting.hpp

namespace IoT {

struct Message {
public:
    Message(const String& payload, const String& topic) : 
    m_payload(payload), m_topic(topic) {};

    ~Message() {};

    String payload() const { return this->m_payload; }
    String topic() const { return this->m_topic; }

private:
    String m_payload;
    String m_topic;
};

class Client {

public:
    Client(Setting* settings);
    ~Client();

    void connect();
    void disconnect();

    void subscribe(const String& topic);

    bool pollIncoming();
    void sendMessage(const String& message);
    void sendMessage(const String& message, const String& topic);
    void sendMessage(const Message& message);

    bool hasMessage() const { return !this->m_messageQueue.empty(); }
    Message getMessage();

private:

    Setting* m_settings;
    WiFiClient m_wifiClient;
    MqttClient* m_mqttClient = nullptr;
    
    std::queue<Message> m_messageQueue = std::queue<Message>();
};

}