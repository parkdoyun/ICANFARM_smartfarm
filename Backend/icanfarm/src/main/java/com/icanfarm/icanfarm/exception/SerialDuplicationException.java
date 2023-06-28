package com.icanfarm.icanfarm.exception;

public class SerialDuplicationException extends RuntimeException {
    public SerialDuplicationException(){
        super("시리얼 번호가 중복되었습니다.");
    }
}
