package com.icanfarm.icanfarm.dto;

import lombok.Builder;
import lombok.Getter;

import java.time.LocalDateTime;

@Getter
@Builder
public class MemberInfoDTO {

    private Long id;

    private String rpiNickname;

    private String rpiSerial;

    private LocalDateTime joinDate;

    private Long rpiID;
}
