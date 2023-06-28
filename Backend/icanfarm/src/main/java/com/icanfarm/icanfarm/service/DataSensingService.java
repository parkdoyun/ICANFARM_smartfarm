package com.icanfarm.icanfarm.service;

import com.icanfarm.icanfarm.config.MqttConfig;
import com.icanfarm.icanfarm.controller.websocketHandler;
import com.icanfarm.icanfarm.entity.FarmSensor;
import com.icanfarm.icanfarm.entity.Hub;
import com.icanfarm.icanfarm.exception.HubNotExistException;
import com.icanfarm.icanfarm.repository.FarmSensorRepository;
import com.icanfarm.icanfarm.repository.HubRepository;
import lombok.RequiredArgsConstructor;
import org.apache.tomcat.util.json.JSONParser;
import org.springframework.stereotype.Service;
import org.springframework.web.socket.TextMessage;

import java.io.IOException;
import java.util.LinkedHashMap;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class DataSensingService {
    private final FarmSensorRepository farmSensorRepository;
    private final MqttConfig.OutboundGateway outboundGateway;
    private final HubService hubService;
    private final HubRepository hubRepository;
    //private final WebsocketController webSocket = new WebsocketController();
    private final websocketHandler ws = new websocketHandler();

    public void saveSensorData(Long hubId, String name, Double value) {
        FarmSensor farmSensor = FarmSensor.builder()
                .hubId(hubId)
                .name(name)
                .value(value)
                .build();

        farmSensorRepository.save(farmSensor);

        // 범위 확인해서 범위 넘을 때에는 소켓통신으로 웹에 전송
        // db에서 범위 확인
        Optional<Hub> hubOpt = hubRepository.findById(hubId);

        if(hubOpt.isEmpty())
            throw new HubNotExistException();

        Hub hub = hubOpt.get();
        Double range, setting;
        String sensor_name;
        if(name.equals("temp")) { range = hub.getTempRate(); setting = hub.getTempSetting(); sensor_name = "온도"; } // 온도
        else { range = hub.getHumidRate(); setting = hub.getHumidSetting(); sensor_name = "습도"; } // 습도

        if(value >= setting - range && value <= setting + range) return;

        try
        {
            // 비교
            if (value < setting - range) // 범위 넘으면 소켓 통신
            {
                String send_str = sensor_name + "가 너무 낮습니다.";
                websocketHandler.CLIENTS.entrySet().forEach(arg -> {
                    try {
                        arg.getValue().sendMessage(new TextMessage(send_str));
                    } catch (IOException e)
                    {
                        e.printStackTrace();
                    }
                });
            }
            else {
                String send_str = sensor_name + "가 너무 높습니다.";
                websocketHandler.CLIENTS.entrySet().forEach(arg -> {
                    try {
                        arg.getValue().sendMessage(new TextMessage(send_str));
                    } catch (IOException e)
                    {
                        e.printStackTrace();
                    }
                });
            }

        }
        catch (Exception e)
        {
            e.getStackTrace();
        }
    }

    public void sendSensorData(Long hubId) {
        try{
            //outboundGateway.sendToMqtt(hubService.getHubInfo(hubId), MqttConfig.OutboundGateway.INITIAL_TOPIC + hubId.toString());
            // 처음부터 server/temp/set, server/temp/range, server/humid/set, server/humid/range로 보내기
            // getHubInfo(hubId)로 받아서 json 내가 파싱해서 보내자
            String tmp_info = hubService.getHubInfo(hubId);
            JSONParser jsonParser = new JSONParser(tmp_info);
            LinkedHashMap<String, Object> json = jsonParser.object();

            Object temp_set = json.get("tempSettingValue");
            String temp_set_str = String.valueOf(temp_set);

            Object temp_range = json.get("tempRangeValue");
            String temp_range_str = String.valueOf(temp_range);

            Object humid_set = json.get("humidSettingValue");
            String humid_set_str = String.valueOf(humid_set);

            Object humid_range = json.get("humidRangeValue");
            String humid_range_str = String.valueOf(humid_range);

            // 각각 보내기
            outboundGateway.sendToMqtt(temp_set_str, "server/temp/set/" + hubId);
            outboundGateway.sendToMqtt(temp_range_str, "server/temp/range/" + hubId);
            outboundGateway.sendToMqtt(humid_set_str, "server/humid/set/" + hubId);
            outboundGateway.sendToMqtt(humid_range_str, "server/humid/range/" + hubId);

            outboundGateway.sendToMqtt(hubService.getHubPasswd(hubId), MqttConfig.OutboundGateway.PASSWORD_TOPIC + hubId);
            //outboundGateway.sendToMqtt(hubService.getHubPasswd(hubId), MqttConfig.OutboundGateway.PASSWORD_TOPIC + hubId);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void sendHubPasswod(Long hubId) {
        try{
            System.out.println("!!!!!!!!![sendHubPasswd]PASSWORD : " + hubService.getHubPasswd(hubId));
            outboundGateway.sendToMqtt(hubService.getHubPasswd(hubId), MqttConfig.OutboundGateway.PASSWORD_TOPIC + hubId);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void sendHubPasswod(String passwd, Long hubId) {
        try{
            outboundGateway.sendToMqtt(passwd, MqttConfig.OutboundGateway.PASSWORD_TOPIC + hubId);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void changeSensorTarget(String name, Long hubId, Double value) {
        try{
            outboundGateway.sendToMqtt(value.toString(), "server/"+ name + "/set/" + hubId);
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void changeSensorRange(String name, Long hubId, Double value) {
        try{
            outboundGateway.sendToMqtt(value.toString(),  "server/" + name + "/range/" + hubId);
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void saveSensorTargetValue(Long hubId, String name, Double value) {
        hubService.setSensorTarget(name, hubId, value);
    }

    public void saveSensorRangeValue(Long hubId, String name, Double value) {
        hubService.setSensorRange(name, hubId, value);
    }
}
