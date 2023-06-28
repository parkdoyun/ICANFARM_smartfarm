package com.icanfarm.icanfarm.entity;

import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.ColumnDefault;
import org.hibernate.annotations.DynamicInsert;

import javax.persistence.*;
import java.util.List;

@DynamicInsert
@Entity
@Getter
@NoArgsConstructor
public class Member {

    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private String email;

    private String passwd;

    @ColumnDefault("'ROLE_USER'")
    @Enumerated(EnumType.STRING)
    private MemberRole role;

    @ColumnDefault("'000000'")
    @Column(name = "rpi_pw")
    private String rpiPasswd;

    @OneToMany(mappedBy = "member")
    private List<Hub> hubs;

    @Builder
    public Member(String name, String email, String passwd){
        this.name = name;
        this.email = email;
        this.passwd = passwd;
    }

    public void changeRPiPasswd(String pw){
        this.rpiPasswd = pw;
    }

    public String getRpiPasswd() { return this.rpiPasswd; }
}
