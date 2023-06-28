package com.icanfarm.icanfarm.service;

import com.icanfarm.icanfarm.dto.HubInfoDTO;
import com.icanfarm.icanfarm.dto.MemberJoinDTO;
import com.icanfarm.icanfarm.dto.RPiPwDTO;
import com.icanfarm.icanfarm.entity.Hub;
import com.icanfarm.icanfarm.entity.Member;
import com.icanfarm.icanfarm.exception.HubNotExistException;
import com.icanfarm.icanfarm.exception.PasswdInvalidException;
import com.icanfarm.icanfarm.exception.UserNotExistException;
import com.icanfarm.icanfarm.repository.HubRepository;
import com.icanfarm.icanfarm.repository.MemberRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class MemberService {

    private final MemberRepository memberRepository;
    private final HubRepository hubRepository;
    private final BCryptPasswordEncoder encoder;
    private final DataSensingService dataSensingService;

    public Long login(MemberJoinDTO memberJoinDTO) {

        Optional<Member> findMemberOpt = memberRepository.findByEmail(memberJoinDTO.getEmail());

        if(findMemberOpt.isEmpty())
            throw new UserNotExistException();

        Member findMember = findMemberOpt.get();

        if(!encoder.matches(memberJoinDTO.getPasswd(), findMember.getPasswd()))
            throw new PasswdInvalidException();

        return findMember.getId();
    }

    public Member getMember(Long memberId){
        Optional<Member> findMember = memberRepository.findById(memberId);

        if(findMember.isEmpty())
            throw new UserNotExistException();

        return findMember.get();
    }

    public String getRPiPasswd(Long id) {
        Member member = getMember(id);

        return member.getRpiPasswd();
    }

    public void setRPiPasswd(Long id, RPiPwDTO rpiPwDTO) {
        Member member = getMember(id);
        String pw = rpiPwDTO.getPwd();

        member.changeRPiPasswd(pw);
        memberRepository.save(member);

        for(Hub h : member.getHubs()){
            dataSensingService.sendHubPasswod(pw, h.getId());
        }
    }

    public List<HubInfoDTO> getHubList(Long id) {
        Member member = getMember(id);
        return member.getHubs().stream().map(
                h -> HubInfoDTO.builder()
                        .id(h.getId())
                        .build()
        ).collect(Collectors.toList());
    }

    public Long getDefaultHub(Long id) {
        Member member = getMember(id);
        Optional<Hub> findHubOpt = hubRepository.findDefaultHub(member);
        if(findHubOpt.isEmpty())
            throw new HubNotExistException();

        return findHubOpt.get().getId();
    }

    public Long getMemberId(String email)
    {
        Optional<Member> findMemberOpt = memberRepository.findByEmail(email);

        if(findMemberOpt.isEmpty())
            throw new UserNotExistException();

        Member findMember = findMemberOpt.get();

        return findMember.getId();
    }

}
