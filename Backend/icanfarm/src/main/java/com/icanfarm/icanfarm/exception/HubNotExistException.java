package com.icanfarm.icanfarm.exception;

public class HubNotExistException extends RuntimeException {
    public HubNotExistException(){
        super("허브가 존재하지 않습니다.");
    }
}
