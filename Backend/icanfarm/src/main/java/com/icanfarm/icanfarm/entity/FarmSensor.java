package com.icanfarm.icanfarm.entity;

import lombok.Builder;
import lombok.Getter;
import org.springframework.data.annotation.Id;

import java.time.LocalDateTime;

@Getter
public class FarmSensor {

    @Id
    private String id;
    private Long hubId;
    private String name;
    private Double value;
    private LocalDateTime date;

    @Builder
    public FarmSensor(Long hubId, String name, Double value){
        this.hubId = hubId;
        this.name = name;
        this.value = value;
        this.date = LocalDateTime.now();
    }
}
