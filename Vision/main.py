import sensor
import image
from pyb import UART

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

# 初始化串口
uart = UART(3, 9600)  # 根据实际串口连接配置

# 颜色阈值
red_threshold = (14, 41, 28, 58, 16, 47) # 红色阈值
green_threshold = (26, 62, -58, -33, -34, 52) # 绿色阈值
blue_threshold = (25, 88, -13, 33, -55, -10) # 蓝色阈值

recv_data=""
WRK_flag=0
def Uart_recv():  # 串口接收数据
    global WL_flag

    if (uart.any()):   # 更新串口接收数据
        recv_data = eval(str(uart.read()))

        print(recv_data)
        #uart.write(recv_data)
        if (recv_data!="") :
            print("Openmv has recved CMD data.")

while True:
    Uart_recv()

while True:
    img = sensor.snapshot() # 获取图像

    # 中值滤波
#    img.median(1) # 使用半径为1的中值滤波
    img.gaussian(1) # 使用半径为1的高斯滤波


    # 检测红色色块
    red_blobs = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=200)
    if red_blobs:
        max_blob = max(red_blobs, key=lambda b: b.pixels())
        img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(255, 0, 0)) # 绘制红色圆形框选
        img.draw_edges(max_blob.min_corners(), color=(255, 0, 0)) # 绘制红色边缘
        print("Red Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
        uart.write("DARed Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
    else:
        # 检测蓝色色块
        blue_blobs = img.find_blobs([blue_threshold], pixels_threshold=200, area_threshold=200)
        if blue_blobs:
            max_blob = max(blue_blobs, key=lambda b: b.pixels())
            img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(0, 0, 255)) # 绘制蓝色圆形框选
            img.draw_edges(max_blob.min_corners(), color=(0, 0, 255)) # 绘制蓝色边缘
            print("Blue Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
            uart.write("DABlue Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
        else:
            # 检测绿色色块
            green_blobs = img.find_blobs([green_threshold], pixels_threshold=200, area_threshold=200)
            if green_blobs:
                max_blob = max(green_blobs, key=lambda b: b.pixels())
                img.draw_circle(max_blob.cx(), max_blob.cy(), max_blob.w() // 2, color=(0, 255, 0)) # 绘制绿色圆形框选
                img.draw_edges(max_blob.min_corners(), color=(0, 255, 0)) # 绘制绿色边缘
                print("Green Circle - Center: ({}, {}), Radius: {}".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
                uart.write("DAGreen Circle - Center: ({}, {}), Radius: {}\n\r".format(max_blob.cx(), max_blob.cy(), max_blob.w() // 2))
