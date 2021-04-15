//
//  VELiteSDK.h
//  VELiteSDK
//
//  Created by iOS VESDK Team on 2021/1/8.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <VEENUMCONFIGER/VEENUMCONFIGER.h>

typedef NS_ENUM(NSInteger, VELiteFunctionType){
    VELiteFunctionType_Transcoding  = 0,    //转码
    VELiteFunctionType_Reverse,             //倒放
    VELiteFunctionType_Crop,                //裁剪
    VELiteFunctionType_Trim,                //截取
    VELiteFunctionType_Compression,         //压缩
    VELiteFunctionType_Transition,          //转场
    VELiteFunctionType_Adjust,              //调色
    VELiteFunctionType_Speed,               //变速
    VELiteFunctionType_VoiceFX,             //变声
    VELiteFunctionType_Voiceover,           //配音
    VELiteFunctionType_Cover,               //封面
    VELiteFunctionType_Text,                //字幕
    VELiteFunctionType_Sticker,             //贴纸
    VELiteFunctionType_Filter,              //滤镜
    VELiteFunctionType_Effect,              //特效
    VELiteFunctionType_Inpaint,             //去水印
    VELiteFunctionType_Overlay,             //画中画
    VELiteFunctionType_Doodle,              //涂鸦
    VELiteFunctionType_Video2Audio,         //提取声音
    VELiteFunctionType_GIF,                 //GIF制作
};

/**  截取完成回调
 *
 *  cutType         :截取方式
 *  asset/videoPath :截取后文件(路径)
 *  startTime       :截取开始时间
 *  endTime         :截取结束时间
 *  cropRect        :裁剪视频区域 如裁剪为原始比例时，cropRect为CGRectMake(0, 0, 1, 1)
 *
 */
typedef void (^VE_TrimAssetCallbackBlock)(VETrimVideoReturnType cutType,AVURLAsset *asset,CMTime startTime,CMTime endTime, CGRect cropRect);

@interface VELiteSDK : NSObject

/** 自定义截取返回方式(先设置此参数再调截取函数)
 */
@property(nonatomic, copy) void (^trimVideoReturnType)(VETrimVideoReturnType*);


#pragma mark - 打开相册
/**选择视频或图片
 * @param viewController  源控制器
 * @param albumType 选择相册类型（仅选图片，仅选视频，两者皆可）
 * @param callbackBlock 相册选择完成返回一个NSURL数组 NSMutableArray <NSURL *> *List
 * @param cancelBlock 取消选择相册资源
 */

- (BOOL)onVEAlbumWithSuperController:(UIViewController *)viewController
                            albumType:(ALBUMTYPE)albumType
                            callBlock:(VEAlbumCompletionHandler) callbackBlock
                          cancelBlock:(VECancelHandler) cancelBlock;

- (BOOL)onVEAlbumForMediaInfoWithSuperController:(UIViewController *)viewController
                            albumType:(ALBUMTYPE)albumType
                        isDisableEdit:(BOOL)isDisableEdit
                            callBlock:(void(^) (NSMutableArray * files)) callbackBlock
                          cancelBlock:(VECancelHandler) cancelBlock;

#pragma mark- 编辑视频
/**   编辑短视频MV
 *
 *  @param viewController    源控制器
 *  @param urlAsset          视频源
 *  @param clipTimeRange     时间段
 *  @param crop              crop范围 default ：CGRectMake(0, 0, 1, 1)
 *  @param outputVideoPath   视频输出路径
 *  @param callbackBlock     完成编辑回调
 *  @param cancelBlock       取消编辑回调
 */
- (void)editVideoWithSuperController:(UIViewController *)viewController
                            urlAsset:(AVURLAsset *)urlAsset
                       clipTimeRange:(CMTimeRange )clipTimeRange
                                crop:(CGRect)crop
                           musicInfo:(VEMusicInfo *)musicInfo
                          outputPath:(NSString *)outputVideoPath
                            callback:(VECompletionHandler )callbackBlock
                              cancel:(VECancelHandler )cancelBlock;

