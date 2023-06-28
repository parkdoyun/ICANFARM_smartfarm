package com.icanfarm.icanfarm.entity;

import lombok.Builder;
import lombok.Getter;
import org.springframework.data.annotation.Id;

import java.time.LocalDateTime;

@Getter
public class FarmLog {
    @Id
    private String id;

    private Long hubId;
    private FarmLogLevel level;
    private LocalDateTime date;
    private String message;

    @Builder
    public FarmLog(Long hubId, FarmLogLevel level, LocalDateTime date, String message){
        this.hubId = hubId;
        this.level = level;
        this.date = date;
        this.message = message;
    }
}
