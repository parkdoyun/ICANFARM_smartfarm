package com.icanfarm.icanfarm.exception;

public class NoRpiExistException extends RuntimeException{
    public NoRpiExistException(){
        super("판매할 수 있는 허브가 없습니다.");
    }
}
