# 17th-SmartCar-Wireless_Charging
## A dump version, unstable

这里是黑龙江科技大学17届智能车无线充电组的代码仓库\
做智能车的这半年来，起步仓促，当然，也收获了不少宝贵的东西


本次比赛所用的车模为f车，转向结构为差速转向，灰度摄像头作为主要传感器；主控用的是英飞凌家的TC264，逐飞家的核心板，灰度摄像头也是逐飞家的总钻风130度无畸变摄像头\
通过使用摄像头来识别赛道特征来达到自主行驶的目的，且通过ADC来检测充电线圈，以达到无线充电的目的\
上面提到过，这是个不稳定的版本，毕竟在比赛结束前还没法讲一些基础元素的识别稳定到一个范围内，不过我想，或许有些还是能可以给大家参考的


/USER 文件夹为主控代码，cpu0_main.c以及cpu1_main.c都在其中，此外，还有中断服务函数isr.c\
/CODE 文件夹为封装好的各个模块，按照功能分门别类\
/Libraries 文件夹为封装好的各个扩展模块库，以及逐飞封装好的各个软件功能库，可在此查看库函数的函数原型及源码


还需提一点，今年电赛的代码我是直接在这套代码上改的，所以删去了部分代码也新增了部分代码，主要修改了cpu0_main.c和isr.c，不过各个模块的可读性是不受影响的，主要看那里就好


以上