/**   编辑视频(传入URL数组)
 *
 *  @param viewController    源控制器
 *  @param foldertype        缓存文件夹类型 （Documents、Library、Temp,None)
 *  @param appAlbumCacheName 需扫描的缓存文件夹名称
 *  @param urlsArray         视频/图片路径(NSMutableArray <NSURL*>)如：相册视频 assets-library://asset/asset...
 *  @param outputVideoPath   视频输出路径
 *  @param callbackBlock     完成编辑回调
 *  @param cancelBlock       取消编辑回调
 */
- (void)editVideoWithSuperController:(UIViewController *)viewController
                          foldertype:(FolderType)foldertype
                   appAlbumCacheName:(NSString *)appAlbumCacheName
                           urlsArray:(NSMutableArray *)urlsArray
                          outputPath:(NSString *)outputVideoPath
                            callback:(VECompletionHandler )callbackBlock
                              cancel:(VECancelHandler )cancelBlock;

#pragma mark- 截取视频
/**  截取视频 通过传入视频对象 AVUrlAsset
 *  @param viewController               源控制器
 *  @param title                        导航栏标题
 *  @param backgroundColor              背景色
 *  @param cancelButtonTitle            取消按钮文字
 *  @param cancelButtonTitleColor       取消按钮标题颜色
 *  @param cancelButtonBackgroundColor  取消按钮背景色
 *  @param otherButtonTitle             完成按钮文字
 *  @param otherButtonTitleColor        完成按钮标题颜色
 *  @param otherButtonBackgroundColor   完成按钮背景色
 *  @param urlAsset                     数据源
 *  @param outputVideoPath              视频输出路径
 *  @param callbackBlock                截取完成回调
 *  @param failback                     截取失败回调
 *  @param cancelBlock                  取消截取回调
 
 */
- (void)trimVideoWithSuperController:(UIViewController *)viewController
                     controllerTitle:(NSString *) title
                     backgroundColor:(UIColor  *) backgroundColor
                   cancelButtonTitle:(NSString *) cancelButtonTitle
              cancelButtonTitleColor:(UIColor  *) cancelButtonTitleColor
         cancelButtonBackgroundColor:(UIColor  *) cancelButtonBackgroundColor
                    otherButtonTitle:(NSString *) otherButtonTitle
               otherButtonTitleColor:(UIColor  *) otherButtonTitleColor
          otherButtonBackgroundColor:(UIColor  *) otherButtonBackgroundColor
                            urlAsset:(AVURLAsset *) urlAsset
                          outputPath:(NSString *) outputVideoPath
                       callbackBlock:(VE_TrimAssetCallbackBlock) callbackBlock
                            failback:(VEFailedHandler       ) failback
                              cancel:(VECancelHandler     ) cancelBlock;

#pragma mark- 录制视频

/** 录制视频 参数设置(cameraConfiguration)
 *  @param source        源视图控制器
 *  @param callbackBlock 完成录制回调(result ：0 表示MV 1表示视频)
 *  @param imagebackBlock 拍照完成回调
 *  @param cancelBlock   取消录制回调
 */

- (void)videoRecordAutoSizeWithSourceController: (UIViewController*)source
                                  callbackBlock: (VERecordCompletionHandler)callbackBlock
                                 imagebackBlock: (VECompletionHandler)imagebackBlock
                                     faileBlock: (VEFailedHandler)failBlock
                                         cancel: (VECancelHandler)cancelBlock;

//主题
- (void)pictureMovieWithSuperController_Theme:(UIViewController *)viewController
                                   UrlsArray:(NSMutableArray *)urlsArray
                                  outputPath:(NSString *)outputVideoPath
                                    callback:(VECompletionHandler )callbackBlock
                                      cancel:(VECancelHandler )cancelBlock;
#pragma mark- AE模板
- (void)AETemplateMovieWithSuperController:(UIViewController *)viewController
                                 UrlsArray:(NSMutableArray *)urlsArray
                                outputPath:(NSString *)outputVideoPath
                                    isMask:(BOOL)isMask
                                  callback:(VECompletionHandler )callbackBlock
                                    cancel:(VECancelHandler )cancelBlock;
