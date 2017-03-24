//
//  QMPermissions.m
//  Q-municate
//
//  Created by Vitaliy Gorbachov on 5/11/16.
//  Copyright © 2016 Quickblox. All rights reserved.
//

#import "QMPermissions.h"

@implementation QMPermissions

+ (void)requestPermissionToMicrophoneWithCompletion:(PermissionBlock)completion {
    
    AVAudioSessionRecordPermission recordPermission = [[AVAudioSession sharedInstance] recordPermission];
    
    PermissionBlock comletionBlock = ^(BOOL granted) {
        
        if (completion) {
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                completion(granted);
            });
        }
    };
    
    if (recordPermission == AVAudioSessionRecordPermissionUndetermined) {
        
        [[AVAudioSession sharedInstance] requestRecordPermission:comletionBlock];
    }
    else {
        
        comletionBlock(recordPermission == AVAudioSessionRecordPermissionGranted);
    }
}

+ (void)requestPermissionToCameraWithCompletion:(PermissionBlock)completion {
    
    NSString *mediaType = AVMediaTypeVideo;
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];
    switch (authStatus) {
            
        case AVAuthorizationStatusNotDetermined: {
            
            [AVCaptureDevice requestAccessForMediaType:mediaType completionHandler:^(BOOL granted) {
                
                if (completion) {
                    
                    dispatch_async(dispatch_get_main_queue(), ^{
                        
                        completion(granted);
                    });
                }
            }];
            
            break;
        }
            
        case AVAuthorizationStatusRestricted:
        case AVAuthorizationStatusDenied:
            
            if (completion) {
                
                completion(NO);
            }
            
            break;
            
        case AVAuthorizationStatusAuthorized:
            
            if (completion) {
                
                completion(YES);
            }
            
            break;
    }
}

@end
