//
//  YQBleCurrCmdStatus.h
//  Metagem
//
//  Created by 杨清 on 16/4/5.
//  Copyright © 2016年 杨清. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>


@interface YQBleCurrCmdStatus : NSObject

/**
 * MARK:初始化命令
 * cmdType = @"scanAllPeripherals", @"connect" , @"readCharacteristicValue" , @"readDescriptorValueForCharacteristic"
 *              @"getBeOperationCharacteristic" , @"writeCharacteristicValue" , @"addNotifyValueForCharacteristic"
 *              @"removeNotifyValueForCharacteristic"
 * cmdStatus = @"start" , @"processing" , @"end"
 * result = @"ok" , @"error"
 */

@property(nonatomic, retain) NSNumber *isBLEOpened;//=0:no, 1:yes

@property(nonatomic, retain) NSNumber *isConnected;//=0:no, 1:yes

@property(nonatomic, retain) NSNumber *cmdStatus;//=0:end, 1:start, 2:processing, 3:processing2

@property(nonatomic, retain) NSNumber *result;//=1:ok, -1:error, nil:uninit

@property(nonatomic, retain) NSString *message;//remind message

@property(nonatomic, retain) NSNumber *cmdType;

@property(nonatomic, retain) NSString *peripheralName;

@property(nonatomic, retain) CBPeripheral * peripheral;

@property(nonatomic, retain) NSNumber *RSSI; //信号强度

@property(nonatomic, retain) NSString *serviceUUIDString;

@property(nonatomic, retain) NSString *characteristicUUIDString;

@property(nonatomic, retain) NSString *descriptorUUIDString;

@property(nonatomic, retain) NSData * characteristicValueForRead;

@property(nonatomic, retain) id descriptorValueForRead;

@property(nonatomic, retain) CBCharacteristic * beOperationCharacteristic; //一般用于被写的特性

@property(nonatomic, retain) NSData *beWritedData;

@property(nonatomic, retain) NSMutableArray<CBCharacteristic *> *characteristicForNotify;

@end
