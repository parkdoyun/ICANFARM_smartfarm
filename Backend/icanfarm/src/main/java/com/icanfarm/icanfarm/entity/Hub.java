package com.icanfarm.icanfarm.entity;

import com.icanfarm.icanfarm.dto.StartingDataDTO;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.ColumnDefault;
import org.hibernate.annotations.DynamicInsert;

import javax.persistence.*;
import java.time.LocalDateTime;

@DynamicInsert
@Entity
@Getter
@NoArgsConstructor
public class Hub {

    @Id
    @GeneratedValue
    @Column(name = "id")
    private Long id;

    @ManyToOne
    @JoinColumn(name = "member_id")
    private Member member;

    @Column(nullable = false, unique = true)
    private String serial;

    private String nickname;

    @Column(name = "temp_setting")
    @ColumnDefault("0.0")
    private Double tempSetting;

    @Column(name = "temp_rate")
    @ColumnDefault("0.0")
    private Double tempRate;

    @Column(name = "humid_setting")
    @ColumnDefault("0.0")
    private Double humidSetting;

    @Column(name = "humid_rate")
    @ColumnDefault("0.0")
    private Double humidRate;

    @Column(name = "light_turn_on")
    @ColumnDefault("'2000-01-01 00:00:00'")
    private LocalDateTime lightTurnOnTime;

    @Column(name = "light_turn_off")
    @ColumnDefault("'2000-01-01 00:00:00'")
    private LocalDateTime lightTurnOffTime;

    @Column(name = "default_hub")
    @ColumnDefault("false")
    private Boolean defaultHub;

    @Column(name = "is_temp")
    @ColumnDefault("false")
    private Boolean isTemp;

    @Column(name = "is_humid")
    @ColumnDefault("false")
    private Boolean isHumid;

    @Column(name = "is_co2")
    @ColumnDefault("false")
    private Boolean isCo2;

    @Column(name = "is_fan")
    @ColumnDefault("false")
    private Boolean isFan;

    @Column(name = "is_light")
    @ColumnDefault("false")
    private Boolean isLight;

    @Column(name = "join_date")
    private LocalDateTime joinDate;

    public void registerMember(Member member, int cnt){
        this.member = member;
        this.nickname = "hub" + cnt;
        this.joinDate = LocalDateTime.now();
        if(cnt == 1) this.defaultHub = true;
    }

    public void deleteMember() {
        this.member = null;
        this.nickname = null;
        this.joinDate = null;
        this.defaultHub = Boolean.FALSE;
        cleanModuleInfo();
        cleanModuleSettings();
    }

    private void cleanModuleSettings() {
        this.tempSetting = 0.0d;
        this.tempRate = 0.0d;
        this.humidSetting = 0.0d;
        this.humidRate = 0.0d;
        this.lightTurnOffTime = LocalDateTime.of(2000, 1, 1, 0, 0, 0);
        this.lightTurnOnTime = LocalDateTime.of(2000, 1, 1, 0, 0, 0);
    }

    private void cleanModuleInfo() {
        this.isTemp = false;
        this.isHumid = false;
        this.isCo2 = false;
        this.isFan = false;
        this.isLight = false;
    }

    public void change2DefaultHub() {
        this.defaultHub = Boolean.TRUE;
    }

    @Builder
    public Hub(String serial){
        this.serial = serial;
    }

    public void useTempModule() {
        this.isTemp = true;
    }

    public void useHumidModule() {
        this.isHumid = true;
    }

    public void useCo2Module() {
        this.isCo2 = true;
    }

    public void useFanModule() {
        this.isFan = true;
    }

    public void useLightModule() {
        this.isLight = true;
    }

    public void changeLightSettings(LocalDateTime startTime, LocalDateTime endTime) {
        this.lightTurnOnTime = startTime;
        this.lightTurnOffTime = endTime;
    }

    public void changeAllSettings(Double t_T, Double t_R, Double h_T, Double h_R, LocalDateTime st, LocalDateTime et)
    {
        this.tempSetting = t_T;
        this.tempRate = t_R;
        this.humidSetting = h_T;
        this.humidRate = h_R;
        this.lightTurnOnTime = st;
        this.lightTurnOffTime = et;
    }

    public String getInitialInfoJson() throws Exception{
        return StartingDataDTO.builder()
                .tempSettingValue(this.tempSetting)
                .tempRangeValue(this.tempRate)
                .humidSettingValue(this.humidSetting)
                .humidRangeValue(this.humidRate)
                .build()
                .toJsonString();
    }

    public void changeTempTarget(Double value) {
        this.tempSetting = value;
    }

    public void changeHumidTarget(Double value) {
        this.humidSetting = value;
    }

    public void changeTempRange(Double value) {
        this.tempRate = value;
    }

    public void changeHumidRange(Double value) {
        this.humidRate = value;
    }


}
