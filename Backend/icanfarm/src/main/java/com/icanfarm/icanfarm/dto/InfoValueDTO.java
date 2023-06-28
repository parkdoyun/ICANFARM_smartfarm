package com.icanfarm.icanfarm.dto;

import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDateTime;

@Getter
@Setter
@NoArgsConstructor
public class InfoValueDTO {
    private LocalDateTime date;
    private Double value;

    @Builder
    public InfoValueDTO(LocalDateTime date, Double value){
        this.date = date;
        this.value = value;
    }
}
