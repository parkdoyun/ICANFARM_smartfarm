package com.icanfarm.icanfarm.service;

import com.icanfarm.icanfarm.dto.MemberInfoDTO;
import com.icanfarm.icanfarm.dto.MemberJoinDTO;
import com.icanfarm.icanfarm.dto.HubJoinDTO;
import com.icanfarm.icanfarm.dto.RPiRegisterDTO;
import com.icanfarm.icanfarm.entity.Hub;
import com.icanfarm.icanfarm.entity.Member;
import com.icanfarm.icanfarm.exception.EmailDuplicationException;
import com.icanfarm.icanfarm.exception.NoRpiExistException;
import com.icanfarm.icanfarm.exception.SerialDuplicationException;
import com.icanfarm.icanfarm.repository.HubRepository;
import com.icanfarm.icanfarm.repository.MemberRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
@Slf4j
public class AdminService {
    private final MemberRepository memberRepository;
    private final MemberService memberService;
    private final HubRepository hubRepository;
    private final BCryptPasswordEncoder encoder;

    private final int ZERO = 0;

    public void checkEmailDuplication(String email){
        log.debug("들어온 값 : " + email);

        if(memberRepository.findByEmail(email).isPresent())
            throw new EmailDuplicationException();
    }

    public void saveMember(MemberJoinDTO memberJoinDTO) {
        log.debug("들어온 값 : " + memberJoinDTO.toString());

        Member member = Member.builder()
                .name(memberJoinDTO.getName())
                .email(memberJoinDTO.getEmail())
                .passwd(encoder.encode(memberJoinDTO.getPasswd()))
                .build();

        memberRepository.save(member);
    }

    public void checkSerialDuplication(String serial) {
        log.debug("들어온 값 : " + memberRepository);

        if(hubRepository.findBySerial(serial).isPresent())
            throw new SerialDuplicationException();
    }

    public void saveRpi(HubJoinDTO rpiJoinDTO) {
        log.debug("들어온 값 : " + rpiJoinDTO.toString());


        Hub hub = Hub.builder()
                .serial(rpiJoinDTO.getSerial())
                .build();

        hubRepository.save(hub);
    }

    public List<MemberInfoDTO> findOneMember(String email) {
        List<Hub> hubs = memberRepository.findByEmail(email).get().getHubs();

        return hubs.stream().map(
                h -> MemberInfoDTO.builder()
                        .id(h.getMember().getId())
                        .rpiNickname(h.getNickname())
                        .rpiSerial(h.getSerial())
                        .joinDate(h.getJoinDate())
                        .rpiID(h.getId())
                        .build()
        ).collect(Collectors.toList());
    }

    public void registerRPi2Member(RPiRegisterDTO rpiRegisterDTO) {

        Optional<Hub> opHub = hubRepository.findFirstByMemberIsNull();

        if(opHub.isEmpty()) throw new NoRpiExistException();

        Hub hub = opHub.get();
        Member member = memberService.getMember(rpiRegisterDTO.getMemberId());

        int hubCnt = member.getHubs().size();
        hub.registerMember(member, hubCnt + 1);

        if(rpiRegisterDTO.isTempModule())
            hub.useTempModule();

        if(rpiRegisterDTO.isHumidModule())
            hub.useHumidModule();

        if(rpiRegisterDTO.isCo2Module())
            hub.useCo2Module();

        if(rpiRegisterDTO.isFanModule())
            hub.useFanModule();

        if(rpiRegisterDTO.isLightModule())
            hub.useLightModule();

        hubRepository.save(hub);
    }

    public void deleteRPiFromMember(Long memberId, Long rpiId) {
        Hub hub = hubRepository.findById(rpiId).get();
        Member member = memberRepository.findById(memberId).get();

        Boolean flag = hub.getDefaultHub();
        hub.deleteMember();

        hubRepository.save(hub);

        if(flag)
            setNewDefaultHub(member);
    }

    private void setNewDefaultHub(Member member) {
        if(member.getHubs().size() == ZERO)
            return;

        Hub hub = member.getHubs().get(0);
        hub.change2DefaultHub();
        hubRepository.save(hub);
    }

}
