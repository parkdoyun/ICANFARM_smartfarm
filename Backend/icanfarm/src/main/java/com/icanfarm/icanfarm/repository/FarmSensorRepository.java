package com.icanfarm.icanfarm.repository;

import com.icanfarm.icanfarm.entity.FarmSensor;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.mongodb.repository.Query;
import org.springframework.data.repository.query.Param;

import java.time.LocalDateTime;
import java.util.List;

public interface FarmSensorRepository extends MongoRepository<FarmSensor, Long> {

    @Query("{ 'name' : ?0, 'hubId' : ?1, 'date' : { $gte: ?2, $lte: ?3  } }")
    List<FarmSensor> findFarmSensorsByNameAndHubId(@Param("name") String name, @Param("hubId") Long hubId, @Param("start") LocalDateTime start, @Param("end") LocalDateTime end);
}
