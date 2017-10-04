//
//  QBSettings.h
//  Core
//

//  Copyright 2011 QuickBlox team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QBLogger.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, QBConnectionZoneType) {
    
    QBConnectionZoneTypeAutomatic       = 1, //Default. Endpoints are loaded from QuickBlox
    QBConnectionZoneTypeProduction      = 2,
    QBConnectionZoneTypeDevelopment     = 3,
    QBConnectionZoneTypeStage           = 4
};

/** 
 QBSettings class interface.
 Class for framework setup.
 */
@interface QBSettings : NSObject

/** Storing Application ID */
@property (nonatomic, class) NSUInteger applicationID;

/** Set account key (from admin.quickblox.com) */
@property (nonatomic, class, nullable) NSString *accountKey;

/** Setting API Key for Quickblox API */
@property (nonatomic, class, nullable) NSString *authKey;

/** Setting API Secret for Quickblox API */
@property (nonatomic, class, nullable) NSString *authSecret;

/** Setting application group identifier */
@property (nonatomic, class, nullable) NSString *applicationGroupIdentifier;

/** Setting Api Endpoint. Default - https://api.quickblox.com*/
@property (nonatomic, class) NSString *apiEndpoint;

/** Setting Chat endpoint. Default - chat.quickblox.com */
@property (nonatomic, class) NSString *chatEndpoint;

/**
 Load QuickBlox application settings from QBSettings-Info.plist.
 
 @discussion Raises an exception if any configuration step fails.
 @note This method should be called after the app is launched and before using Quickblox services.
*/
+ (void)settingsFromPlist;

/**
 Load QuickBlox application settings from specific plist with name.

 @param name plist file name
 */
+ (void)settingsFromPlistWithName:(NSString *)name;

@end



@interface QBSettings (QBChat)
/**
 Enable or disable chat auto reconnect. The default value is NO
 */
@property (nonatomic, class) BOOL autoReconnectEnabled;

/**
 Enable or disable message carbons
 */
@property (nonatomic, class) BOOL carbonsEnabled;

/**
 Set timeout value for Stream Management send a message operation
 */
@property (nonatomic, class) NSUInteger streamManagementSendMessageTimeout;

/**
 A reconnect timer may optionally be used to attempt a reconnect periodically.
 Default value is 5 seconds
 */
@property (nonatomic, class) NSTimeInterval reconnectTimerInterval;

/**
 Many routers will teardown a socket mapping if there is no activity on the socket.
 For this reason, the stream supports sending keep-alive data.
 This is simply whitespace, which is ignored by the protocol.
 
 Keep-alive data is only sent in the absence of any other data being sent/received.
 
 The default value is 20s.
 The minimum value for TARGET_OS_IPHONE is 10s, else 20s.
 
 To disable keep-alive, set the interval to zero (or any non-positive number).
 
 The keep-alive timer (if enabled) fires every (keepAliveInterval / 4) seconds.
 Upon firing it checks when data was last sent/received,
 and sends keep-alive data if the elapsed time has exceeded the keepAliveInterval.
 Thus the effective resolution of the keepalive timer is based on the interval.
 */
@property (nonatomic, class) NSTimeInterval keepAliveInterval;

/**
 The port the xmpp server is running on.
 If you do not explicitly set the port, the default port will be used.
 If you set the port to zero, the default port will be used.
 
 The default port is 5223.
 **/
@property (nonatomic, class) NSUInteger chatEndpointPort;

@end



@interface QBSettings (UIKit)

/**
 A Boolean value indicating whether the manager is enabled.

 @note If YES, the manager will change status bar network activity indicator according to network
 operation notifications it receives. The default value is NO.
 
 @param enabled
 */
#if TARGET_OS_IOS
@property (nonatomic, class) BOOL networkIndicatorManagerEnabled;

/**
 A Boolean value indicating whether the network activity indicator is currently displayed in the
 status bar.
 */
+ (BOOL)isNetworkIndicatorVisible;

#endif

@end



@interface QBSettings (Logging)

/** Set SDK log level (by default: QBLogLevelDebug). Possible values: QBLogLevelDebug, QBLogLevelNothing. */
@property (nonatomic, class) QBLogLevel logLevel;

/** Enable full XMPP Framework logging to console. By default is disabled. */
+ (void)enableXMPPLogging;

/** Disable full XMPP Framework logging to console. */
+ (void)disableXMPPLogging;

/**
 Enable log to file
 The approximate maximum size to allow log files to grow.
 If a log file is larger than this value after a log statement is appended,
 then the log file is rolled.
 @param maximumFileSize maximum file size in bytes, for example: 1024 * 1024 * 10 = 10Mb
 */
+ (void)enableFileLoggingWithMaximumFileSize:(unsigned long long)maximumFileSize;

/** Disable logging to file */
+ (void)disableFileLogging;

/**
 Returns log file paths if loggint to file is enabled
 Example name of log file:
 /var/mobile/Containers/Data/Application/<UDID>/Library/Caches/Logs/com.quickblox.<app_name> 2016-03-25 11-23.log
 
 @return Array of log file paths or nil if logging to file is disabled
 */
+ (nullable NSArray<NSString *> *)logFilePaths;

@end

@interface QBSettings (NSURLSessionConfiguration)

/**
 Set custom session configuration that will be used for REST API requests.
 '[NSURLSessionConfiguration defaultSessionConfiguration]' is used if nil is passed.
 */

@property (nonatomic, class, nullable) NSURLSessionConfiguration *sessionConfiguration;

@end

@interface QBSettings (DEPRECATED)

/**
 *  Allows to set api endpoint and chat endpoint for service zone.
 *
 *  @note QBConnectionZoneTypeAutomatic is used by default.
 *  If you are using shared server and you are migrating to enterprise account,
 *  then you don't need to resubmit your application, endpoints will be updated automatically.
 
 *  To set custom endpoints use QBConnectionZoneTypeProduction or QBConnectionZoneTypeDevelopment service zone.
 *  Then you should manually activate your service zone by calling setServiceZone:
 *
 *  @param apiEndpoint  apiEndpoint - Endpoint for service i.e. http://my_custom_endpoint.com. Possible to pass nil to return to default settings
 *  @param chatEndpoint chat endpoint
 *  @param zone         QBConnectionZoneType - service zone
 */
+ (void)setApiEndpoint:(nullable NSString *)apiEndpoint
          chatEndpoint:(nullable NSString *)chatEndpoint
        forServiceZone:(QBConnectionZoneType)zone
DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.12.");

/**
 * Allows to change Services Zone to work with Production, Development and Staging environments
 *
 * @param serviceZone - Service Zone. One from QBConnectionZoneType. Default - QBConnectionZoneTypeAutomatic.
 */
+ (void)setServiceZone:(QBConnectionZoneType)serviceZone
DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.12.");

/**
 *  Return current Service Zone
 *
 *  @note serviceZone - Service Zone. One from QBConnectionZoneType. Default - QBConnectionZoneTypeAutomatic
 */
+ (QBConnectionZoneType)currentServiceZone
DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.12.");

@end

NS_ASSUME_NONNULL_END
