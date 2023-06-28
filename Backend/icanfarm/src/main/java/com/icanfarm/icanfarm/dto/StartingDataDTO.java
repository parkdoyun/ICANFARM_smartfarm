package com.icanfarm.icanfarm.dto;

import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.*;

@Getter
@Setter
@ToString
@NoArgsConstructor
public class StartingDataDTO {
    private Double tempSettingValue;
    private Double tempRangeValue;
    private Double humidSettingValue;
    private Double humidRangeValue;

    @Builder
    public StartingDataDTO(Double tempSettingValue, Double tempRangeValue, Double humidSettingValue, double humidRangeValue){
        this.tempSettingValue = tempSettingValue;
        this.tempRangeValue = tempRangeValue;
        this.humidSettingValue = humidSettingValue;
        this.humidRangeValue = humidRangeValue;
    }

    public String toJsonString() throws Exception{
        ObjectMapper objectMapper = new ObjectMapper();
        return objectMapper.writeValueAsString(this);
    }

}
