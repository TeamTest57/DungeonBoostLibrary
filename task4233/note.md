# 正方形探索
## Task
 - nxnマスに任意の値が格納されている
 - 与えられた値cだけから成る最大の正方形の面積を求めよ
 
## Editorial
 - `dp[i][j] := (i,j)から左上に向かってできる最大の正方形の辺の長さ`
 - 初期化
   - 上端と左端のタイル(hi,wi=0の場所にあるタイル)で, `dp[i][j] = T[i][j]==c?1:0`とする
 - 遷移
   - `dp[i][j] = min(dp[hi-1][wi-1], dp[hi][wi-1], dp[hi-1][wi]) + 1`
   - easy
   
# ヒストグラムの中の最大長方形探索
## Task
 - 横幅がnのヒストグラムがある
 - このヒストグラム内に存在する最大の長方形の面積を求めよ

## Editorial
 - `Rectangle{ width, xPos }`を用意して, その情報をstackに入れることで更新していく
 - 遷移
   - stackが空の場合　もしくは　stackTopのwidthが今見ている場所のwidthよりも小さい場合
     - stackに今見ている場所のwidth, xPosをpushする
   - stackTopのwidthが, 今見ている場所のwidthと等しい場合
     - 何もしない(過去の値を引き継ぐ)
   - stackTopのwidthが, 今見ている場所のwidthよりも大きい場合
     - stackTopのwidthが, 今見ている場所のwidth以上である限りその面積を計算して最大値を更新する
     - 更新終了後, stackに今見ている場所のwidth, xPosをpushする
     - xPosは最後にstackTopから取り出したwidthの値とする
 - こういうdpもあるんですね

# 長方形探索
## Task
 - nxnマスに任意の値が格納されている
 - 与えられた値cだけから成る最大の長方形の面積を求めよ
 
## Editorial
 - まず上からcが何個連続しているかを示すテーブルを作る
   - 各列ごとで上から最大値を更新すればおk
 - 生成したテーブルについて, 先述したヒストグラム探索を用いれば良い
   - 列ごとで生成したテーブルの値を参考に更新していくだけ
 - これも良い応用

# 参考文献
 - [最大正方形の面積　正方形探索](http://algorithms.blog55.fc2.com/blog-entry-131.html)
 - [ヒストグラム中の最大の長方形の面積](http://algorithms.blog55.fc2.com/blog-entry-132.html)
 - [長方形探索：　最大長方形の面積　Largest Rectangle](http://algorithms.blog55.fc2.com/blog-entry-133.html)
