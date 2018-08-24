package main

import (
	crand "crypto/rand"
	"encoding/binary"
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var s int64

	// crypt/rand から Seed 値を取得
	if err := binary.Read(crand.Reader, binary.LittleEndian, &s); err != nil {
		// crypto/rand から read できなかった場合の代替手段
		s = time.Now().UnixNano()
	}

	rand.Seed(s)
	fmt.Println(rand.Int63)
}
