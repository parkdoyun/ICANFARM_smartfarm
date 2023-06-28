package com.icanfarm.icanfarm.dto;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
public class SettingValueDTO {
    private Double value;

    @Builder
    public SettingValueDTO(Double value){
        this.value = value;
    }
}
