package com.icanfarm.icanfarm.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;
import com.icanfarm.icanfarm.controller.websocketHandler;

@Configuration
@EnableWebSocket
public class WebSocketConfig implements WebSocketConfigurer {
    private final websocketHandler websocketHandler;
    public WebSocketConfig(websocketHandler websocketHandler)
    {
        this.websocketHandler = websocketHandler;
    }

    @Override
    public void registerWebSocketHandlers(WebSocketHandlerRegistry registry)
    {
        registry.addHandler(websocketHandler, "/api/socket").setAllowedOrigins("*");
    }
}
