package com.icanfarm.icanfarm.controller;

import com.icanfarm.icanfarm.config.MqttConfig;
import com.icanfarm.icanfarm.dto.StartingDataDTO;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
public class MqttController {

    private final MqttConfig.OutboundGateway outboundGateway;

    @GetMapping("/")
    public void mqttTest(){
        StartingDataDTO dto = StartingDataDTO.builder()
                .tempSettingValue(10.0)
                .tempRangeValue(3.0)
                .humidSettingValue(20.0)
                .humidRangeValue(6.0)
                .build();

        outboundGateway.sendToMqtt("안녕 ㅎㅎ", "test");

        try{

            outboundGateway.sendToMqtt(dto.toJsonString(), "test");
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
