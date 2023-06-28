package com.icanfarm.icanfarm.exception;

import org.springframework.security.core.Authentication;

public class AuthorizationNotExistException extends RuntimeException {
    public AuthorizationNotExistException(){
        super("권한이 존재하지 않습니다.");
    }
}
