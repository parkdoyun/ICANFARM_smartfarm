package com.icanfarm.icanfarm.repository;

import com.icanfarm.icanfarm.entity.Hub;
import com.icanfarm.icanfarm.entity.Member;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface HubRepository extends JpaRepository<Hub, Long> {
    Optional<Hub> findBySerial(String serial);

//    @Query("select h from Hub h where h.member is NULL")
    Optional<Hub> findFirstByMemberIsNull();

    @Query("select h from Hub h where h.member = :member and h.defaultHub = true")
    Optional<Hub> findDefaultHub(@Param("member") Member member);
}
