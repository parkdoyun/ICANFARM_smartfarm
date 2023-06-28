package com.icanfarm.icanfarm.exception;

public class EmailDuplicationException extends RuntimeException {

    public EmailDuplicationException(){
        super("이메일이 중복되었습니다.");
    }
}