#pragma mark- 拍同款
- (void)AEHome_SameWithSuperController:(UIViewController *)viewController
                            outputPath:(NSString *)outputVideoPath
                              callback:(VERecordCompletionHandler)callbackBlock
                                cancel:(VECancelHandler)cancelBlock
                        imagebackBlock: (VECompletionHandler)imagebackBlock
                            faileBlock: (VEFailedHandler)failBlock;

- (void)AEHomeWithSuperController:(UIViewController *)viewController
                            outputPath:(NSString *)outputVideoPath
                              callback:(VECompletionHandler)callbackBlock
                                cancel:(VECancelHandler)cancelBlock;
#pragma mark- 模板录制
- (void)templateRecordWithSourceController: (UIViewController*)source
                             callbackBlock: (VERecordCompletionHandler)callbackBlock
                            imagebackBlock: (VECompletionHandler)imagebackBlock
                                faileBlock: (VEFailedHandler)failBlock
                                    cancel: (VECancelHandler)cancelBlock;

#pragma mark - 字说界面
- (void)aeTextAnimateWithSuperViewController:(UIViewController *)viewController
                                  outputPath:(NSString *)outputVideoPath
                                    callback:(VECompletionHandler)callbackBlock
                                      cancel:(VECancelHandler)cancelBlock;
#pragma mark - 字说
- (void)aeTextAnimateWithSuperController:(UIViewController *)viewController
                              outputPath:(NSString *)outputVideoPath
                                callback:(VECompletionHandler )callbackBlock
                                  cancel:(VECancelHandler )cancelBlock;

#pragma mark - 自绘
- (void)customDrawWithSuperController:(UIViewController *)viewController
                           outputPath:(NSString *)outputVideoPath
                             callback:(VECompletionHandler )callbackBlock
                               cancel:(VECancelHandler )cancelBlock;
#pragma mark- 多格 拼图
- (void)dogePuzzleWithSuperController:(UIViewController *)viewController
                                    UrlsArray:(NSMutableArray *)urlsArray
                                   outputPath:(NSString *)outputVideoPath
                                     callback:(VECompletionHandler )callbackBlock
                                       cancel:(VECancelHandler )cancelBlock;

/** 单个媒体编辑
 *
 *  @param viewController    源控制器
 *  @param functionType      编辑类型
 *  @param urlArray          视频/图片路径如：相册视频 assets-library://asset/asset...
 *  @param outputVideoPath   视频输出路径
 *  @param completionHandler     完成编辑回调
 *  @param cancelHandler       取消编辑回调
 */
- (void)singleMediaWithSuperController:(UIViewController *)viewController
                          functionType:(VELiteFunctionType)functionType
                            outputPath:(NSString *)outputVideoPath
                              urlArray:(NSMutableArray <NSURL *>*)urlArray
                     completionHandler:(VECompletionHandler)completionHandler
                         cancelHandler:(VECancelHandler)cancelHandler;

/**   编辑视频(单场景多媒体 最多只能条件两个多媒体)
 *
 *  @param viewController    源控制器
 *  @param foldertype        缓存文件夹类型 （Documents、Library、Temp,None)
 *  @param appAlbumCacheName 需扫描的缓存文件夹名称
 *  @param lists             视频图片路径(NSMutableArray <AVURLAsset*>)
 *  @param outputVideoPath   视频输出路径
 *  @param callbackBlock     完成编辑回调
 *  @param cancelBlock       取消编辑回调
 */
- (void)editVideoWithSuperController_SingleSceneMultimedia:(UIViewController *)viewController
                                                foldertype:(FolderType)foldertype
                                         appAlbumCacheName:(NSString *)appAlbumCacheName
                                                     lists:(NSMutableArray *)lists
                                                outputPath:(NSString *)outputVideoPath
                                                  callback:(VECompletionHandler )callbackBlock
                                                    cancel:(VECancelHandler )cancelBlock;

#pragma mark- 获取视频信息
/**获取视频信息 字典 width height fps bitrate
 *
 */
- (NSDictionary *) getVideoInformation:(AVURLAsset *)urlAsset;

@end
