Pod::Spec.new do |spec|

  spec.name         = "VELiteSDK"
  spec.version      = "0.0.1"
  spec.summary      = "VELiteSDK."
  spec.homepage     = "https://github.com/vefans/VELiteSDK"
  spec.license      = "MIT"
  spec.author       = "iOS VESDK Team"
  spec.platform     = :ios, "9.0"
  spec.source       = { :git => 'https://github.com/vefans/VELiteSDK.git', :tag => spec.version.to_s}
  spec.source_files  = '**/*.{h}'
  spec.vendored_frameworks = 'VELiteSDK.framework'
  spec.requires_arc = true  
  spec.swift_version = "5.0"

  spec.dependency 'SDWebImage'
  spec.dependency 'SDWebImageWebPCoder', '0.2.3'
  spec.dependency 'MBProgressHUD','1.1.0'
  spec.dependency 'SVProgressHUD'
  spec.dependency 'ZipArchive'
  spec.dependency 'Reachability'
  spec.dependency 'ATMHud'
  spec.dependency 'MJRefresh','3.5.0'
  spec.dependency 'VECore'
  spec.dependency 'VEENUMCONFIGER'

end
