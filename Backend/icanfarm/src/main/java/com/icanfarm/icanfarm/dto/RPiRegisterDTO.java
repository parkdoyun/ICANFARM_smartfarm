package com.icanfarm.icanfarm.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@NoArgsConstructor
@AllArgsConstructor
public class RPiRegisterDTO {
    private Long memberId;
    private boolean tempModule;
    private boolean humidModule;
    private boolean lightModule;
    private boolean fanModule;
    private boolean co2Module;
}
