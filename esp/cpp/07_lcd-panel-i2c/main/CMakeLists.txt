idf_component_register(
    SRCS
    main.cpp display.cpp panel_device.cpp scoped_lock.cpp
    i2c.h time_keeper.h panel.h ssd1306.h
    INCLUDE_DIRS .
    REQUIRES driver
)
