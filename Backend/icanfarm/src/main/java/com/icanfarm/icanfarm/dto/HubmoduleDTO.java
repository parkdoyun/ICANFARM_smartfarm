package com.icanfarm.icanfarm.dto;

import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
public class HubmoduleDTO {
    private Boolean isCo2;
    private Boolean isFan;
    private Boolean isHumid;
    private Boolean isLight;

    @Builder
    public HubmoduleDTO(Boolean is_co2, Boolean is_fan, Boolean is_humid, Boolean is_light)
    {
        this.isCo2 = is_co2;
        this.isFan = is_fan;
        this.isHumid = is_humid;
        this.isLight = is_light;
    }
}
