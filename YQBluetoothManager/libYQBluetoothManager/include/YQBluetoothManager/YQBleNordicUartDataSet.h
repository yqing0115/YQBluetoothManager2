//
//  YQBleNordicUartDataSet.h
//  Metagem
//
//  Created by 杨清 on 16/4/13.
//  Copyright © 2016年 杨清. All rights reserved.
//

#import <Foundation/Foundation.h>

/*  蓝牙协议 */

//串口服务的UUID
#define NORDIC_UART_SERVICE_UUID @"6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define NORDIC_LLS_UUID          @"1803"
//特征
#define NORDIC_UART_CHARACTERISTIC_NOTIFY @"6e400003-b5a3-f393-e0a9-e50e24dcca9e"
#define NORDIC_UART_CHARACTERISTIC_WRITE  @"6e400002-b5a3-f393-e0a9-e50e24dcca9e"
#define NORDIC_UART_CHARACTERISTIC_LLS    @"2A06"




@interface YQBleNordicUartDataSet : NSObject

#if 0 //yqing test
#pragma mark - 测试接口
+(NSData *)testDataWithSetUserInfo;
#endif


/**
 * 计算校验和
 */
+(int)verifyCheck:(Byte *)bytes;


/**
 * 命令0x15 , APP发送获取外设电量命令
 */
+(NSData *)dataWithGetDevicePower;



/**
 * 命令0x01 , APP发送重要参数给设备
 * 参数：
 * dateTime：年月日时分秒，各占两位
 * sex: 男／女
 * height:身高
 * weight:体重
 * format:＝0公制，＝1英制
 */
+(NSData *)dataWithSetUserInfoWithSex:(NSString *)sex
                                  age:(NSString *)age
                               height:(NSString *)height
                               weight:(NSString *)weight
                               format:(NSString *)format;



/**
 * 命令0x02, APP获取珠宝设备型号
 */
+(NSData *)dataWithGetDeviceMode;


/**
 * 命令0x03, APP获取珠宝设备编号
 */
+(NSData *)dataWithGetDeviceNumber;


/**
 * 命令0x05, APP获得当前紫外线指数
 */
+(NSData *)dataWithGetCurUvValue;


/**
 * 命令0x07 , APP发送同步历史紫外线数据的请求给设备
 */
+(NSData *)dataWithRequestHistoryUv;


/**
 * 命令0x14, APP获得固件版本号
 */
+(NSData *)dataWithGetFirmwareVersion;

/**
 * 命令0x0D, type=0x01 来电提醒设置
 */
+(NSData *)dataWithSetCallRemind:(BOOL)isOpen shake:(BOOL)isShake;

/**
 * 命令0x0D, type=0x02 短信提醒设置
 */
+(NSData *)dataWithSetSmsRemind:(BOOL)isOpen shake:(BOOL)isShake;

/**
 * 命令0x0D, type=0x03 邮件提醒设置
 */
+(NSData *)dataWithSetEmailRemind:(BOOL)isOpen shake:(BOOL)isShake;

/**
 * 命令0x0D, type=0x04 防晒霜到期提醒设置
 */
+(NSData *)dataWithSetSunDueRemind:(BOOL)isOpen timeout:(unsigned short)timeout;

/**
 * 命令0x0D, type=0x05 紫外线等级超过5级给出提醒
 */
+(NSData *)dataWithSetSunGradeRemind:(BOOL)isOpen;

/**
 * 命令0x0D, type=0x06 作息时间提醒（闹钟）设置
 1)	闹钟最多只能设置3个，按顺序依次设置“闹钟编号”、“时”、“分”、“闹钟设置”
 2)	闹钟编号：取值1,2,3
 3)	“闹钟设置”：
 *	0x00：关闭闹钟提醒功能。
 *	0x01：不重复，即仅提醒一次，以后不再提醒。
 *	0x02：重复，即每天都在设置的时间提醒。
 *	0x03：工作日提醒
 *	0x04：周末提醒
 
 */
+(NSData *)dataWithSetAlarmClock:(Byte)number hour:(Byte)hour minuts:(Byte)minuts type:(Byte)type;

/**
 * 命令0x0D, type=0x07 防丢提醒设置
 */
+(NSData *)dataWithSetLostRemind:(BOOL)isOpen;


/**
 * 命令0x0D, type=0x08 备忘录（自定义）提醒设置
 备忘录最多只能设置2条
 备忘录编号：取值1,2
 备忘录设置：
 0：关闭备忘录提醒功能
 1：开启备忘录提醒功能
 */
