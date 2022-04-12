import sensor, image, lcd, time
import KPU as kpu
import gc, sys
from fpioa_manager import fm
from machine import UART

fm.register(15, fm.fpioa.UART1_TX, force=True)
fm.register(17, fm.fpioa.UART1_RX, force=True)

uart_A = UART(UART.UART1, 115200)

class Dot(object):
    x = 0
    y = 0
    ok = 0
    flag = 0

    One = 0
    Two = 0
    Three = 0
    Four = 0
    Five = 0
    Six = 0
    Seven = 0
    Eight = 0

dot  = Dot()

#数据打包#
def pack_dot_data():
    pack_data=bytearray([0xAA,0xFF,
        dot.One,dot.Two,dot.Three,dot.Four,dot.Five,dot.Six,dot.Seven,dot.Eight,
        0xCC])

    dot.x = 0
    dot.y = 0
    dot.One = 0
    dot.Two = 0
    dot.Three = 0
    dot.Four = 0
    dot.Five = 0
    dot.Six = 0
    dot.Seven = 0
    dot.Eight = 0

    lens = len(pack_data)      #数据包大小
    #pack_data[3] = lens-6;     #有效数据个数

    #sc = 0
    #ac = 0
    #i = 0
    #while i<(lens-1):
        #sc = sc + pack_data[i]
        #ac = ac + sc
        #i=i+1
    #pack_data[lens-2] = sc
    #pack_data[lens-1] = ac;

    return pack_data
#       #

def lcd_show_except(e):
    import uio
    err_str = uio.StringIO()
    sys.print_exception(e, err_str)
    err_str = err_str.getvalue()
    img = image.Image(size=(224,224))
    img.draw_string(0, 10, err_str, scale=1, color=(0xff,0x00,0x00))
    lcd.display(img)

def main(anchors, labels = None, model_addr="/sd/test.kmodel", sensor_window=(224, 224), lcd_rotation=0, sensor_hmirror=False, sensor_vflip=False):
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_windowing(sensor_window)
    sensor.set_hmirror(1)
    sensor.set_vflip(1)
    sensor.run(1)

    lcd.init(type=1)
    lcd.rotation(lcd_rotation)
    lcd.clear(lcd.WHITE)

    if not labels:
        with open('labels.txt','r') as f:
            exec(f.read())
    if not labels:
        print("no labels.txt")
        img = image.Image(size=(320, 240))
        img.draw_string(90, 110, "no label s.txt", color=(255, 0, 0), scale=2)
        lcd.display(img)
        return 1
    try:
        img = image.Image("startup.jpg")
        lcd.display(img)
    except Exception:
        img = image.Image(size=(320, 240))
        img.draw_string(90, 110, "loading model...", color=(255, 255, 255), scale=2)
        lcd.display(img)

    task = kpu.load(model_addr)
    kpu.init_yolo2(task, 0.5, 0.3, 5, anchors) # threshold:[0,1], nms_value: [0, 1]
    try:
        while(True):
            img = sensor.snapshot()
            t = time.ticks_ms()
            objects = kpu.run_yolo2(task, img)
            t = time.ticks_ms() - t
            if objects:
                for obj in objects:
                    pos = obj.rect()
                    img.draw_rectangle(pos)

                    dot.x = pos[0]+(int)(pos[2]/2)    #x坐标
                    dot.y = pos[1]+(int)(pos[3]/2)    #y坐标
                    dot.ok= dot.ok+1
                    img.draw_cross(dot.x, dot.y)


                    img.draw_string(pos[0], pos[1], "%s : %.2f" %(labels[obj.classid()], obj.value()), scale=2)

                    if (labels[obj.classid()] == "1" and obj.value() > 0.70) or dot.One==1:
                        dot.One = 1
                    else :
                        dot.One = 0

                    if (labels[obj.classid()] == "2" and obj.value() > 0.70) or dot.Two==1:
                        dot.Two = 1
                    else :
                        dot.Two = 0

                    if (labels[obj.classid()] == "3" and obj.value() > 0.70) or dot.Three==1:
                        dot.Three = 1
                    else :
                        dot.Three = 0

                    if (labels[obj.classid()] == "4" and obj.value() > 0.70) or dot.Four==1:
                        dot.Four = 1
                    else :
                        dot.Four = 0

                    if (labels[obj.classid()] == "5" and obj.value() > 0.50) or dot.Five==1:
                        dot.Five = 1
                    else :
                        dot.Five = 0

                    if (labels[obj.classid()] == "6" and obj.value() > 0.70) or dot.Six==1:
                        dot.Six = 1
                    else :
                        dot.Six = 0

                    if (labels[obj.classid()] == "7" and obj.value() > 0.70) or dot.Seven==1:
                        dot.Seven = 1
                    else :
                        dot.Seven = 0

                    if (labels[obj.classid()] == "8" and obj.value() > 0.70) or dot.Eight==1:
                        dot.Eight = 1
                    else :
                        dot.Eight = 0

                   # print("centre_x = %d, centre_y = %d"%(dot.x, dot.y))

            else :
                dot.ok = 0
                dot.flag = dot.ok
                dot.One = 0
                dot.Two = 0
                dot.Three = 0
                dot.Four = 0
                dot.Five = 0
                dot.Six = 0
                dot.Seven = 0
                dot.Eight = 0

            if dot.ok>10:
                dot.flag = 1

            uart_A.write(pack_dot_data())    #发送数据
            img.draw_string(0, 200, "t:%dms" %(t), scale=2)
            lcd.display(img)
    except Exception as e:
        raise e
    finally:
        kpu.deinit(task)


if __name__ == "__main__":
    try:
        labels = ["3", "4", "1", "2", "7", "8", "5", "6"]
        anchors = [1.7048, 1.6693, 1.8474, 2.1746, 2.0003, 1.8557, 2.1034, 2.612, 2.4321, 3.0607]
        # main(anchors = anchors, labels=labels, model_addr=0x300000, lcd_rotation=0)
        main(anchors = anchors, labels=labels, model_addr="/sd/test.kmodel")
    except Exception as e:
        sys.print_exception(e)
        lcd_show_except(e)
    finally:
        gc.collect()
