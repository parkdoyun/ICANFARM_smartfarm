package com.icanfarm.icanfarm.controller;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;

import org.springframework.stereotype.Component;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

@Component
public class websocketHandler extends TextWebSocketHandler {
    public static final ConcurrentHashMap<String, WebSocketSession> CLIENTS = new ConcurrentHashMap<String, WebSocketSession>();

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        CLIENTS.put(session.getId(), session);
        System.out.println("!!!!!!!!!!!!!!!!!WEBSOCKET GOOD");
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        CLIENTS.remove(session.getId());
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        String id = session.getId();  //메시지를 보낸 아이디
        System.out.println("!!!!!!!!!!!!!!!!!WEBSOCKET" + message.getPayload());

        CLIENTS.entrySet().forEach( arg->{
            try {
                    arg.getValue().sendMessage(message);
                    System.out.println("!!!!!!!!!!!!!!!!!WEBSOCKET" + message.toString());
                } catch (IOException e) {
                    e.printStackTrace();
                }
        });

    }

}
