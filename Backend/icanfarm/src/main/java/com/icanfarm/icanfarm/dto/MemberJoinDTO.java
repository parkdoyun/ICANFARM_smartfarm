package com.icanfarm.icanfarm.dto;

import lombok.*;

@Getter
@ToString
@NoArgsConstructor
@AllArgsConstructor
public class MemberJoinDTO {

    private String email;

    private String passwd;

    private String name;
}
