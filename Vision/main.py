import sensor, image, time, math,lcd
from pyb import UART, Pin, Timer

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
clock = time.clock()

# 初始化串口
uart = UART(3, 115200)  # 根据实际串口连接配置

# 颜色阈值
red_threshold = (14, 41, 28, 58, 16, 47) # 红色阈值
green_threshold = (26, 62, -58, -33, -34, 52) # 绿色阈值
blue_threshold = (25, 88, -13, 33, -55, -10) # 蓝色阈值

recv_data=""
WRK_flag=0
Blok_Object=1
def Uart_recv():  # 串口接收数据
    global WRK_flag

    if (uart.any()):   # 更新串口接收数据
        recv_data = eval(str(uart.read()))

        print(recv_data)
        #uart.write(recv_data)
        if (recv_data!="") :
            print("Openmv has recved CMD data.")
        if ("CR" in recv_data):
            WRK_flag=1
            if("RED" in recv_data):
                Blok_Object=1
            elif("GREEN" in recv_data):
                Blok_Object=2
            elif("GREEN" in recv_data):
                Blok_Object=3
            else:Blok_Object=0
        elif ("PV" in recv_data):
            WRK_flag=2
        elif ("ED" in recv_data):
            WRK_flag=0
        recv_data=""




while True:
    clock.tick()
    img = sensor.snapshot().replace(vflip=False,       #水平翻转
                                    hmirror=False,     #镜像翻转
                                    transpose=False)

    Uart_recv() # 串口接收（接收arduino发送的指令）

    while(WRK_flag):
        if(WRK_flag==2):
            light = Timer(2, freq=50000).channel(1, Timer.PWM, pin=Pin("P6"))
            light.pulse_width_percent(100) # 控制亮度 0~100
            sensor.set_pixformat(sensor.GRAYSCALE)
            while(WRK_flag==2):
                Uart_recv()
                img = sensor.snapshot() # 获取图像
                # 中值滤波
                #img.median(1) # 使用半径为1的中值滤波
                img.gaussian(1) # 使用半径为1的高斯滤波
                img.find_edges(image.EDGE_CANNY, threshold = (40, 80))
                for c in img.find_circles(x_stride=2, y_stride=1 ,threshold = 6000, x_margin = 36, y_margin = 36, r_margin = 28,
                r_min = 38, r_max = 72, r_step = 2):
                    if c.r()>35 and c.r()<100:
                        #img.draw_circle(c.x(), c.y(), c.r(), color = (255,255, 255))
                        img.draw_rectangle(c.x()- c.r(), c.y()- c.r(), 2*c.r(),2*c.r(), color = (255,255, 255))
                        print("Found Circle - Center: ({}, {}), Radius: {} , Magnitude: {}\n\r".format(c.x(), c.y(), c.r() , c.magnitude()))
                        uart.write("DAFound Circle - Center: ({}, {}), Radius: {} , Magnitude: {}\n\r".format(c.x(), c.y(), c.r() , c.magnitude()))


        if(WRK_flag==1):
            sensor.set_pixformat(sensor.RGB565)
            light = Timer(2, freq=50000).channel(1, Timer.PWM, pin=Pin("P6"))
            light.pulse_width_percent(100) # 控制亮度 0~100
            while(WRK_flag==1):
                Uart_recv()
                img = sensor.snapshot() # 获取图像

                # 中值滤波
                #img.median(1) # 使用半径为1的中值滤波
                img.gaussian(1) # 使用半径为1的高斯滤波

                if(Blok_Object==1):
                    # 检测红色色块
                    red_blobs = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=200)
                    if red_blobs:
                        max_blob = max(red_blobs, key=lambda b: b.pixels())
                        img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(255, 0, 0)) # 绘制红色圆形框选
                        img.draw_edges(max_blob.min_corners(), color=(255, 0, 0)) # 绘制红色边缘
                        print("Red Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
                        uart.write("DARed Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))

                elif(Blok_Object==3):
                    # 检测蓝色色块
                        blue_blobs = img.find_blobs([blue_threshold], pixels_threshold=200, area_threshold=200)
                        if blue_blobs:
                            max_blob = max(blue_blobs, key=lambda b: b.pixels())
                            img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(0, 0, 255)) # 绘制蓝色圆形框选
                            img.draw_edges(max_blob.min_corners(), color=(0, 0, 255)) # 绘制蓝色边缘
                            print("Blue Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
                            uart.write("DABlue Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
                elif(Blok_Object==2):
                # 检测绿色色块
                    green_blobs = img.find_blobs([green_threshold], pixels_threshold=200, area_threshold=200)
                    if green_blobs:
                        max_blob = max(green_blobs, key=lambda b: b.pixels())
                        img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(0, 255, 0)) # 绘制绿色圆形框选
                        img.draw_edges(max_blob.min_corners(), color=(0, 255, 0)) # 绘制绿色边缘
                        print("Green Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
                        uart.write("DAGreen Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
