create database energy_saver default character set utf8;

use energy_saver;

CREATE TABLE arduino_main_info (
    `arduino_main_name` VARCHAR(50) NOT NULL,
    `arduino_main_num` INT NOT NULL AUTO_INCREMENT,
    CONSTRAINT pk1 PRIMARY KEY (arduino_main_num)
);

CREATE TABLE arduino_sub_info (
    `arduino_main_num` INT NOT NULL,
    `arduino_sub_name` VARCHAR(50) NOT NULL,
    `arduino_sub_num` INT NOT NULL,
    CONSTRAINT pk2 PRIMARY KEY (arduino_main_num , arduino_sub_num)
);
CREATE TABLE user_info (
    `id` VARCHAR(50) NOT NULL,
    `password` VARCHAR(50) NOT NULL,
    `name` VARCHAR(50) NOT NULL,
    `sex` BOOLEAN NOT NULL,
    `address` VARCHAR(100) NOT NULL,
    `phone_num` VARCHAR(50) NOT NULL,
    `email` VARCHAR(100) NOT NULL,
    `arduino_main_num` INT NOT NULL,
    CONSTRAINT pk3 PRIMARY KEY (id),
    CONSTRAINT FOREIGN KEY (arduino_main_num)
        REFERENCES arduino_main_info (arduino_main_num) on update cascade on delete cascade
);

CREATE TABLE main_interval (
    `arduino_main_num` INT NOT NULL,
    `time_interval` TIME NOT NULL,
    CONSTRAINT FOREIGN KEY (arduino_main_num)
        REFERENCES arduino_main_info (arduino_main_num) on update cascade on delete cascade
);

CREATE TABLE main_send (
    `arduino_main_num` INT NOT NULL,
    `time` DATETIME NOT NULL,
    `isPerson` BOOL NOT NULL,
    CONSTRAINT FOREIGN KEY (arduino_main_num)
        REFERENCES arduino_main_info (arduino_main_num) on update cascade on delete cascade
);

CREATE TABLE sub_send (
    `arduino_main_num` INT NOT NULL,
    `arduino_sub_num` INT NOT NULL,
    `time` DATETIME NOT NULL,
    `power` INT NOT NULL,
    CONSTRAINT fk1 FOREIGN KEY (arduino_main_num, arduino_sub_num)
        REFERENCES arduino_sub_info (arduino_main_num , arduino_sub_num)
);