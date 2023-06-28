package com.icanfarm.icanfarm.controller;

import com.icanfarm.icanfarm.dto.HubInfoDTO;
import com.icanfarm.icanfarm.dto.MemberJoinDTO;
import com.icanfarm.icanfarm.dto.RPiPwDTO;
import com.icanfarm.icanfarm.service.MemberService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api")
@Slf4j
@CrossOrigin
public class MemberController {

    private final MemberService memberService;
    private final BCryptPasswordEncoder encoder;

    @PostMapping("/login")
    public ResponseEntity login(@RequestBody MemberJoinDTO memberJoinDTO){
        Long memberId = memberService.login(memberJoinDTO);

        return ResponseEntity.ok().body(memberId);
    }

    @GetMapping("/rpi/pw/{member_id}")
    public ResponseEntity getRPiPasswd(@PathVariable("member_id")Long id){
        String pw = memberService.getRPiPasswd(id);

        return ResponseEntity.ok().body(pw);
    }

    @PostMapping("/rpi/pw/{member_id}")
    public ResponseEntity setRPiPasswd(@PathVariable("member_id")Long id, @RequestBody RPiPwDTO rpiPwDTO){
        log.debug("입력 받은 RPi 비밀번호 : " + rpiPwDTO.getPwd());

        memberService.setRPiPasswd(id, rpiPwDTO);
        return ResponseEntity.ok("비밀번호가 성공적으로 변경됐습니다.");
    }

    @GetMapping("/hub/{member_id}")
    public ResponseEntity getHubList(@PathVariable("member_id")Long id){
        List<HubInfoDTO> hubs = memberService.getHubList(id);
        return ResponseEntity.ok().body(hubs);
    }

    @GetMapping("/hub/default/{member_id}")
    public ResponseEntity getDefaultHub(@PathVariable("member_id")Long id){
        Long hubId = memberService.getDefaultHub(id);
        return ResponseEntity.ok().body(hubId);
    }

    @GetMapping("/memberId/{email}")
    public ResponseEntity getMemberId(@PathVariable("email")String email){
        Long id = memberService.getMemberId(email);
        return ResponseEntity.ok().body(id);
    }
}