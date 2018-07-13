fpcx v1.1(Windows)
MSX-BASIC 起動ツール

行番号の無いbasファイルを引数にして起動すると、行番号をつけてMSX-BASIC上で起動します。gotoの宛先時等は、ラベルを使えます。
Disk Explorer(junnnoさん作) http://hp.vector.co.jp/authors/VA013937/editdisk/index.html
blueMSX(Daniel Vikさん作) http://bluemsx.msxblue.com/
が必要です。

・起動方法
fpcx.exe basfile editdisk.exeのﾌﾙﾊﾟｽ bluemsx.exeのﾌﾙﾊﾟｽ
例：fpc.exe c:\bas\sample.bas C:\apps\editdisk\editdisk.exe C:\apps\bluemsx\bluemsx.exe

・変換後ソース確認モード
fpcx.exe view
上の枠で数字を入れてenterを押すと、その行番号を移動します。
ESCで終了します。

・エディタでの設定例(Megon)
ctrl+O
[bas] [c:\projects\fpc\fpc.exe "%f" C:\apps\editdisk\editdisk.exe C:\apps\bluemsx\bluemsx.exe %g] [適用]

・置換機能
「basrep.def」に
検索文字列,置換後列
を羅列しておくと、置換して実行します。
正規表現が使えます。

・注釈機能
「/*」、「*/」括った部分を注釈とします。

その他文法はtest.xbs,33test.xbsを参考にしてください

----------------------------------------------------------------------
・Perl5互換の正規表現エンジン bregexp.dllはTatsuo Baba氏
(http://www.hi-ho.ne.jp/babaq/)のものを使用させていただきました。
・99 BASIC インタプリタは飯田崇之氏のプログラムです。
(公式ホームページ：http://www.sagami.ne.jp/tadaka/99Basic/)
----------------------------------------------------------------------

v1.0 fpcを元にfpcxを作成
v1.1 2016/07/14 beginなどが10以降正しく使えないバグを修正

------------------
N.I
n.i@10-59.com
http://ni.10-59.com
------------------