+(NSData *)dataWithSetMemoRemind:(Byte)number year:(Byte)year month:(Byte)month day:(Byte)day hour:(Byte)hour minuts:(Byte)minuts type:(Byte)type;


/** 
 * 命令0x0D, type=0x09 心率提醒设置
 1)	开关：关闭或开启该提醒
 λ	0x00：关闭
 λ	0x01：开启
 2)	最小心率和最大心率：
 用户在APP端设置，小于最小心率，大于最大心率，设备均会报警。填0表示未设置。
 */
+(NSData *)dataWithSetHeartRateRemind:(BOOL)isOpen min:(Byte)min max:(Byte)max;

/**
 * 命令0x0D, type=0x0A 微信提醒设置
 */
+(NSData *)dataWithSetWeixinRemind:(BOOL)isOpen shake:(BOOL)isShake;

/**
 * 命令0x0D, type=0x0B 微博提醒设置
 */
+(NSData *)dataWithSetWeiboRemind:(BOOL)isOpen shake:(BOOL)isShake;

/**
 * 命令0x0D, type=0x0C 未接来电提醒设置
 */
+(NSData *)dataWithSetMissedCallRemind:(BOOL)isOpen shake:(BOOL)isShake;


/**
 * 恢复出厂设置命令给设备：0x1f
 */
+(NSData *)dataWithSetFactory;

/**
 * 开启灯光测试的命令：0x20
 */
+(NSData *)dataWithTestOpenLight:(Byte)r G:(Byte)g B:(Byte)b;

/**
 * 关闭灯光测试的命令：0x21
 */
+(NSData *)dataWithTestCloseLight;


//========= 灯光效果 =============================================================================================
#pragma mark 设置事件对应的亮灯(常亮)方式的命令：0x24
/**
 * 设置事件对应的亮灯(常亮)方式的命令：0x24
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventLongLight:(Byte)event
                              isLong:(BOOL)isLong
                                   R:(Byte)r
                                   G:(Byte)g
                                   B:(Byte)b
                             timeout:(unsigned short)timeout
                               level:(Byte)level;

/**
 * 设置事件对应的亮灯(循环亮灭)方式的命令：0x24
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventBlinkLight:(Byte)event
                          isCirculate:(BOOL)isCirculate
                                    R:(Byte)r
                                    G:(Byte)g
                                    B:(Byte)b
                                times:(unsigned short)times
                               ontime:(unsigned short)ontime
                              offtime:(unsigned short)offtime
                                level:(Byte)level;

/**
 * 设置事件对应的亮灯(呼吸灯)方式的命令：0x24
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventBreathLight:(Byte)event
                           isCirculate:(BOOL)isCirculate
                                     R:(Byte)r
                                     G:(Byte)g
                                     B:(Byte)b
                               timeout:(unsigned short)timeout
                                    T0:(Byte)T0
                                    T1:(Byte)T1
                                    T2:(Byte)T2
                                    T3:(Byte)T3
                                    T4:(Byte)T4
                                 level:(Byte)level;


/**
 * 设置事件对应的亮灯(呼吸灯)方式的命令：0x24
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventBreathLightSimplify:(Byte)event
                                             R:(Byte)r
                                             G:(Byte)g
                                             B:(Byte)b
                                            T0:(Byte)T0
                                            T1:(Byte)T1
                                            T2:(Byte)T2
                                            T3:(Byte)T3
                                            T4:(Byte)T4;


//============== 振动效果 ========================================================================================
/**
 * 设置事件对应的马达振动(长振)方式的命令：0x25
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventLongShake:(Byte)event
                              isLong:(BOOL)isLong
                             timeout:(unsigned short)timeout;

/**
 * 设置事件对应的马达振动(循环振停)方式的命令：0x25
 (Byte)event(事件)：启动该亮灯方式的事件，
 来电：1
 短信：2
 邮件：3
 未接来电：4
 微信：5
 微博：6
 触摸：7
 */
+(NSData *)dataWithSetEventCirculateShake:(Byte)event
                              isCirculate:(BOOL)isCirculate
                                    times:(unsigned short)times
                                   ontime:(unsigned short)ontime
                                  offtime:(unsigned short)offtime;


/**
 * 打开陀螺仪 命令：0x20
 */
+(NSData *)dataWithGyroSensorOpen;

/**
 * 关闭陀螺仪 命令：0x21
 */
+(NSData *)dataWithGyroSensorClose;



@end


