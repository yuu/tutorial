package main

import (
	"fmt"
	"regexp"
)

// 正規表現パターン生成はコストがかかる
// init() or var の初期化時に生成しよう
// バッククォートで囲む raw string literal を使うことでエスケープを省ける
func main() {
	// MustXXX関数は引数が間違えた場合はPanicが発生する
	// 実行中関数で使わないほうがいい
	var wordReg = regexp.MustCompile(`\w+`)
	fmt.Println(wordReg.Match([]byte("Hello World")))
}
