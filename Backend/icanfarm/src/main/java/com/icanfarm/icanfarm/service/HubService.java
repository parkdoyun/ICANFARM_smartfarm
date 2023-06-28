package com.icanfarm.icanfarm.service;

import com.icanfarm.icanfarm.config.MqttConfig;
import com.icanfarm.icanfarm.dto.*;
import com.icanfarm.icanfarm.entity.FarmSensor;
import com.icanfarm.icanfarm.entity.Hub;
import com.icanfarm.icanfarm.exception.HubNotExistException;
import com.icanfarm.icanfarm.repository.FarmSensorRepository;
import com.icanfarm.icanfarm.repository.HubRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class HubService {
    private final HubRepository hubRepository;
    private final FarmSensorRepository farmSensorRepository;
    private final MqttConfig.OutboundGateway outboundGateway;

    private Hub getHub(Long id){
        Optional<Hub> hubOpt = hubRepository.findById(id);

        if(hubOpt.isEmpty())
            throw new HubNotExistException();

        return hubOpt.get();
    }

    public LightSettingDTO getLightSetting(Long id) {
        Hub hub = getHub(id);

        return LightSettingDTO.builder()
                .startTime(hub.getLightTurnOnTime())
                .endTime(hub.getLightTurnOffTime())
                .build();
    }

    public void setLightSetting(Long id, LightSettingDTO lightSettingDTO) {
        Hub hub = getHub(id);

        hub.changeLightSettings(lightSettingDTO.getStartTime(), lightSettingDTO.getEndTime());
        hubRepository.save(hub);
    }

    public void setAllSetting(Long id, AllSettingDTO AllSettingDTO)
    {
        Hub hub = getHub(id);

        hub.changeAllSettings(AllSettingDTO.getTempTarget(), AllSettingDTO.getTempRange(), AllSettingDTO.getHumidTarget(), AllSettingDTO.getHumidRange(),
                AllSettingDTO.getStartTime(), AllSettingDTO.getEndTime());
        hubRepository.save(hub);
    }

    public List<InfoValueDTO> getDataInfo(String sensor, Long id) {
        LocalDateTime end = LocalDateTime.now();
        LocalDateTime start = end.minus(7, ChronoUnit.DAYS);

        List<FarmSensor> sensors = farmSensorRepository.findFarmSensorsByNameAndHubId(sensor, id, start, end);
        return sensors.stream()
                .sorted(Comparator.comparing(FarmSensor::getDate).reversed())
                .map(
                        s -> InfoValueDTO.builder()
                                .date(s.getDate())
                                .value(s.getValue())
                                .build()
                ).collect(Collectors.toList());
    }

    public String getHubInfo(Long hubId) throws Exception{
        Hub hub = getHub(hubId);
        return hub.getInitialInfoJson();
    }

    public String getHubPasswd(Long hubId){
        Hub hub = getHub(hubId);
        //System.out.println("!!!!!!!!![getHubPasswd]PASSWORD : " + hub.getMember().getPasswd());
        return hub.getMember().getRpiPasswd();
    }

    public SettingValueDTO getTargetValue(String name, Long hubId) {
        Hub hub = getHub(hubId);
        if(name.equals("temp")){
            return SettingValueDTO.builder()
                            .value(hub.getTempSetting())
                    .build();

        }else if(name.equals("humid")){
            return SettingValueDTO.builder()
                    .value(hub.getHumidSetting())
                    .build();
        }
        return null;
    }

    public SettingValueDTO getRangeValue(String name, Long hubId) {
        Hub hub = getHub(hubId);
        if(name.equals("temp")){
            return SettingValueDTO.builder()
                    .value(hub.getTempRate())
                    .build();
        }else if(name.equals("humid")){
            return SettingValueDTO.builder()
                    .value(hub.getHumidRate())
                    .build();
        }
        return null;
    }

    public void setSensorTarget(String name, Long hubId, Double value) {
        Hub hub = getHub(hubId);
        if(name.equals("temp")){
            hub.changeTempTarget(value);
        }else if(name.equals("humid")){
            hub.changeHumidTarget(value);
        }
        hubRepository.save(hub);
    }

    public void setSensorRange(String name, Long hubId, Double value) {
        Hub hub = getHub(hubId);
        if(name.equals("temp")){
            hub.changeTempRange(value);
        }else if(name.equals("humid")){
            hub.changeHumidRange(value);
        }
        hubRepository.save(hub);
    }

    public HubmoduleDTO findModule(Long id) {
        Hub hub = getHub(id);

        return HubmoduleDTO.builder()
                .is_co2(hub.getIsCo2())
                .is_fan(hub.getIsFan())
                .is_humid(hub.getIsHumid())
                .is_light(hub.getIsLight())
                .build();
    }
}
