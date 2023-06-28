package com.icanfarm.icanfarm.controller;

import com.icanfarm.icanfarm.dto.AllSettingDTO;
import com.icanfarm.icanfarm.dto.InfoValueDTO;
import com.icanfarm.icanfarm.dto.LightSettingDTO;
import com.icanfarm.icanfarm.dto.SettingValueDTO;
import com.icanfarm.icanfarm.service.DataSensingService;
import com.icanfarm.icanfarm.service.HubService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api")
@RequiredArgsConstructor
@CrossOrigin
public class HubController {

    private final HubService hubService;
    private final DataSensingService dataSensingService;

    @GetMapping("/moduleInfo/{rpi_id}")
    public ResponseEntity findModule(@PathVariable("rpi_id") Long id){
        return ResponseEntity.ok().body(hubService.findModule(id));
    }
    @GetMapping("/{sensor}/{rpi_id}")
    public ResponseEntity getDataInfo(@PathVariable("sensor")String sensor, @PathVariable("rpi_id") Long id){
        List<InfoValueDTO> values = hubService.getDataInfo(sensor, id);
        return ResponseEntity.ok().body(values);
    }

    @GetMapping("/setting/target/{sensor}/{rpi_id}")
    public ResponseEntity getSensorTarget(@PathVariable("sensor")String sensor, @PathVariable("rpi_id") Long id){
        SettingValueDTO value = hubService.getTargetValue(sensor, id);
        return ResponseEntity.ok().body(value);
    }

    @GetMapping("/setting/range/{sensor}/{rpi_id}")
    public ResponseEntity getSensorRange(@PathVariable("sensor")String sensor, @PathVariable("rpi_id") Long id){
        SettingValueDTO value = hubService.getRangeValue(sensor, id);
        return ResponseEntity.ok().body(value);
    }

    @PostMapping("/setting/target/{sensor}/{rpi_id}")
    public ResponseEntity setSensorTarget(@PathVariable("sensor")String sensor, @PathVariable("rpi_id") Long id, @RequestBody SettingValueDTO settingValueDTO){
        hubService.setSensorTarget(sensor, id, settingValueDTO.getValue());
        dataSensingService.changeSensorTarget(sensor, id, settingValueDTO.getValue());
        return ResponseEntity.ok().body("설정을 변경했습니다.");
    }

    @PostMapping("/setting/range/{sensor}/{rpi_id}")
    public ResponseEntity setSensorRange(@PathVariable("sensor")String sensor, @PathVariable("rpi_id") Long id, @RequestBody SettingValueDTO settingValueDTO){
        hubService.setSensorRange(sensor, id, settingValueDTO.getValue());
        dataSensingService.changeSensorRange(sensor, id, settingValueDTO.getValue());
        return ResponseEntity.ok().body("설정을 변경했습니다.");
    }

    @GetMapping("/setting/light/{rpi_id}")
    public ResponseEntity getLightSetting(@PathVariable("rpi_id") Long id){
        return ResponseEntity.ok().body(hubService.getLightSetting(id));
    }

    @PostMapping("/setting/light/{rpi_id}")
    public ResponseEntity setLightSetting(@PathVariable("rpi_id") Long id, @RequestBody LightSettingDTO lightSettingDTO){
        hubService.setLightSetting(id, lightSettingDTO);
        return ResponseEntity.ok().body("조명 설정을 변경했습니다.");
    }

    @PostMapping("/setting/all/{rpi_id}")
    public ResponseEntity setAllSetting(@PathVariable("rpi_id") Long id, @RequestBody AllSettingDTO AllSettingDTO){
        hubService.setAllSetting(id, AllSettingDTO);
        dataSensingService.changeSensorTarget("temp", id, AllSettingDTO.getTempTarget());
        dataSensingService.changeSensorTarget("humid", id, AllSettingDTO.getHumidTarget());
        return ResponseEntity.ok().body("모든 설정을 변경했습니다.");
    }


}
