package com.icanfarm.icanfarm.dto;

import lombok.*;

import java.time.LocalDateTime;

@Getter
@Setter
@NoArgsConstructor
public class AllSettingDTO {
    private Double tempTarget;
    private Double tempRange;
    private Double humidTarget;
    private Double humidRange;
    private LocalDateTime startTime;
    private LocalDateTime endTime;

    @Builder
    private AllSettingDTO(Double t_T, Double t_R, Double h_T, Double h_R, LocalDateTime st, LocalDateTime et)
    {
        this.tempTarget = t_T;
        this.tempRange = t_R;
        this.humidTarget = h_T;
        this.humidRange = h_R;
        this.startTime = st;
        this.endTime = et;
    }

}
