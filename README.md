機車安全帽導航HUD
===============================
利用用*Android*智慧型手機進行導航，並將導航資訊透過*藍芽通訊*，呈現於安全帽上的*微型投影設備*。

指導老師：莊家峰教授

# GuidingProject(Android專案名稱)
--------------------------------
>[!WARNING]
>請於Android Studio中點選File->Open->GuidingProject絕對路徑，GuidingProject資料夾將會被Android Studio(簡稱AS
)自動判定為Android專案，點擊即可開啟本專案。
>由於每台電腦的環境不見得相同，AS中的專案由[Gradle](http://www.cnscnjtc.com/android/20161119/25836.html)建構。Gradle在建構專案前，會先核對專案中標示之Android SDK絕對路徑是否存在。若不存在，會跳出一個視窗要求更改路徑。這時只要選擇確認即可，Gradle會自動幫你更改。
>若專案建構失敗(出現紅字，或者fail_to_sych等等字眼)，請點擊AS視窗最下方工具列的Build。根據顯示的錯誤訊息排除障礙(理論上啦)。
>可從AS視窗最左邊工具列選擇1.Project，可以看到專案的所有資料夾擊檔案。根據經驗，其中有三個檔案較可能造成專案建構失敗:
>>build.gradle(Project:GuidingProject)
>>build.gradle(Module:app)
>>AndroidManifest.xml

##Java程式碼
--------------------------------
>[!NOTE]
>路徑: GuidingProject/app/src/main/java/com/p1/genius/bluetoothconectionapp/
>藏得非常隱密。

###MainActivity.java
---------------------
主畫面程式碼。

###MapsActivity.java
--------------------
導航畫面程式碼。

###BluetoothController.java
---------------------------
管理藍芽通訊的程式碼。

###GuidingThread.java
---------------------
執行導航任務的程式碼。


##使用者介面(xml檔)
------------------
>[!NOTE]
>路徑: GuidingProject/app/src/main/res/layout/

###activity_main.xml
--------------------
決定主畫面的長相。

###activity_maps.xml
--------------------
決定導航畫面的長相。

##Google Services說明
----------------
使用到的services:
-[Google LocationServices](https://developers.google.com/android/reference/com/google/android/gms/location/LocationServices)
-[Google GeoAPI](https://developers.google.com/maps/documentation/geolocation/intro)
-[Google Directions API](https://developers.google.com/maps/documentation/directions/intro)
-[Google Cloud Translation API](https://cloud.google.com/translate/docs/)

>[!IMPORTANT]
>要使用Directions API及Translation API，需要先開通[Google Cloud Platform](https://cloud.google.com/)。
>並且為專案申請一組金鑰，將金鑰加入AndroidManifest.xml中(怎麼加入請自行Google)。
>此專案已經有一組金鑰，已能正常取得服務。然而只有金鑰持有人才能從Google Cloud Platform查看與Google伺服器連線的資訊，因此建議自行開通帳號申請自己的金鑰。

#GPU_test.ino(Arduino程式碼)
---------------------------
> [!NOTE]
>請先在電腦中，Arduino的Libary資料夾中加入這些[函式庫](https://drive.google.com/open?id=1BN2cVhkNcPo1DAjy2CpQeJpGof3ncZrU)。

Arduino端*建立藍芽連線*、*導航指令判讀*、*設定指令顯示圖*的程式碼。

#外殼3D圖檔