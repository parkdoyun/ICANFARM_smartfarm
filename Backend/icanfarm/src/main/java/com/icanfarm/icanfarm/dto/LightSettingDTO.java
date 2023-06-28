package com.icanfarm.icanfarm.dto;

import lombok.*;

import java.time.LocalDateTime;

@Getter
@Setter
@NoArgsConstructor
public class LightSettingDTO {
    private LocalDateTime startTime;
    private LocalDateTime endTime;

    @Builder
    private LightSettingDTO(LocalDateTime startTime, LocalDateTime endTime){
        this.startTime = startTime;
        this.endTime = endTime;
    }
}
