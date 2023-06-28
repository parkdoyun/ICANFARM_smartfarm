FROM mongo:4.2

COPY ./mongod.conf /etc/mongod.conf

RUN /usr/bin/mongod --fork --logpath /var/log/mongodb.log --config /etc/mongod.conf && \
    sleep 10 && \
    mongo admin --eval 'db.getSiblingDB("admin").createUser({user: "admin", pwd: "admin123", roles: [{role: "root", db: "admin"}]})' && \
    sleep 10 && \
    mongo admin -u admin -p admin123 --eval 'db.getSiblingDB("farmData").createUser({user: "icfarm", pwd: "a206", roles: [{role: "readWrite", db: "farmData"}]})' && \
    sleep 10 && \
    /usr/bin/mongod --shutdown
EXPOSE 27017

CMD ["mongod", "--bind_ip_all", "--config", "/etc/mongod.conf"]

