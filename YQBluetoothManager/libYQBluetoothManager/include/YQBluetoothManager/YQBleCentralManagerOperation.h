//
//  YQBleCentralManagerOperation.h
//  Metagem
//
//  Created by 杨清 on 16/3/2.
//  Copyright © 2016年 杨清. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "YQBleCurrCmdStatus.h"


///上报外设发送过来的数据
#define OBSERVE_NOTIFY_CHARACTERISTIC_VALUE     @"observeNotityCharacteristicValue"


// 定义该对象的代理对象必须遵守的协议
@protocol YQBleCentralManagerOperationDelegate <NSObject>
@optional
-(void)BleManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;

#pragma mark !!! Peripheral断开连接
- (void)BleManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

- (void)BlePeripheral:(CBPeripheral *)peripheral didReadRSSI:(NSNumber *)RSSI;

@end


@interface YQBleCentralManagerOperation : NSObject<CBCentralManagerDelegate,CBPeripheralDelegate>
{
//@public
    //系统蓝牙设备管理对象，可以把他理解为主设备，通过他，可以去扫描和连接外设
    CBCentralManager *centerManager;
    dispatch_queue_t serialQueue;
    // 下面四个成员变量都只包含未被连接的外设，不包含已经被连接的外设
    NSMutableArray<CBPeripheral *> *discoverPeripherals;//扫描所有外设，并保存
    NSMutableArray<NSNumber *> *discoverPeripheralsRSSI;//扫描所有外设的信号强度，并保存
    NSMutableArray<CBPeripheral *> *totalDiscoverPeripherals; //所有被发现的外设
    NSMutableArray<NSNumber *> *totalDiscoverPeripheralsRSSI; //所有被发现的外设的信号强度
    NSNotificationCenter *notiCenter; //上报订阅的特性value值
//@public
    YQBleCurrCmdStatus *currCmdStatus;//封装命令，当前命令处理状态，可以用于返回Notification处理的结果
}

@property (nonatomic,weak) id <YQBleCentralManagerOperationDelegate> delegate;

/**
 * 单例
 */
+ (instancetype) sharedCentralManager;



#pragma mark - 蓝牙命令

/**
 * 获得命令状态
 */
-(YQBleCurrCmdStatus *)currCmdStatusGet;

/**
 * 获得蓝牙是否打开
 */
-(BOOL)isBluetoothOpened;

/**
 * 非阻塞式扫描所有外设
 */
-(BOOL)asyncScanAllPeripherals;

/**
 * 获得所有被发现的外设
 */
-(NSMutableArray<CBPeripheral *> *)getTotalDiscoverPeripherals;

/**
 * 获得所有的扫描到外设的RSSI
 */
-(NSMutableArray<NSNumber *> *)RSSITotalGet;

/**
 * 返回已经被当前手机系统连接上的外设
 */
-(NSArray<CBPeripheral *> *)getBeConnectedPeripheralsWithService:(NSString *)serviceUUIDString;

/**
 * 命令1:发送扫描所有外设命令, 阻塞式扫描
 */
-(NSMutableArray<CBPeripheral *> *)scanAllPeripherals;

/**
 * 1.1:获得扫描到外设的RSSI
 */
-(NSMutableArray<NSNumber *> *)RSSIGet;


/**
 * 命令2:发送连接外设命令
 */
-(CBPeripheral *)connectPeripheral:(NSString *)peripheralName;


/**
 * 命令2.1:发送连接外设命令并获得所有services
 */
-(CBPeripheral *)connectPeripheralAndDiscoverAllServices:(NSString *)peripheralName;


/**
 * 命令3:发送读Characteristic Value命令
 */
-(NSData *)readCharacteristicValue:(NSString *)peripheralName
                 serviceUUIDString:(NSString *)serviceUUIDString
          characteristicUUIDString:(NSString *)characteristicUUIDString;


/**
 * 命令4:发送读Descriptor Value命令
 */
-(NSData *)readDescriptorValue:(NSString *)peripheralName
             serviceUUIDString:(NSString *)serviceUUIDString
      characteristicUUIDString:(NSString *)characteristicUUIDString
          descriptorUUIDString:(NSString *)descriptorUUIDString;


/**
 * 命令5:获得characteristic, 很少被调用
 */
- (CBCharacteristic *)getCharacteristic:(NSString *)peripheralName
                      serviceUUIDString:(NSString *)serviceUUIDString
               characteristicUUIDString:(NSString *)characteristicUUIDString;


/**
 * 命令6:发送写Characteristic Value命令
 */
- (CBCharacteristic *)writeCharacteristicValue:(NSString *)peripheralName
                             serviceUUIDString:(NSString *)serviceUUIDString
                      characteristicUUIDString:(NSString *)characteristicUUIDString
                                          data:(NSData *)data;


/**
 * 命令7:订阅通知
 */
- (CBCharacteristic *)addNotifyValueForCharacteristic:(NSString *)peripheralName
                                    serviceUUIDString:(NSString *)serviceUUIDString
                             characteristicUUIDString:(NSString *)characteristicUUIDString;



/**
 * 命令8:取消订阅通知
 */
- (BOOL)removeNotifyValueForCharacteristic:(NSString *)peripheralName
                         serviceUUIDString:(NSString *)serviceUUIDString
                  characteristicUUIDString:(NSString *)characteristicUUIDString;


/**
 * 命令9:断开连接
 */
-(BOOL)disconnectPeripheral;


/**
 * 命令10:停止扫描
 */
-(void)stopScan;

//--------------------------------------------------------------------------
/**
 * 获取外设的RSSI
 */
-(void)readRSSI:(CBPeripheral *)peripheral;


/**
 * 监听从外设发送过来的数据
 */
- (void)addObserverForRecvValue:(id)observer selector:(SEL)aSelector;

/**
 * 移除监听从外设发送过来的数据
 */
-(void)removeObserverForRecvValue:(id)observer;


@end
