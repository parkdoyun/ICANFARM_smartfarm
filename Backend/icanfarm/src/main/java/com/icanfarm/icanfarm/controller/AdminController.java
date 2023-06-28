package com.icanfarm.icanfarm.controller;

import com.icanfarm.icanfarm.dto.MemberInfoDTO;
import com.icanfarm.icanfarm.dto.MemberJoinDTO;
import com.icanfarm.icanfarm.dto.HubJoinDTO;
import com.icanfarm.icanfarm.dto.RPiRegisterDTO;
import com.icanfarm.icanfarm.service.AdminService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/admin")
@RequiredArgsConstructor
@CrossOrigin
public class AdminController {

    private final AdminService adminService;

    @GetMapping("/validation/email/{email}")
    public ResponseEntity checkEmailDuplication(@PathVariable("email") String email){
        adminService.checkEmailDuplication(email);

        return ResponseEntity.ok("사용 가능한 이메일입니다.");
    }

    @PostMapping("/member")
    public ResponseEntity saveMemberInfo(@RequestBody MemberJoinDTO memberJoinDTO){
        adminService.checkEmailDuplication(memberJoinDTO.getEmail());
        adminService.saveMember(memberJoinDTO);

        return ResponseEntity.ok("회원 저장에 성공했습니다.");
    }

    @GetMapping("/validation/serial/{serial}")
    public ResponseEntity checkSerialDuplication(@PathVariable("serial") String serial){
        adminService.checkSerialDuplication(serial);

        return ResponseEntity.ok("등록 가능한 시리얼 번호입니다.");
    }

    @PostMapping("/rpi")
    public ResponseEntity saveRPiInfo(@RequestBody HubJoinDTO rpiJoinDTO){
        adminService.checkSerialDuplication(rpiJoinDTO.getSerial());
        adminService.saveRpi(rpiJoinDTO);

        return ResponseEntity.ok("허브 저장에 성공했습니다.");
    }

    @GetMapping("/member/{email}")
    public ResponseEntity findOneMember(@PathVariable("email") String email){
        return ResponseEntity.ok().body(adminService.findOneMember(email));
    }

    @PostMapping("/member/rpi")
    public ResponseEntity registerRPi2Member(@RequestBody RPiRegisterDTO rpiRegisterDTO){
        adminService.registerRPi2Member(rpiRegisterDTO);

        return ResponseEntity.ok("허브 등록에 성공했습니다.");
    }

    @DeleteMapping("/member/rpi/{member_id}/{rpi_id}")
    public ResponseEntity deleteRPiFromMember(@PathVariable("member_id")Long memberId, @PathVariable("rpi_id")Long rpiId){
        adminService.deleteRPiFromMember(memberId, rpiId);

        return ResponseEntity.ok("허브 삭제에 성공했습니다.");
    }

}
