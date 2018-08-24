package main

import (
	"fmt"
	"sync"
)

// mapへの操作はスレッドセーフではない
// syncを使った排他処理

type KeyValue struct {
	store map[string]string
	mu    sync.RWMutex
}

func NewKeyValue() *KeyValue {
	return &KeyValue{store: make(map[string]string)}
}

func (v *KeyValue) Set(key, val string) {
	v.mu.Lock()
	defer v.mu.Unlock()
	v.store[key] = val
}

func (v *KeyValue) Get(key string) (string, bool) {
	v.mu.Lock()
	defer v.mu.Unlock()
	val, ok := v.store[key]
	return val, ok
}

func main() {
	val := NewKeyValue()
	val.Set("誕生日", "5/2")
	value, ok := val.Get("誕生日")
	if ok {
		fmt.Println("誕生日", value)
	}
}
